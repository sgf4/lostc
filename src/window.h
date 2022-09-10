#pragma once
#include <vec.h>

extern int window_width;
extern int window_height;
extern vec2 window_center;
extern const char* window_title;
extern void (*window_loop) (void);
extern void (*window_on_close) (void);

void window_init(void);
void window_do_loop(void);
void window_destroy(void);
void window_set_loop(void (*fl)(void));
