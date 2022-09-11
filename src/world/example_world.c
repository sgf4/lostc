#include "world.h"
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <input.h>
#include <gui/menu_list.h>
#include <models/cube.h>

static unsigned int listid;
#define list_size 1

static void draw() {
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0}; /* bright white */
    GLfloat mat_diffuse[] = {0.0, 1.0, 1.0, 1.0};
    GLfloat mat_ambient[] = {0.0, 0.4, 0.4, 1.0}; /* same as diffuse */
    GLfloat mat_shininess = 5.f;

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
    glCallList(listid);
    glPopMatrix();
}


void example_world_init() {
    world_init();
    // Prepare lights
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHT0);
    listid = glGenLists(list_size);
    glNewList(listid, GL_COMPILE);
    draw_model(&cube_model);
    glEndList();

    glNewList(listid+1, GL_COMPILE);
    glutSolidCube(1);
    glEndList();

    player.position = (vec3){0.f, 0.f, -5.f};
}

void example_world_update() {
    world_update();
    glEnable(GL_LIGHTING);
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0}; /* bright white */
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};

    float light_ambient[] = {1.f, 1.f, 1.f, 1.0};
    float light_pos[] = {4.f, 4.f, 4.f, 1.f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    draw();

    if (input_getkeydown(KEY_ESC)) {
        example_world_destroy();
        main_menu_init();
        window_set_loop(main_menu_update);
    }
    glDisable(GL_LIGHTING);
}

void example_world_destroy() {
    world_destroy();  
    glDeleteLists(listid, list_size);
    glDisable(GL_NORMALIZE);
    glDisable(GL_LIGHT0);  
}

