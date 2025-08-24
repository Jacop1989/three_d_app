#ifndef VEC_H
#define VEC_H

typedef struct { float x, y, z; } vec3;

vec3 vec3_add(vec3 a, vec3 b);
vec3 vec3_sub(vec3 a, vec3 b);
vec3 vec3_cross(vec3 a, vec3 b);
float vec3_dot(vec3 a, vec3 b);
vec3 vec3_norm(vec3 v);

#endif
