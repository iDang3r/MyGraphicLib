#pragma once

#include "dump.h"
#include "help_classes.hpp"
#include "Event.hpp"

class Engine_protocol 
{
private:
public:
    static  int     window_width;
    static  int     window_height;
    static  double  window_w_to_h;

    static  double  angle_circle_x;
    static  double  angle_circle_y;

    static  constexpr double Pi = M_PI;

    static  int init();                                                          
    static  int terminate();                                                     

    static  int is_run();                                                        

    static void before_rendering();                                              
    static void after_rendering();                                               

    static void wait_events();                                                   

    static void draw_rectangle(const Point&, double, double, const Color);       
    static void draw_square   (const Point&, double, const Color&);              
    static void draw_circle   (const Point&, double, const Color&);               
    static void draw_text     (const Point&, double, double, const char*, int);   
    
};
