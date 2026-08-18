#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "olive.h"

#define WIDTH 800
#define HEIGHT 600

float angle = 0;
static std::vector<std::uint32_t> pixels(WIDTH * HEIGHT);

void rotate_point(int* x,int* y){
    int dx = *x - WIDTH / 2;
    int dy = *y - HEIGHT / 2;
    float meg = sqrtf(dx*dx+dy*dy);
    float dir = atan2f(dy, dx) + angle;
    *x = cosf(dir)*meg + WIDTH / 2;
    *y = sinf(dir)*meg + HEIGHT / 2;
}

uint32_t* render(float dt) {

    angle += 2 * M_PI * dt;
    olive_fill(pixels, WIDTH, HEIGHT, 0xFF181818);

    return pixels.data();
}