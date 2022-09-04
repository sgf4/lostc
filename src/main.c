#include "textures/texture.h"
#include <textures/font.h>
#include "window.h"
#include <world/world.h>
#include <gui/menu_list.h>
#include <GL/gl.h>

int main() {
    window_init();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_BLEND);

    // load essential textures
    load_texture(&texture_font);

    main_menu_init();
    window_set_loop(main_menu_update);
    //load_world(&example_world);
    //window_set_loop(world_update);
    window_do_loop();
    main_menu_destroy();
    destroy_texture(&texture_font);
    return 0;
}
