// main.c
// ตัวอย่างการใช้ framebuffer และ SDL2 เพื่อแสดงผลกราฟิกพื้นฐาน
// โดยใช้มาตรฐานภาษา C17
// คอมไพล์ด้วย: gcc src/app/main.c src/app/camera.c src/math/vec.c src/math/mat4.c src/renderer/framebuffer.c src/renderer/line.c -I src -I include -lSDL2 -lm -o cad_wireframe
// คอมไพล์สำหรับ debug: gcc -g src/app/main.c src/app/camera.c src/math/vec.c src/renderer/framebuffer.c src/renderer/line.c -I src -lSDL2 -lm -o cad_wireframe
// รันด้วย: ./cad_wireframe



#include <string.h>
#include <SDL2/SDL.h>
#include "math/vec.h"
#include "math/mat4.h"
#include "renderer/framebuffer.h"
#include "renderer/line.h"
#include "app/camera.h"

typedef struct { float x, y, z, w; } vec4;

static vec4 mat4_mul_vec4(mat4 m, vec4 v){
    vec4 r;
    r.x = m.m[0]*v.x + m.m[4]*v.y + m.m[8]*v.z + m.m[12]*v.w;
    r.y = m.m[1]*v.x + m.m[5]*v.y + m.m[9]*v.z + m.m[13]*v.w;
    r.z = m.m[2]*v.x + m.m[6]*v.y + m.m[10]*v.z + m.m[14]*v.w;
    r.w = m.m[3]*v.x + m.m[7]*v.y + m.m[11]*v.z + m.m[15]*v.w;
    return r;
}

int main(){
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }
    SDL_Window* win = SDL_CreateWindow("3D",0,0,800,600,0);
    if (!win) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Surface* surf = SDL_GetWindowSurface(win);
    if (!surf) {
        SDL_Log("SDL_GetWindowSurface failed: %s", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    framebuffer* fb = fb_create(surf->w, surf->h);
    if (!fb) {
        SDL_Log("fb_create failed");
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    camera cam = {
        .yaw = 0.0f,
        .pitch = 0.0f,
        .distance = 5.0f,
        .target = {0.0f, 0.0f, 0.0f}
    };

    int running = 1;
    while(running){
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            if(e.type==SDL_QUIT) running=0;
            if(e.type==SDL_MOUSEMOTION && (e.motion.state & SDL_BUTTON_RMASK)){
                cam.yaw += e.motion.xrel * 0.01f;
                cam.pitch += e.motion.yrel * 0.01f;
                if(cam.pitch > 1.5f) cam.pitch = 1.5f;
                if(cam.pitch < -1.5f) cam.pitch = -1.5f;
            } else if(e.type==SDL_MOUSEWHEEL){
                cam.distance -= e.wheel.y * 0.5f;
                if(cam.distance < 0.5f) cam.distance = 0.5f;
            }
        }

        camera_update_viewproj(&cam, fb->w, fb->h);

        fb_clear(fb, 0x000000ff, 1.0f);

        float t = SDL_GetTicks() * 0.001f;
        mat4 model = mat4_mul(mat4_rotate_y(t), mat4_rotate_x(t*0.5f));
        mat4 mvp = mat4_mul(cam.viewproj, model);

        vec3 verts[8] = {
            {-1,-1,-1}, {1,-1,-1}, {1,1,-1}, {-1,1,-1},
            {-1,-1, 1}, {1,-1, 1}, {1,1, 1}, {-1,1, 1}
        };

        int sx[8], sy[8];
        for(int i=0;i<8;i++){
            vec4 v = {verts[i].x, verts[i].y, verts[i].z, 1.0f};
            vec4 p = mat4_mul_vec4(mvp, v);
            if(p.w != 0.0f){ p.x/=p.w; p.y/=p.w; p.z/=p.w; }
            sx[i] = (int)((p.x*0.5f+0.5f)*fb->w);
            sy[i] = (int)((1.0f-(p.y*0.5f+0.5f))*fb->h);
        }

        int edges[12][2] = {
            {0,1},{1,2},{2,3},{3,0},
            {4,5},{5,6},{6,7},{7,4},
            {0,4},{1,5},{2,6},{3,7}
        };
        for(int i=0;i<12;i++){
            draw_line(fb,
                      sx[edges[i][0]], sy[edges[i][0]],
                      sx[edges[i][1]], sy[edges[i][1]],
                      0xffffffff);
        }

        memcpy(surf->pixels, fb->color, fb->w*fb->h*4);
        SDL_UpdateWindowSurface(win);
        SDL_Delay(16); // Limit to ~60 FPS
    }
    fb_destroy(fb);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
