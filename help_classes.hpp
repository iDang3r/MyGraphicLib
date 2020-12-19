// #pragma once
#ifndef HELP_CLASSES_HPP
#define HELP_CLASSES_HPP

#include <iostream>
#include <cmath>

#include "Color.hpp"

#define ww(x) std::cout << #x << ": " << x << std::endl; 
#define ws(x) std::cout << x << std::endl;

#define SQR(x) ((x) * (x))

class Point 
{
public:

    double x;
    double y;

    Point(double x, double y);

    Point& operator+=(const Point &p);

    Point& operator-=(const Point &p);

    Point operator+(const Point &p) const;

    Point operator-(const Point &p) const;

    Point operator*(double k) const;

    Point orthogonal() const;

    double length() const;

    void set_normal();

    void OpenGL_fit();

};

std::ostream& operator<<(std::ostream &out, const Point &point);

#pragma pack(push, 1)
class Pixel
{
public:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xFF);

    Pixel& operator=(const Color &color);

};
#pragma pack(pop)

std::ostream& operator<<(std::ostream &out, const Color &color);

struct Pixel_array
{
    Pixel* start  = NULL;
    int    width  = 0;
    int    height = 0; 
};

struct Visible_part 
{
    int x       = 0;
    int y       = 0;
    int width   = 0;
    int height  = 0;
};


#endif // HELP_CLASSES_HPP