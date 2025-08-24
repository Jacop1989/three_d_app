#include "framebuffer.h"
#include <stdlib.h>
#include <string.h>

framebuffer* fb_create(int w, int h){
    framebuffer* fb = malloc(sizeof(framebuffer));
    fb->w = w; fb->h = h;
    fb->color = malloc(sizeof(uint32_t)*w*h);
    fb->depth = malloc(sizeof(float)*w*h);
    return fb;
}

void fb_clear(framebuffer* fb, uint32_t color, float depth){
    for(int i=0;i<fb->w*fb->h;i++){
        fb->color[i]=color;
        fb->depth[i]=depth;
    }
}

void fb_putpixel(framebuffer* fb, int x, int y, uint32_t color, float z){
    if(x<0||y<0||x>=fb->w||y>=fb->h) return;
    int idx = y*fb->w + x;
    if(z < fb->depth[idx]){
        fb->depth[idx] = z;
        fb->color[idx] = color;
    }
}

void fb_destroy(framebuffer* fb){
    free(fb->color); free(fb->depth); free(fb);
}
