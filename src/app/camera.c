#include "camera.h"
#include <math.h>

void camera_update_viewproj(camera *cam, int width, int height){
    float cy = cosf(cam->yaw);
    float sy = sinf(cam->yaw);
    float cp = cosf(cam->pitch);
    float sp = sinf(cam->pitch);

    vec3 eye = {
        cam->target.x + cam->distance * cp * sy,
        cam->target.y + cam->distance * sp,
        cam->target.z + cam->distance * cp * cy
    };

    cam->view = mat4_look_at(eye, cam->target, (vec3){0.0f, 1.0f, 0.0f});
    float aspect = (float)width / (float)height;
    cam->proj = mat4_perspective(60.0f, aspect, 0.1f, 1000.0f);
    cam->viewproj = mat4_mul(cam->proj, cam->view);
}
