#include "model.h"
#include <GL/gl.h>


void draw_model(const Model* model) {
    glBegin(GL_TRIANGLES);
    for (unsigned int i=0; i<model->nprimitives; i++) {
        const Primitive* p = &model->primitives[i];
        for (unsigned int j=0; j<p->nfaces; j++) {
            const Face* f = &p->faces[j];
            glNormal3f(f->a.normal.x, f->a.normal.y, f->a.normal.z);
            glVertex3f(f->a.position.x, f->a.position.y, f->a.position.z);
            glNormal3f(f->b.normal.x, f->b.normal.y, f->b.normal.z);
            glVertex3f(f->b.position.x, f->b.position.y, f->b.position.z);
            glNormal3f(f->c.normal.x, f->c.normal.y, f->c.normal.z);
            glVertex3f(f->c.position.x, f->c.position.y, f->c.position.z);
        }
    }
    glEnd();
}
