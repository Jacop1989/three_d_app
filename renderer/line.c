#include <stdlib.h>
#include "framebuffer.h"

void draw_line(framebuffer* fb, int x0, int y0, int x1, int y1, uint32_t color){
    int dx = abs(x1-x0), sx = x0<x1?1:-1;
    int dy = -abs(y1-y0), sy = y0<y1?1:-1;
    int err = dx + dy;
    while(1){
        fb_putpixel(fb,x0,y0,color,0.0f);
        if(x0==x1 && y0==y1) break;
        int e2 = 2*err;
        if(e2 >= dy){ err += dy; x0 += sx; }
        if(e2 <= dx){ err += dx; y0 += sy; }
    }
}
