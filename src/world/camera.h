#pragma once
#include <vec.h>

typedef struct {
    float sensibility;
    Vec3 position;
    Vec3 direction;
} Camera;

extern Camera camera;

void camera_update(void);
