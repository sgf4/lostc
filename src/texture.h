#pragma once

typedef struct {
    const unsigned char* data;
    unsigned int id;
    unsigned int width;
    unsigned int height;
} Texture;

#define TEXTURE(name) \
extern Texture texture_##name

void texture_load(Texture* texture);
void texture_destroy(Texture* texture);
void texture_set_offset(Texture* texture, float offsetx, float offsety, float sizex, float sizey);
void texture_use(Texture* texture);
extern Texture* current_texture;
