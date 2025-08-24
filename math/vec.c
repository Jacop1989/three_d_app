#include "vec.h"
#include <math.h>

vec3 vec3_add(vec3 a, vec3 b){ return (vec3){a.x+b.x, a.y+b.y, a.z+b.z}; }
vec3 vec3_sub(vec3 a, vec3 b){ return (vec3){a.x-b.x, a.y-b.y, a.z-b.z}; }
vec3 vec3_cross(vec3 a, vec3 b){
    return (vec3){
        a.y*b.z - a.z*b.y,
        a.z*b.x - a.x*b.z,
        a.x*b.y - a.y*b.x
    };
}
float vec3_dot(vec3 a, vec3 b){ return a.x*b.x + a.y*b.y + a.z*b.z; }
vec3 vec3_norm(vec3 v){
    float l = sqrtf(vec3_dot(v,v));
    return (vec3){v.x/l, v.y/l, v.z/l};
}
