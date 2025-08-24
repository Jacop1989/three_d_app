// main.c
// ตัวอย่างการใช้ framebuffer และ SDL2 เพื่อแสดงผลกราฟิกพื้นฐาน
// โดยใช้มาตรฐานภาษา C17
// คอมไพล์ด้วย: gcc src/app/main.c src/app/camera.c src/math/vec.c src/math/mat4.c src/renderer/framebuffer.c src/renderer/line.c -I src -I include -lSDL2 -lm -o cad_wireframe
// คอมไพล์สำหรับ debug: gcc -g src/app/main.c src/app/camera.c src/math/vec.c src/renderer/framebuffer.c src/renderer/line.c -I src -lSDL2 -lm -o cad_wireframe
// รันด้วย: ./cad_wireframe



#include <string.h>
#include <SDL2/SDL.h>
#include "math/vec.h"
#include "renderer/framebuffer.h"
#include "renderer/line.h"
#include "app/camera.h"

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

        // ตัวอย่าง: วาดสี่เหลี่ยมจัตุรัส
        draw_line(fb,100,100,200,100,0xffffffff);
        draw_line(fb,200,100,200,200,0xffffffff);
        draw_line(fb,200,200,100,200,0xffffffff);
        draw_line(fb,100,200,100,100,0xffffffff);

        memcpy(surf->pixels, fb->color, fb->w*fb->h*4);
        SDL_UpdateWindowSurface(win);
        SDL_Delay(16); // Limit to ~60 FPS
    }
    fb_destroy(fb);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
