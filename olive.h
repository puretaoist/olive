#ifndef OLIVE_H
#define OLIVE_H

#include <cstdint>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>

float lerp(float a, float b, float t)
{
    return a + (b - a) * t;
}

void sort_triangle_points_by_y(int& x1, int& y1,
                               int& x2, int& y2,
                               int& x3, int& y3) {
    if (y1 > y2) { std::swap(x1, x2); std::swap(y1, y2); }
    if (y2 > y3) { std::swap(x2, x3); std::swap(y2, y3); }
    if (y1 > y2) { std::swap(x1, x2); std::swap(y1, y2); }
}

typedef enum 
{
    COMP_RED=0,
    COMP_GREEN,
    COMP_BLUE,
    COMP_ALPHA,
    COUNT_COMPS,
} Comp_Index;

void unpack_rgba32(std::uint32_t c,std::uint8_t comp[COUNT_COMPS]){
    for (size_t i = 0; i < COUNT_COMPS;++i){
        comp[i] = c & 0xFF;
        c >>= 8;
    }
}

std::uint32_t pack_rgba32(std::uint8_t comp[COUNT_COMPS]){
    std::uint32_t result = 0;
    for (size_t i = 0; i < COUNT_COMPS;++i){
        result |= comp[i] << (8 * i);
    }
    return result;
}
std::uint8_t olive_mix_comps(std::uint16_t c1,std::uint16_t c2,std::uint16_t a){
    return c1 + (c2 - c1) * a / 255;
}

std::uint32_t olive_mix_color(std::uint32_t c1,std::uint32_t c2){
    std::uint8_t comp1[COUNT_COMPS];
    unpack_rgba32(c1,comp1);

    std::uint8_t comp2[COUNT_COMPS];
    unpack_rgba32(c2, comp2);

    for (size_t i = 0; i < COMP_ALPHA;i++){
        comp1[i] = olive_mix_comps(comp1[i], comp2[i], comp2[COMP_ALPHA]);
    }

    return pack_rgba32(comp1);
}

void olive_fill(std::vector<std::uint32_t>& pixels,size_t width,size_t height,std::uint32_t color){
    for (size_t i = 0;i< width*height;i++){
        pixels[i] = color;
    }
}

void olive_fill_rect(std::vector<std::uint32_t>& pixels,size_t pixels_width,size_t pixels_height,
                     int x0,int y0,size_t w,size_t h,
                     std::uint32_t color){
    for (int dy = 0; dy < h;++dy){
        int y = y0 + dy;
        if(y>=0 && y < pixels_height){
            for (int dx = 0; dx < w;++dx){
                int x = x0 + dx;
                if(x>=0 && x<pixels_width){
                    pixels[y*pixels_width + x] = olive_mix_color(pixels[y*pixels_width + x],color);
                }
            }
    }
}
}

void olive_draw_line(std::vector<std::uint32_t> &pixels, size_t pixels_width, size_t pixels_height,
                     int x1, int y1, 
                     int x2, int y2, 
                     std::uint32_t color)
{
    if (x1!=x2)
    {
        if (x1 > x2)
            std::swap(x1, x2);
        for (int x = x1; x <= x2; x++)
        {
            if (0 <= x && x < (int)pixels_width)
            {
                int sy1 = (y2 - y1) * (x-x1) / (x2 - x1) + y1;
                int sy2 = (y2 - y1) * (x + 1 - x1) / (x2 - x1) + y1;
                if (sy1 > sy2)
                    std::swap(sy1, sy2);
                for (int y = sy1; y <= sy2; y++)
                {
                    if (0 <= y && y < (int)pixels_height)
                    {
                        pixels[y*pixels_width + x] = olive_mix_color(pixels[y*pixels_width + x],color);
                    }
                }
            }
        }
    }
    else
    {
        int x = x1;
        if (0 <= x && x < (int)pixels_width)
        {
            if (y1 > y2)
                std::swap(y1, y2);
            for (int y = y1; y <= y2; y++)
            {
                if (0 <= y && y < (int)pixels_height)
                {
                    pixels[y*pixels_width + x] = olive_mix_color(pixels[y*pixels_width + x],color);
                }
            }
        }
    }
}

void olive_fill_circle(std::vector<std::uint32_t> &pixels, size_t pixels_width, size_t pixels_height,
                       int cx, int cy, int r, 
                       std::uint32_t color)
{
    int x1 = cx - r;
    int y1 = cy - r;
    int x2 = cx + r;
    int y2 = cy + r;
    for (int y = y1-1; y <= y2+1; y++)
    {
        if (0 <= y && y < (int)pixels_height)
        {
            for (int x = x1-1; x <= x2+1; x++)
            {
                if (0 <= x && x < (int)pixels_width)
                {
                    int dx = x - cx;
                    int dy = y - cy;
                    if (dx * dx + dy * dy < r * r)
                    {
                    pixels[y*pixels_width + x] = olive_mix_color(pixels[y*pixels_width + x],color);
                    }
                }
            }
        }
    }
}

void olive_fill_triangle(std::vector<std::uint32_t> &pixels, size_t pixels_width, size_t pixels_height,
                         int x1, int y1, 
                         int x2 ,int y2, 
                         int x3 ,int y3, 
                         std::uint32_t color)
{
    sort_triangle_points_by_y(x1, y1, x2, y2, x3, y3);

    int dx12 = x2 - x1;
    int dy12 = y2 - y1;
    int dx13 = x3 - x1;
    int dy13 = y3 - y1;

    for (int y = y1; y <= y2;y++){
        if(0<=y&&y<(size_t) pixels_height){
            int s1 = dy12 != 0 ? (y - y1) * dx12 / dy12 + x1 : x1;
            int s2 = dy13 != 0 ? (y - y1) * dx13 / dy13 + x1 : x1;
            if(s1>s2)std::swap(s1, s2);
            for (int x = s1; x <= s2;x++){
                if(0<=x&&x<(size_t)pixels_width){
                    pixels[y*pixels_width + x] = olive_mix_color(pixels[y*pixels_width + x],color);
                }
            }
        }
    }

    int dx32 = x2 - x3;
    int dy32 = y2 - y3;
    int dx31 = x1 - x3;
    int dy31 = y1 - y3;

    for (int y = y2; y <= y3;y++){
        if(0<=y&&y<(size_t) pixels_height){
            int s1 = dy32 != 0 ? (y - y3) * dx32 / dy32 + x3 : x3;
            int s2 = dy31 != 0 ? (y - y3) * dx31 / dy31 + x3 : x3;
            if(s1>s2)std::swap(s1, s2);
            for (int x = s1; x <= s2;x++){
                if(0<=x&&x<(size_t)pixels_width){
                    pixels[y*pixels_width + x] = olive_mix_color(pixels[y*pixels_width + x],color);
                }
            }
        }
    }
}

int olive_save_into_ppm_file(const std::vector<std::uint32_t>& pixels,size_t width,size_t height,const std::string& filename){
    std::ofstream f(filename, std::ios::binary);
    std::vector<uint8_t> rgb(width * height * 3);
    for (size_t i = 0; i < width * height; ++i) {
        uint32_t p = pixels[i];
        rgb[i*3 + 0] = (p >> 0) & 0xFF;
        rgb[i*3 + 1] = (p >> 8) & 0xFF;
        rgb[i*3 + 2] = (p >> 16) & 0xFF;
    }
    f << "P6\n" << width << " " << height << "\n255\n";
    f.write(reinterpret_cast<const char*>(rgb.data()), rgb.size());
    return f.good() ? 0 : -1;
}

#endif // OLIVE_H