#include <GL/gl.h>
#include <png.h>
#include <string.h>
#include <stdlib.h>

#include "texture.h"


Texture* current_texture;

static void read_callback(png_structp png_ptr, png_bytep data, png_size_t length) {
    unsigned char* p = png_get_io_ptr(png_ptr);
    memcpy(data, p, length);
    png_set_read_fn(png_ptr, p + length, read_callback);
}

static void error_fn(png_structp png_ptr, png_const_charp msg) {
    printf("warn: %s", msg);
}

static void warn_fn(png_structp png_ptr, png_const_charp msg) {
    printf("error: %s", msg);
}

void texture_load_fn(Texture* texture) {
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, warn_fn, error_fn);
    png_infop info = png_create_info_struct(png);

    png_set_read_fn(png, (png_voidp)texture->data, read_callback);
    png_set_sig_bytes(png, 0);
    png_read_info(png, info);

    texture->width = png_get_image_width(png, info);
    texture->height = png_get_image_height(png, info);

    //png_byte bit_depth = png_get_bit_depth(png, info);

    unsigned int row_size = png_get_rowbytes(png, info);
    png_bytep data = (png_bytep) malloc(texture->height * row_size * sizeof(png_byte));
    png_bytep row_pointers[texture->height * sizeof(png_bytep)];

    for (unsigned int i = 0; i < texture->height; i++) {
        row_pointers[texture->height-1-i] = data + (i * row_size);
    }
    png_read_image(png, row_pointers);

    int alpha;
    switch (png_get_color_type(png, info)) {
        case PNG_COLOR_TYPE_RGBA:
            alpha = GL_RGBA;
            break;
        case PNG_COLOR_TYPE_RGB:
            alpha = GL_RGB;
            break;
        default:
            printf("color type not supported\n");
            exit(1);
    }

    png_destroy_read_struct(&png, &info, NULL);

    glGenTextures(1, &texture->id); 
    glBindTexture(GL_TEXTURE_2D, texture->id); 
    //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, alpha, GL_UNSIGNED_BYTE, data); 

    free(data);
}

void texture_use(Texture* texture) {
    current_texture = texture;
    glBindTexture(GL_TEXTURE_2D, texture->id);
}

void texture_destroy(Texture* texture) {
    glDeleteTextures(1, &texture->id);
}

void texture_set_offset(Texture* texture, float offsetx, float offsety, float sizex, float sizey) {
    glPushAttrib(GL_TRANSFORM_BIT);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glTranslatef(offsetx/texture->width, 1.f-(sizey/texture->height)-(offsety/texture->height), 0.f);
    glScalef(sizex/texture->width, sizey/texture->height, 1.f);
    glPopAttrib();
}
