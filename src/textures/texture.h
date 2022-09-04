#pragma once

typedef struct {
    int width;
    int height;
    unsigned int id;
    const unsigned char* data;
} Texture;

void load_texture(Texture* texture);
void destroy_texture(Texture* texture);
void set_offset(Texture* texture, float offsetx, float offsety, float sizex, float sizey);
void use_texture(Texture* texture);
extern Texture* current_texture;
