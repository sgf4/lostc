#pragma once

typedef struct {
    const unsigned char* data;
    unsigned int id;
    unsigned int width;
    unsigned int height;
} Texture;

#define EXTERN_TEXTURE(name) \
extern const unsigned char texture_##name##_start[]; \
extern Texture texture_##name

#define TEXTURE(name) \
extern const unsigned char* texture_##name##_start[]; \
Texture texture_##name

#define texture_load(name) \
(name)->data = *(name##_start); \
texture_load_fn(name)

void texture_load_fn(Texture* texture);
void texture_destroy(Texture* texture);
void texture_set_offset(Texture* texture, float offsetx, float offsety, float sizex, float sizey);
void texture_use(Texture* texture);
extern Texture* current_texture;
