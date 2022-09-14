#pragma once

typedef struct {
    float x;
    float y;
    float z;
} vec3;

typedef struct {
    int x;
    int y;
} ivec2;

#define ivec2_opv(v1, v2, op) v1.x op##= v2.x, v1.y op##= v2.y
#define ivec2_addv(v1, v2) ivec2_opv(v1, v2, +)
#define ivec2_subv(v1, v2) ivec2_opv(v1, v2, -)
#define ivec2_mulv(v1, v2) ivec2_opv(v1, v2, *)
#define ivec2_divv(v1, v2) ivec2_opv(v1, v2, /)

#define ivec2_opn(v1, n, op) v1.x op##= n, v1.y op##= n
#define ivec2_addn(v1, n) ivec2_opn(v1, n, +)
#define ivec2_subn(v1, n) ivec2_opn(v1, n, -)
#define ivec2_muln(v1, n) ivec2_opn(v1, n, *)
#define ivec2_divn(v1, n) ivec2_opn(v1, n, /)


#define vec3_opv(v1, v2, op) v1.x op##= v2.x, v1.y op##= v2.y, v1.z op##= v2.z
#define vec3_addv(v1, v2) vec3_opv(v1, v2, +)
#define vec3_subv(v1, v2) vec3_opv(v1, v2, -)
#define vec3_mulv(v1, v2) vec3_opv(v1, v2, *)
#define vec3_divv(v1, v2) vec3_opv(v1, v2, /)

#define vec3_opn(v1, n, op) v1.x op##= n, v1.y op##= n
#define vec3_addn(v1, n) vec3_opn(v1, n, +)
#define vec3_subn(v1, n) vec3_opn(v1, n, -)
#define vec3_muln(v1, n) vec3_opn(v1, n, *)
#define vec3_divn(v1, n) vec3_opn(v1, n, /)

#define clampGt(x, c1) x = x > c1 ? c1 : x
#define clampLt(x, c1) x = x < c1 ? c1 : x
#define clamp(x, c1, c2) clampLt(x, c1), clampGt(x, c2)
