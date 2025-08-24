// renderer/line.h
#ifndef LINE_H
#define LINE_H

#include <stdint.h>
#include "framebuffer.h"

// ฟังก์ชันวาดเส้นแบบ Bresenham
void draw_line(framebuffer* fb,
               int x0, int y0,
               int x1, int y1,
               uint32_t color);

#endif
