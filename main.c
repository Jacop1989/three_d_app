// main.c
// ตัวอย่างการใช้ framebuffer และ SDL2 เพื่อแสดงผลกราฟิกพื้นฐาน
// โดยใช้มาตรฐานภาษา C17
// คอมไพล์ด้วย: gcc main.c math/vec.c renderer/framebuffer.c renderer/line.c -I. -lSDL2 -lm -o cad_wireframe
// คอมไพล์สำหรับ debug: gcc -g main.c math/vec.c renderer/framebuffer.c renderer/line.c -I. -lSDL2 -lm -o cad_wireframe
// รันด้วย: ./cad_wireframe



#include <SDL2/SDL.h>
#include "math/vec.h"
#include "renderer/framebuffer.h"
#include "renderer/line.h"

int main(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win = SDL_CreateWindow("3D",0,0,800,600,0);
    SDL_Surface* surf = SDL_GetWindowSurface(win);

    framebuffer* fb = fb_create(surf->w, surf->h);
    int running = 1;
    while(running){
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            if(e.type==SDL_QUIT) running=0;
        }
        fb_clear(fb, 0x000000ff, 1.0f);

        // ตัวอย่าง: วาดสี่เหลี่ยมจัตุรัส
        draw_line(fb,100,100,200,100,0xffffffff);
        draw_line(fb,200,100,200,200,0xffffffff);
        draw_line(fb,200,200,100,200,0xffffffff);
        draw_line(fb,100,200,100,100,0xffffffff);

        memcpy(surf->pixels, fb->color, fb->w*fb->h*4);
        SDL_UpdateWindowSurface(win);
    }
    fb_destroy(fb);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
