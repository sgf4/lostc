#pragma once
#include <vec.h>
#include <stdbool.h>

typedef struct {
    bool is_you;
    vec3 position;
} Player;

void player_update(Player* player);
extern Player player;
