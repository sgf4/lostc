#include <GLFW/glfw3.h>
#include "time.h"

float time_delta;
float time_now;
unsigned int fps;

void time_update() {
    double now = glfwGetTime();
    
    static int next_t = 0;
    static int fcount = 0;
    time_delta = now-time_now;
    time_now = now;

    if (time_now >= next_t) {
        fps = fcount;
        fcount = 0;
        next_t = time_now+1;
    }
    fcount++;
}
