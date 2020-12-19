#include "help_classes.hpp"

Point::Point(double x, double y) : x(x), y(y) {}

Point& Point::operator+=(const Point &p) 
{
    x += p.x;
    y += p.y;
    return *this;
}

Point& Point::operator-=(const Point &p) 
{
    x -= p.x;
    y -= p.y;
    return *this;
}

Point Point::operator+(const Point &p) const 
{
    Point n_p = *this;
    return n_p += p;
}

Point Point::operator-(const Point &p) const 
{
    Point n_p = *this;
    return n_p -= p;
}

Point Point::operator*(double k) const 
{
    return Point(k * x, k * y);
}

Point Point::orthogonal() const 
{
    return Point(-y, x);
}

double Point::length() const 
{
    return std::sqrt(x * x + y * y);
}

void Point::set_normal() 
{
    double len = length();
    x /= len;
    y /= len;
}

void Point::OpenGL_fit() 
{
    x *= 2;
    y *= 2;
}

std::ostream& operator<<(std::ostream &out, const Point &point)
{
    out << "x: " << point.x << ", y: " << point.y;
    return out;
}


Pixel::Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : 
    r(r), g(g), b(b), a(a) 
{}

Pixel& Pixel::operator=(const Color &color)
{
    r = static_cast<uint8_t>(color.r * 255);
    g = static_cast<uint8_t>(color.g * 255);
    b = static_cast<uint8_t>(color.b * 255);
    a = static_cast<uint8_t>(color.a * 255);

    return *this;
}


std::ostream& operator<<(std::ostream &out, const Color &color)
{
    out << color.r << " " << color.g << " " << color.b << " " << color.a;
    return out;
}