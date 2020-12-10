#include "Color.hpp"

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