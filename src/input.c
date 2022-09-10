#include "input.h"
#include <stdio.h>
#include <GL/freeglut.h>
#include "window.h"

static uint8_t keys[256];
static vec2 mpos;
static vec2 mdirection;

static void keydown_callback(unsigned char key, int x, int y) {
    keys[key] = 1;
}

static void keyup_callback(unsigned char key, int x, int y) {
    keys[key] = 0;
}

static void specialdown_callback(int key, int x, int y) {
    if (key < 0) return;
    keys[key] = 1;
}

static void specialup_callback(int key, int x, int y) {
    if (key < 0) return;
    keys[key] = 0;
}

static void mousemove_callback(int x, int y) {
    vec2 pos = {x, y};
    mdirection = window_center;
    ivec2_subv(mdirection, pos);
    ivec2_muln(mdirection, -1);
    mpos = pos;
}

void input_init() {
    glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
    glutKeyboardFunc(keydown_callback);
    glutKeyboardUpFunc(keyup_callback);
    glutSpecialFunc(specialdown_callback);
    glutSpecialUpFunc(specialup_callback);

    //glutMouseFunc(mouse_callback);
    
    glutPassiveMotionFunc(mousemove_callback);
    glutMotionFunc(mousemove_callback);
    
}

bool input_getkey(uint8_t key) {
    return keys[key] > 0;
}

bool input_getkeydown(uint8_t key) {
    return keys[key] == 1 ? keys[key]++ : 0;
}

vec2 input_getmousedir() {
    return mdirection;
}
