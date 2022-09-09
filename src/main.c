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
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    // load essential textures
    texture_load(&texture_font);

    main_menu_init();
    window_set_loop(main_menu_update);
    //load_world(&example_world);
    //window_set_loop(world_update);
    window_do_loop();
    main_menu_destroy();
    texture_destroy(&texture_font);
    return 0;
}
