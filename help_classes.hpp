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

    Point(double x, double y) : x(x), y(y) {}

    // void set() const 
    // {
    //     glVertex2d(x, y);
    // }

    Point& operator+=(const Point &p) 
    {
        x += p.x;
        y += p.y;
        return *this;
    }

    Point& operator-=(const Point &p) 
    {
        x -= p.x;
        y -= p.y;
        return *this;
    }

    Point operator+(const Point &p) const 
    {
        Point n_p = *this;
        return n_p += p;
    }

    Point operator-(const Point &p) const 
    {
        Point n_p = *this;
        return n_p -= p;
    }

    Point operator*(double k) const 
    {
        return Point(k * x, k * y);
    }

    Point orthogonal() const 
    {
        return Point(-y, x);
    }

    double length() const 
    {
        return std::sqrt(x * x + y * y);
    }

    void set_normal() 
    {
        double len = length();
        x /= len;
        y /= len;
    }

    void OpenGL_fit() 
    {
        x *= 2;
        y *= 2;
    }

};

std::ostream& operator<<(std::ostream &out, const Point &point)
{
    out << "x: " << point.x << ", y: " << point.y;
    return out;
}

#pragma pack(push, 1)
class Pixel
{
public:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xFF) : 
        r(r), g(g), b(b), a(a) 
    {}

    Pixel& operator=(const Color &color)
    {
        r = static_cast<uint8_t>(color.r * 255);
        g = static_cast<uint8_t>(color.g * 255);
        b = static_cast<uint8_t>(color.b * 255);
        a = static_cast<uint8_t>(color.a * 255);

        return *this;
    }

};
#pragma pack(pop)

std::ostream& operator<<(std::ostream &out, const Color &color)
{
    out << color.r << " " << color.g << " " << color.b << " " << color.a;
    return out;
}

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