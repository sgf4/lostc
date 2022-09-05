#include "text.h"
#include <string.h>
#include <textures/texture.h>
#include <GL/gl.h>
#include <textures/font.h>

static const unsigned char font_size_map[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//     !  "  #  $  %  &  '  (  )  *  +  ,  -  .  /
    3, 2, 4, 5, 5, 5, 5, 2, 5, 5, 2, 4, 2, 4, 1, 5,
//  0  1  2  3  4  5  6  7  8  9  :     <  =  >  ?
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 2, 5, 5, 5, 5, 5, 
//  @  A  B  C  D  E  F  G  H  I  J  K  L  M  N  O
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
//  P  Q  R  S  T  U  V  W  X  Y  Z  [  \  ]  ^  _
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
//  `  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o
    5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 5, 5, 2, 5, 5, 5, 
//  p  q  r  s  t  u  v  w  x  y  z  {  |  }  ~  
    5, 5, 5, 5, 3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
};

void text(const char* text) {
    use_texture(&texture_font);
    glPushAttrib(GL_TRANSFORM_BIT | GL_ENABLE_BIT);
    use_texture(&texture_font);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    for (int i=0; text[i] != '\0'; i++) {
        unsigned char c = text[i];
        int columns = 16;
        int px = c%columns*8;
        int py = c/columns*8;
        int size = font_size_map[c];
	    set_offset(current_texture, px, py, size, 8);
        float sizef = size/5.f;
		glBegin(GL_QUADS);
			glTexCoord2d(0.f, 0.f);
			glVertex2d(0.f, 0.f);
			glTexCoord2d(1.f, 0.f);
			glVertex2d(sizef, 0.f);
			glTexCoord2d(1.f, 1.f);
			glVertex2d(sizef, 1.f);
			glTexCoord2d(0.f, 1.f);
			glVertex2d(0.f, 1.f);
		glEnd();
		glTranslatef(sizef + 0.3f, 0.f, 0.f);
    }
    glPopMatrix();
    glPopAttrib();
}
