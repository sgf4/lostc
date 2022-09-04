#include "window.h"

#include <GL/freeglut_std.h>
#include <GL/gl.h>
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

static void resize_callback(int w, int h) {
    window_width = w;
    window_height = h;
    window_center = (iVec2){w/2, h/2};
    glViewport(0, 0, w, h);
}

static void window_updater() {
    if (input_getkeydown(GLUT_KEY_F11)) {
        glutFullScreenToggle();
    }
    
    time_update();
    window_loop();
    glutSwapBuffers();
    glutPostRedisplay();
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
    input_init();
}

void window_do_loop() {
    glutMainLoop();
}

void window_set_loop(void (*f) (void)) {
    window_loop = f;
}

void window_destroy() {
    glutLeaveMainLoop();
}

