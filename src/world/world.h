#pragma once
#include "player.h"
#include "camera.h"

void world_init(void);
void world_update(void);
void world_destroy(void);
void window_set_loop(void(*f)(void));
void window_hide_cursor(void);
void window_unhide_cursor(void);
extern void (*world_update_f) (void);


#define def_world(name) \
void name##_init(void); \
void name##_update(void); \
void name##_destroy(void)

// World_list
def_world(example_world);
