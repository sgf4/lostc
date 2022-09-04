#include "window.h"
#include <world/world.h>
#include <gui/menu_list.h>
#include <GL/gl.h>

int main() {
    window_init();

    glEnable(GL_TEXTURE_2D);

    main_menu_init();
    window_set_loop(main_menu_update);
    //load_world(&example_world);
    //window_set_loop(world_update);
    window_do_loop();
    main_menu_destroy();
    return 0;
}
