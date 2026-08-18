#include <iostream>
#include <fstream>
#include "olive.h"

#define WIDTH 800
#define HEIGHT 600

#define COLS 8
#define ROWS 6
#define CELL_WIDTH (WIDTH / COLS)
#define CELL_HEIGHT (HEIGHT / ROWS)

static std::vector<std::uint32_t> pixels(WIDTH *HEIGHT);

float lerp(float a, float b, float t)
{
    return a + (b - a) * t;
}

bool lines_example()
{
    olive_fill(pixels, WIDTH, HEIGHT, 0xFF404040);

    olive_draw_line(pixels, WIDTH, HEIGHT, 0, 0, WIDTH, HEIGHT, 0xFF202020);
    olive_save_into_ppm_file(pixels, WIDTH, HEIGHT, "./example/lines.ppm");
    return true;
}
bool checker_example()
{
    olive_fill(pixels, WIDTH, HEIGHT, 0xFF0000FF);
    for (int y = 0; y < ROWS; y++)
    {
        for (int x = 0; x < COLS; x++)
        {
            std::uint32_t color = 0xFF202020;
            if ((x + y) % 2 == 0)
            {
                color = 0xFF404040;
            }
            else
            {
                color = 0xFF202020;
            }
            olive_fill_rect(pixels, WIDTH, HEIGHT, x * CELL_WIDTH, y * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, color);
        }
    }
    olive_save_into_ppm_file(pixels, WIDTH, HEIGHT, "./example/checker.ppm");
    return true;
}

bool circle_example()
{
    olive_fill(pixels, WIDTH, HEIGHT, 0xFFFFFFFF);

    
    olive_fill_circle(pixels, WIDTH, HEIGHT, WIDTH / 2, HEIGHT / 2, HEIGHT / 4, 0xFF202020);
        
    
    olive_save_into_ppm_file(pixels, WIDTH, HEIGHT, "./example/circle.ppm");
    return true;
}

bool triangle_example()
{
    olive_fill(pixels, WIDTH, HEIGHT, 0xFFFFFFFF);
    olive_fill_triangle(pixels, WIDTH, HEIGHT, WIDTH / 2, HEIGHT / 8, WIDTH / 2 + 200, HEIGHT / 8, WIDTH * 3 / 4, HEIGHT * 7 / 8, 0xBBAB4242);
    olive_fill_triangle(pixels, WIDTH, HEIGHT, WIDTH / 2, 0, 0, HEIGHT - 1, WIDTH - 1, HEIGHT - 1, 0xBBA5C8F6);
    olive_save_into_ppm_file(pixels, WIDTH, HEIGHT, "./example/triangle.ppm");
    return true;
}
int main()
{
    if (!checker_example())
        return -1;
    if (!circle_example())
        return -1;
    if (!lines_example())
        return -1;
    if (!triangle_example())
        return -1;
    return 0;
}
