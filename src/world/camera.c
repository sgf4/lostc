#include "camera.h"
#include "world.h"
#include <window.h>
#include <input.h>
#include <math.h>
#include <GL/glu.h>

Camera camera = {.sensibility=0.1f};

void camera_update() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0f, (float)window_width/window_height, 0.01f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    Vec3* dir = &camera.direction;
    glRotatef(dir->x, 1, 0, 0);
    glRotatef(dir->y, 0, 1, 0);
    glRotatef(dir->z, 0, 0, 1);
    clamp(dir->x, -90.f, 90.f);
    dir->y -= 360 * (int)(dir->y/180);
    
    Vec3* p = &camera.position;
    glTranslatef(p->x, p->y, p->z);
}
