#include "Color.hpp"

#include <cstdint>

double H(int hex) {
    return static_cast<double>(hex) / 255; 
}

const double Color::light_const = 1.21;

void Color::inverse()
{
    r = 1 - r;
    g = 1 - g;
    b = 1 - b;
}

void Color::lighter()
{
    r *= light_const;
    g *= light_const;
    b *= light_const;
}

void Color::de_lighter()
{
    r /= light_const;
    g /= light_const;
    b /= light_const;
}

Color::operator uint32_t() const
{
    int ret = 0;
    uint8_t* p = reinterpret_cast<uint8_t*>(&ret);
     
    p[0] = static_cast<uint8_t>(r * 255);
    p[1] = static_cast<uint8_t>(g * 255);
    p[2] = static_cast<uint8_t>(b * 255);
    p[3] = static_cast<uint8_t>(a * 255);

    return ret;
}