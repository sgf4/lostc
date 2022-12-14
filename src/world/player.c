#include <math.h>
#include <stdio.h>

#include "player.h"
#include "camera.h"
#include "../input.h"
#include "../time.h"



Player player = {
    .is_you=true
};

void player_update(Player* player) {
    if (player->is_you) {
        ivec2 v = input_getmousedir();
        camera.direction.x += v.y * camera.sensibility * time_delta;
        camera.direction.y += v.x * camera.sensibility * time_delta;

        float dir_x = cos(camera.direction.y * (3.14159265 / 180)) * time_delta * 5.f;
        float dir_z = sin(camera.direction.y * (3.14159265 / 180)) * time_delta * 5.f;

        if (input_getkey(KEY_W)) {
            player->position.x -= dir_z;
            player->position.z += dir_x;
        } 
        if (input_getkey(KEY_S)) {
            player->position.x += dir_z;
            player->position.z -= dir_x;
        }
        if (input_getkey(KEY_A)) {
            player->position.x += dir_x;
            player->position.z += dir_z;
        }
        if (input_getkey(KEY_D)) {
            player->position.x -= dir_x;
            player->position.z -= dir_z;
        }

        camera.position = player->position;
    }
}

