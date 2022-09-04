#pragma once


#define def_menu(name) \
void name##_init(); \
void name##_update(); \
void name##_destroy()

def_menu(main_menu);
