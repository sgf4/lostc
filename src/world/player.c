#include "player.h"
#include "camera.h"

#include <input.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

Player player = {
    .is_you=true
};

void player_update(Player* player) {
    if (player->is_you) {
        vec2 v = input_getmousedir();
        camera.direction.x += v.y * camera.sensibility;
        camera.direction.y += v.x * camera.sensibility;

        float dir_x = cos(camera.direction.y * (3.14159265 / 180)) * time_delta * 5.f;
        float dir_z = sin(camera.direction.y * (3.14159265 / 180)) * time_delta * 5.f;

        if (input_getkey('w')) {
            player->position.x -= dir_z;
            player->position.z += dir_x;
        } 
        if (input_getkey('s')) {
            player->position.x += dir_z;
            player->position.z -= dir_x;
        }
        if (input_getkey('a')) {
            player->position.x += dir_x;
            player->position.z += dir_z;
        }
        if (input_getkey('d')) {
            player->position.x -= dir_x;
            player->position.z -= dir_z;
        }

        camera.position = player->position;
    }
}

