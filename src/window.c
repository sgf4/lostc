#include "window.h"

#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <stdio.h>
#include <world/world.h>
#include <GL/freeglut.h>
#include <gui/text.h>
#include <input.h>
#include <time.h>

int window_width = 640;
int window_height = 480;
iVec2 window_center;
const char* window_title = "omg";
void (*window_loop) (void);
bool window_cursor_ishiden;

static void resize_callback(int w, int h) {
    window_width = w;
    window_height = h;
    window_center = (iVec2){w/2, h/2};
    glViewport(0, 0, w, h);
}

static void show_fps() {
    glEnable(GL_TEXTURE_2D);
    char num[5];
    snprintf(num, 4, "%d", fps);
    glColor3f(0.f, 1.f, 1.f);
    glPushMatrix();
    glTranslatef(0.f, 9.f, 0.f);
    text(num);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

static void window_updater() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (input_getkeydown(GLUT_KEY_F11)) {
        glutFullScreenToggle();
    } 
    
    time_update();
    window_loop();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect_ratio = (float)window_width/window_height; 
    glOrtho(0.f, aspect_ratio*10.f, 0.f, 10.f, 0.f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    show_fps();

    glutSwapBuffers();
    glutPostRedisplay();
    if (window_cursor_ishiden) {
        glutWarpPointer(window_width / 2, window_height / 2);
    }
}

void window_init() {
    int argc = 0;
    glutInit(&argc, 0);            // Initialize GLUT
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Enable double buffered mode
    glutInitWindowSize(window_width, window_height);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutSetWindow(glutCreateWindow(window_title));
    glutReshapeFunc(resize_callback);       // Register callback handler for window re-size event
    glutDisplayFunc(window_updater);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
    glutFullScreen();
    input_init();
}

void window_do_loop() {
    glutMainLoop();
}

void window_hide_cursor() {
    glutSetCursor(GLUT_CURSOR_NONE);
    window_cursor_ishiden = true;
    
}

void window_unhide_cursor() {
    glutSetCursor(GLUT_CURSOR_INHERIT);
    window_cursor_ishiden = false;
}

void window_set_loop(void (*f) (void)) {
    window_loop = f;
}

void window_destroy() {
    glutLeaveMainLoop();
}

