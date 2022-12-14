#include <GL/gl.h>

#include <stdio.h>
#include "../texture.h"
#include "../window.h"
#include "../world/world.h"
#include "../input.h"
#include "menu_list.h"

#include "text.h"
#include "../vec.h"

void main_menu_init() {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    window_set_update(main_menu_update);
    window_unhide_cursor();
}

static unsigned int selected_opt = 0;

static void on_play() {
    main_menu_destroy();
    example_world_init();
}

char vsync_str[] = "vsync on ";
static void on_vsync() {
    window_set_vsync(!window_vsync);
    if (window_vsync) {
        vsync_str[7] = 'n'; 
        vsync_str[8] = ' ';
    } else {
        vsync_str[7] = 'f'; 
        vsync_str[8] = 'f';
    }
}

static void on_exit() { 
    main_menu_destroy();
    window_close();
}

typedef struct {
    const char* str;
    void (*fn) (void);
} option_entry_t;

option_entry_t options[] = {
    {"play", on_play},
    {vsync_str, on_vsync},
    {"exit", on_exit}
};

static unsigned int noptions = sizeof(options)/sizeof(option_entry_t);

void main_menu_update() {
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0.f, 5.f, 0.f);
    //glScalef(0.5f, 0.5f, 0.5f);

    if (input_getkeydown(KEY_UP)) {
        if (selected_opt != 0) selected_opt--;
    } else if (input_getkeydown(KEY_DOWN)) {
        if (selected_opt != noptions-1) selected_opt++;
    } 
    
    for (unsigned int i=0; i<noptions; i++) {
        if (i == selected_opt) {
            glColor3f(1.f, 0.f, 0.f);
        } else {
            glColor3f(1.f, 1.f, 1.f);
        }
        text(options[i].str);
        glTranslatef(0.f, -2.f, 0.f);
    }
    glPopMatrix();

    if (input_getkeydown(KEY_ENTER)) {
        options[selected_opt].fn();
    }
    glDisable(GL_TEXTURE_2D);
	//glRotatef(70.f, 0.f, 0.f, 1.f);

}

void main_menu_destroy() {
}

