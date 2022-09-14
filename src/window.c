#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>

#include "window.h"
#include "gui/text.h"
#include "input.h"
#include "time.h"

int window_width = 640;
int window_height = 480;
ivec2 window_center;
const char* window_title = "omg";
bool window_cursor_ishiden;
bool window_fullscreen;
bool window_vsync = true;
GLFWwindow* window_glfw;

static void (*window_update_fn) (void);

static void resize_callback(GLFWwindow* wnd, int w, int h) {
    window_width = w;
    window_height = h;
    window_center = (ivec2){w/2, h/2};
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

void window_set_fullscreen(bool v) {
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    static ivec2 lastpos = {0, 0};
    static ivec2 lastsize = {0, 0};
    if (v) {
        glfwGetWindowPos(window_glfw, &lastpos.x, &lastpos.y);
        glfwGetWindowSize(window_glfw, &lastsize.x, &lastsize.y);
        glfwSetWindowMonitor(window_glfw, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    } else {
        glfwSetWindowMonitor(window_glfw, NULL, lastpos.x, lastpos.y, lastsize.x, lastsize.y, mode->refreshRate);
    }
    window_fullscreen = v;
}

void window_set_vsync(bool v) {
    glfwSwapInterval(v);
    window_vsync = v;
}

void window_update() {
    while (!glfwWindowShouldClose(window_glfw)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (input_getkeydown(KEY_F11)) {
            window_set_fullscreen(!window_fullscreen);
        }
        
        time_update();
        window_update_fn();

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        float aspect_ratio = (float)window_width/window_height; 
        glOrtho(0.f, aspect_ratio*10.f, 0.f, 10.f, 0.f, 100.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        show_fps();

        /* Swap front and back buffers */
        glfwSwapBuffers(window_glfw);

        /* Poll for and process events */
        glfwPollEvents();
    }
}

void window_init() {
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: glfwInit()\n");
    }

    // OpenGL 1.0
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    window_glfw = glfwCreateWindow(window_width, window_height, window_title, NULL, NULL);
    if (!window_glfw) {
        glfwTerminate();
        fprintf(stderr, "ERROR: creating window\n");
        exit(1);
    }

    glfwMakeContextCurrent(window_glfw);
    glfwSetWindowSizeCallback(window_glfw, resize_callback);

    input_init();
}

void window_hide_cursor() {
    glfwSetInputMode(window_glfw, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    window_cursor_ishiden = true;   
}

void window_unhide_cursor() {
    glfwSetInputMode(window_glfw, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    window_cursor_ishiden = false;
}

void window_set_update(void (*fn) (void)) {
    window_update_fn = fn;
}

void window_destroy() {
    glfwDestroyWindow(window_glfw);
    glfwTerminate();
}

void window_close() {
    glfwSetWindowShouldClose(window_glfw, 1);
}