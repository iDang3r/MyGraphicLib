// #pragma once
#ifndef HELP_CLASSES_HPP
#define HELP_CLASSES_HPP

#define ww(x) std::cout << #x << ": " << x << std::endl; 
#define ws(x) std::cout << x << std::endl;

#define SQR(x) ((x) * (x))

double H(int hex) {
    return static_cast<double>(hex) / 255; 
}

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

    // void set() const 
    // {
    //     glColor3d(r, g, b);
    // }

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

    sf::Color sf() const
    {
        return sf::Color   (static_cast<uint8_t>(r * 255),
                            static_cast<uint8_t>(g * 255),
                            static_cast<uint8_t>(b * 255),
                            static_cast<uint8_t>(a * 255));
    }

};
const double Color::light_const = 1.21;

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

namespace COLORS
{
    const Color red             (0.8,       0.0,        0.0);
    const Color green           (0.0,       0.8,        0.0);
    const Color blue            (0.0,       0.0,        0.8);
    const Color black           (0.0,       0.0,        0.0);
    const Color white           (1.0,       1.0,        1.0);

    const Color cyan            (H(0x0),    H(0x99),    H(0x99));

    const Color clear           (1.0,       1.0,        1.0,        0.0);

    const Color window          (1.0,       0.0,        0.0);
    const Color sys_window      (0.357,     0.357,      0.357);
    const Color sys_window_top  (0.16,      0.16,       0.16);
    const Color button          (H(0xFF),   H(0x5F),    H(0x5F));

    const Color scroll_back     (H(0x34),   H(0x35),    H(0x64));
    const Color scroll_slider   (H(0x9A),   H(0x7C),    H(0xAD));

    const Color tool_manager_fr (H(0xBF),   H(0xE5),    H(0xE0));
    const Color tool_manager    (H(0xE6),   H(0xD5),    H(0x97));

    const Color tool            (H(0x78),   H(0xB8),    H(0xB2));

    const Color painter         (H(0x96),   H(0xB5),    H(0x8A));

    const Color main_background (H(0xFF),   H(0xD0),    H(0x7B),    0.3);
    
} // namespace COLORS

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