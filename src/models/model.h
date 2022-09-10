#pragma once
#include <vec.h>

typedef struct {
    vec3 position;
    vec3 normal;
    vec3 tex;
} Vertex;

typedef struct {
    Vertex a;
    Vertex b;
    Vertex c;
} Face;

// Group of Faces
typedef struct {
    Face* faces;
    unsigned int nfaces;
} Primitive;

typedef struct {
    Primitive* primitives;
    unsigned int nprimitives;
} Model;

extern void draw_model(const Model* m);
