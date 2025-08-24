#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <stdint.h>

typedef struct {
    int w, h;
    uint32_t* color;
    float* depth;
} framebuffer;

framebuffer* fb_create(int w, int h);
void fb_clear(framebuffer* fb, uint32_t color, float depth);
void fb_putpixel(framebuffer* fb, int x, int y, uint32_t color, float z);
void fb_destroy(framebuffer* fb);

#endif
