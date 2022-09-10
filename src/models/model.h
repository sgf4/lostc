#pragma once
#include <vec.h>

typedef struct {
    Vec3 position;
    Vec3 normal;
    Vec3 tex;
} Vertex;

typedef struct {
    Vertex a;
    Vertex b;
    Vertex c;
} Face;

typedef struct {
    unsigned int nfaces;
    const Face* faces;
} Model;

extern void draw_model(Model* m);
