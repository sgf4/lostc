#include <GL/gl.h>
#include <textures/texture.h>
#include <stdio.h>
#include <window.h>
#include <textures/font.h>
#include <GL/freeglut.h>
#include <world/world.h>
#include <input.h>
#include "menu_list.h"

#include "text.h"
#include "vec.h"

void main_menu_init() {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutSetCursor(GLUT_CURSOR_INHERIT);
    glEnable(GL_BLEND);
    load_texture(&texture_font);
    printf("main_menu\n");
}

static unsigned int selected_opt = 0;

static void on_play() {
    main_menu_destroy();
    example_world_init();
    window_set_loop(example_world_update);   
}

static void on_fuck() {
}

static void on_exit() { 
    main_menu_destroy();
    window_destroy();
}

typedef struct {
    const char* str;
    void (*fn) (void);
} option_entry_t;

option_entry_t options[] = {
    {"play", on_play},
    {"fuck", on_fuck},
    {"exit", on_exit}
};

static unsigned int noptions = sizeof(options)/sizeof(option_entry_t);

void main_menu_update() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect_ratio = (float)window_width/window_height; 
    glOrtho(0.f, aspect_ratio, 0.f, 1.f, 0.f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.05f, 1.f-(0.05f*2.f), 0.f);
    glScalef(0.05f, 0.05f, 0.05f);

    if (input_getkeydown(GLUT_KEY_UP)) {
        if (selected_opt != 0) selected_opt--;
    }

    if (input_getkeydown(GLUT_KEY_DOWN)) {
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

    if (input_getkeydown('\r')) {
        options[selected_opt].fn();
    }

	//glRotatef(70.f, 0.f, 0.f, 1.f);

}

void main_menu_destroy() {
    glDisable(GL_BLEND);
    destroy_texture(&texture_font);
}

