#pragma once
#include <vec.h>

typedef struct {
    float sensibility;
    vec3 position;
    vec3 direction;
} Camera;

extern Camera camera;

void camera_update(void);
