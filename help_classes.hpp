#pragma once

#define w(x) std::cout << #x << ": " << x << std::endl; 

double H(int hex) {
    return static_cast<double>(hex) / 255; 
}

class Point 
{
public:

    double x;
    double y;

    Point(double x, double y) : x(x), y(y) {}

    void set() const 
    {
        glVertex2d(x, y);
    }

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

class Color 
{
public:
    static const double light_const;
    
    double r;
    double g;
    double b;
    double a;

    explicit Color(double r, double g, double b, double a = 1.0) : r(r),    g(g),    b(b),    a(a)    {}
    explicit Color(int    r, int    g, int    b, int    a = 255) : r(H(r)), g(H(g)), b(H(b)), a(H(a)) {} 

    void set() const 
    {
        glColor3d(r, g, b);
    }

    void inverse()
    {
        r = 1 - r;
        g = 1 - g;
        b = 1 - b;
    }

    void lighter()
    {
        r *= light_const;
        g *= light_const;
        b *= light_const;
    }

    void de_lighter()
    {
        r /= light_const;
        g /= light_const;
        b /= light_const;
    }

};
const double Color::light_const = 1.4;

std::ostream& operator<<(std::ostream &out, const Color &color)
{
    out << color.r << " " << color.g << " " << color.b << " " << color.a << std::endl;
    return out;
}

namespace COLORS
{
    const Color red             (1.0,       0.0,        0.0);
    const Color green           (0.0,       1.0,        0.0);
    const Color blue            (0.0,       0.0,        1.0);
    const Color black           (0.0,       0.0,        0.0);
    const Color white           (1.0,       1.0,        1.0);

    const Color cyan            (H(0x0),    H(0x99),    H(0x99));

    const Color clear           (1.0,       1.0,        1.0,        0.0);

    const Color window          (1.0,       0.0,        0.0);
    const Color sys_window      (0.357,     0.357,      0.357);
    const Color sys_window_top  (0.16,      0.16,       0.16);
    const Color button          (H(0xFF),   H(0x73),    H(0x73));

    const Color main_background (H(0xFF),   H(0xD0),    H(0x7B),    0.3);
    
} // namespace COLORS
