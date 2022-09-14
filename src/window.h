#pragma once
#include "vec.h"
#include <stdbool.h>

struct GLFWwindow;
typedef struct GLFWwindow GLFWwindow;

extern GLFWwindow* window_glfw;
extern int window_width;
extern int window_height;
extern const char* window_title;
extern bool window_vsync;

void window_init(void);
void window_update();
void window_set_update(void (*fn) (void));
void window_close(void);
void window_destroy(void);
void window_hide_cursor(void);
void window_unhide_cursor(void);
void window_set_fullscreen(bool);
void window_set_vsync(bool);
