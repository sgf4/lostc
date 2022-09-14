#include <stdio.h>
#include <GLFW/glfw3.h>

#include "input.h"
#include "window.h"

static uint8_t keys[512];
static ivec2 mpos;
static ivec2 mdirection;

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    keys[key] = action;
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        keys[MOUSE_LEFT] = action;
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        keys[MOUSE_RIGHT] = action;
    }
}

static void cursor_position_callback(GLFWwindow* window, double x, double y) {
    ivec2 pos = {x, y};
    mdirection = mpos;
    ivec2_subv(mdirection, pos);
    ivec2_muln(mdirection, -1);
    mpos = pos;
}

void input_init() {
    glfwSetKeyCallback(window_glfw, key_callback);
    glfwSetCursorPosCallback(window_glfw, cursor_position_callback);
    glfwSetMouseButtonCallback(window_glfw, mouse_button_callback);

    //glutMouseFunc(mouse_callback);
    
}

bool input_getkey(unsigned int key) {
    return keys[key] > 0;
}

bool input_getkeydown(unsigned int key) {
    return keys[key] == 1 ? keys[key]++ : 0;
}

ivec2 input_getmousedir() {
    ivec2 m = mdirection;
    mdirection = (ivec2) {0, 0};
    return m;
}
