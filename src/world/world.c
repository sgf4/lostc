#include "world.h"
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <window.h>

void world_init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClearDepth(1.f);
    glutSetCursor(GLUT_CURSOR_NONE);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    //glutSetCursor(GLUT_CURSOR_NONE);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void world_destroy() {
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
}

void (*world_update_f) (void);
void world_update() {
    glutWarpPointer(window_width / 2, window_height / 2);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera_update();
    player_update(&player);
}

