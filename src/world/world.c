#include <GL/gl.h>
#include <stdio.h>
#include "../window.h"

#include "world.h"

void world_init() {
    window_hide_cursor();
    glClearDepth(1.f);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void world_destroy() {

}

void (*world_update_f) (void);
void world_update() {
    camera_update();
    player_update(&player);
}

