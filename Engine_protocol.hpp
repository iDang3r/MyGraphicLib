#pragma once

#include "help_classes.hpp"
#include "Event.hpp"

class Engine_protocol 
{
private:
public:
    static constexpr int        window_width    = 1920;
    static constexpr int        window_height   = 1080;
    static constexpr double     window_w_to_h   = (double)window_width / window_height;

    static constexpr double     Pi              = M_PI;
    static constexpr double     angle_circle_x  = 0.007;
    static constexpr double     angle_circle_y  = angle_circle_x * window_w_to_h;

    static int init()                                                       {}
    static int terminate()                                                  {}

    static int is_run()                                                     {}

    static void draw_rectangle(const Point&, double, double, const Color)   {}
    static void draw_square   (const Point&, double, const Color&)          {}
    static void draw_circle   (const Point&, double, const Color&)          {} 
    
};