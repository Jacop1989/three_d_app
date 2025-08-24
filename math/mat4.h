#ifndef MAT4_H
#define MAT4_H

#include "vec.h"

typedef struct { float m[16]; } mat4;

mat4 mat4_identity(void);
mat4 mat4_mul(mat4 a, mat4 b);
mat4 mat4_translate(vec3 v);
mat4 mat4_scale(vec3 v);
mat4 mat4_rotate_x(float angle);
mat4 mat4_rotate_y(float angle);
mat4 mat4_rotate_z(float angle);
mat4 mat4_perspective(float fov_deg, float aspect, float znear, float zfar);
mat4 mat4_look_at(vec3 eye, vec3 target, vec3 up);

#endif
