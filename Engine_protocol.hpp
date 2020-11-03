#pragma once

#include "help_classes.hpp"
#include "Event.hpp"

class Engine_protocol 
{
private:
public:
    static  int     window_width;//    = 1920;
    static  int     window_height;//   = 1080;
    static  double  window_w_to_h;//  = (double)window_width / window_height;

    static  double  angle_circle_x;//  = 0.007;
    static  double  angle_circle_y;// = angle_circle_x * window_w_to_h;

    static  constexpr double Pi = M_PI;

    static  int init()                                                       {}
    static  int terminate()                                                  {}

    static  int is_run()                                                     {}

    static  void draw_rectangle(const Point&, double, double, const Color)   {}
    static  void draw_square   (const Point&, double, const Color&)          {}
    static  void draw_circle   (const Point&, double, const Color&)          {} 
    static  void draw_text     (const Point&, double, double, const char*)   {} 
    
};
int     Engine_protocol::window_width    = 1920;
int     Engine_protocol::window_height   = 1080;
double  Engine_protocol::window_w_to_h   = (double)window_width / window_height;

double  Engine_protocol::angle_circle_x  = 0.007;
double  Engine_protocol::angle_circle_y  = angle_circle_x * window_w_to_h;