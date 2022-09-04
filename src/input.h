#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <vec.h>

#define KEY_ESC 27
#define KEY_UP 101
#define KEY_DOWN 103
#define KEY_LEFT 100
#define KEY_RIGHT 102

void input_init(void);
bool input_getkey(uint8_t key);
bool input_getkeydown(uint8_t key);
iVec2 input_getmousedir();
