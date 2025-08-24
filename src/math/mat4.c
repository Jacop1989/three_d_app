#include "mat4.h"
#include <math.h>
#include "vec.h"

#define DEG2RAD (0.01745329251994329577f)

mat4 mat4_identity(void){
    return (mat4){ {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1} };
}

mat4 mat4_mul(mat4 a, mat4 b){
    mat4 r = {0};
    for(int c=0;c<4;c++){
        for(int r_i=0;r_i<4;r_i++){
            float sum = 0.0f;
            for(int k=0;k<4;k++){
                sum += a.m[k*4 + r_i] * b.m[c*4 + k];
            }
            r.m[c*4 + r_i] = sum;
        }
    }
    return r;
}

mat4 mat4_translate(vec3 v){
    mat4 r = mat4_identity();
    r.m[12] = v.x;
    r.m[13] = v.y;
    r.m[14] = v.z;
    return r;
}

mat4 mat4_scale(vec3 v){
    mat4 r = {0};
    r.m[0] = v.x;
    r.m[5] = v.y;
    r.m[10] = v.z;
    r.m[15] = 1.0f;
    return r;
}

mat4 mat4_rotate_x(float angle){
    float c = cosf(angle), s = sinf(angle);
    mat4 r = mat4_identity();
    r.m[5] = c;  r.m[9] = -s;
    r.m[6] = s;  r.m[10] = c;
    return r;
}

mat4 mat4_rotate_y(float angle){
    float c = cosf(angle), s = sinf(angle);
    mat4 r = mat4_identity();
    r.m[0] = c;  r.m[8] = s;
    r.m[2] = -s; r.m[10] = c;
    return r;
}

mat4 mat4_rotate_z(float angle){
    float c = cosf(angle), s = sinf(angle);
    mat4 r = mat4_identity();
    r.m[0] = c;  r.m[4] = -s;
    r.m[1] = s;  r.m[5] = c;
    return r;
}

mat4 mat4_perspective(float fov_deg, float aspect, float znear, float zfar){
    float f = 1.0f / tanf((fov_deg * DEG2RAD) / 2.0f);
    mat4 r = {0};
    r.m[0] = f/aspect;
    r.m[5] = f;
    r.m[10] = (zfar + znear) / (znear - zfar);
    r.m[11] = -1.0f;
    r.m[14] = (2.0f * zfar * znear) / (znear - zfar);
    return r;
}

mat4 mat4_look_at(vec3 eye, vec3 target, vec3 up){
    vec3 f = vec3_norm(vec3_sub(target, eye));
    vec3 s = vec3_norm(vec3_cross(f, up));
    vec3 u = vec3_cross(s, f);

    mat4 r = mat4_identity();
    r.m[0] = s.x; r.m[4] = s.y; r.m[8]  = s.z;
    r.m[1] = u.x; r.m[5] = u.y; r.m[9]  = u.z;
    r.m[2] = -f.x; r.m[6] = -f.y; r.m[10] = -f.z;
    r.m[12] = -vec3_dot(s, eye);
    r.m[13] = -vec3_dot(u, eye);
    r.m[14] = vec3_dot(f, eye);
    return r;
}

/* Example tests:
mat4 I = mat4_identity();
mat4 T = mat4_translate((vec3){1,2,3});
mat4 S = mat4_scale((vec3){2,2,2});
mat4 Rx = mat4_rotate_x(0.5f);
mat4 P = mat4_perspective(60.0f, 1.0f, 0.1f, 100.0f);
vec3 eye = {0,0,3}, target = {0,0,0}, up = {0,1,0};
mat4 V = mat4_look_at(eye, target, up);
mat4 VP = mat4_mul(P, V);
<<<<<<< HEAD:math/mat4.c
*/
=======
*/
>>>>>>> a36dfee (Restructure: split into /src/{core,math,geo,render,scene,sketch,features,io,ui,app} and /include):src/math/mat4.c
