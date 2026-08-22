#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "olive.h"

#define WIDTH 800
#define HEIGHT 600
#define GRID_COUNT 10
#define GRID_PAD 50
#define GRID_SIZE ((GRID_COUNT-1) * GRID_PAD)

float angle = 0;
static std::vector<std::uint32_t> pixels(WIDTH * HEIGHT);

uint32_t* render(float dt) {

    angle += 0.25 * M_PI * dt;
    float cosA = cosf(angle);
    float sinA = sinf(angle);
    olive_fill(pixels, WIDTH, HEIGHT, 0xFF181818);

    for (int ix = 0; ix < GRID_COUNT;++ix){
        for (int iy = 0; iy < GRID_COUNT;++iy){
            for (int iz = 0; iz < GRID_COUNT;++iz){
                float x = ix * GRID_PAD - GRID_SIZE / 2;
                float y = iy * GRID_PAD - GRID_SIZE / 2;
                float z = iz * GRID_PAD + 0.5;

                float cx = 0.0;
                float cz = 0.5 + GRID_SIZE / 2;

                float dx = x - cx;
                float dz = z - cz;

                // 应用旋转矩阵（2D 旋转）
                float rx = dx * cosA + dz * sinA;
                float rz = -dx * sinA + dz * cosA;
                x = rx + cx;
                z = rz + cz;


                x /= z;
                y /= z;
                olive_fill_circle(pixels, WIDTH, HEIGHT, (x + 1) / 2 * WIDTH, (y + 1) / 2 * HEIGHT, 20, 0xFF202020);
            }
        }
    }
        return pixels.data();
}