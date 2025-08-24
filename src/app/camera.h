#ifndef CAMERA_H
#define CAMERA_H

#include "math/vec.h"
#include "math/mat4.h"

typedef struct {
    float yaw, pitch, distance;
    vec3 target;
    mat4 view;
    mat4 proj;
    mat4 viewproj;
} camera;

void camera_update_viewproj(camera *cam, int width, int height);

#endif // CAMERA_H
