#pragma once

typedef struct {
    int width;
    int height;
    unsigned int id;
    const unsigned char* data;
} Texture;

void texture_load(Texture* texture);
void texture_destroy(Texture* texture);
void texture_set_offset(Texture* texture, float offsetx, float offsety, float sizex, float sizey);
void texture_use(Texture* texture);
extern Texture* current_texture;
