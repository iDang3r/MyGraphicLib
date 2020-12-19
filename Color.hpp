#pragma once

#include <cstdint>

double H(int hex);

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

    void inverse();

    void lighter();

    void de_lighter();

    operator uint32_t() const;
};

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