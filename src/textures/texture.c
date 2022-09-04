#include "texture.h"
#include <GL/gl.h>

Texture* current_texture;

void load_texture(Texture* texture) {
    glGenTextures(1, &texture->id); 
    glBindTexture(GL_TEXTURE_2D, texture->id); 
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->data); 
}
void use_texture(Texture* texture) {
    current_texture = texture;
    glBindTexture(GL_TEXTURE_2D, texture->id);
}

void destroy_texture(Texture* texture) {
    glDeleteTextures(1, &texture->id);
}

void set_offset(Texture* texture, float offsetx, float offsety, float sizex, float sizey) {
    glPushAttrib(GL_TRANSFORM_BIT);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glTranslatef(offsetx/texture->width, 1.f-(sizey/texture->height)-(offsety/texture->height), 0.f);
    glScalef(sizex/texture->width, sizey/texture->height, 1.f);
    glPopAttrib();
}
