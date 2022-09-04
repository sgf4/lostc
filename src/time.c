#include "time.h"
#include <GL/freeglut.h>
#include <stdio.h>

float time_delta;
float time_now;

void time_update() {
    double now = glutGet(GLUT_ELAPSED_TIME) / 1000.0;

    static int next_t = 0;
    static int fps = 0;
    time_delta = now-time_now;
    time_now = now;

    if (time_now >= next_t) {
        printf("%d\n", fps);
        fps = 0;
        next_t = time_now+1;
    }
    fps++;
}