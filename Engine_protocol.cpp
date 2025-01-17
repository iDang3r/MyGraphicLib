#include "Engine_protocol.hpp"

int  Engine_protocol::init()                                                          {return 1;}
int  Engine_protocol::terminate()                                                     {return 1;}

int  Engine_protocol::is_run()                                                        {return 0;}

void Engine_protocol::before_rendering()                                              {}
void Engine_protocol::after_rendering()                                               {}

void Engine_protocol::wait_events()                                                   {}

void Engine_protocol::draw_rectangle(const Point&, double, double, const Color)       {}
void Engine_protocol::draw_square   (const Point&, double, const Color&)              {}
void Engine_protocol::draw_circle   (const Point&, double, const Color&)              {} 
void Engine_protocol::draw_text     (const Point&, double, double, const char*, int)  {}

int     Engine_protocol::window_width    = 1920; // 1400
int     Engine_protocol::window_height   = 1000; // 800
double  Engine_protocol::window_w_to_h   = (double)window_width / window_height;

double  Engine_protocol::angle_circle_x  = 0.007;
double  Engine_protocol::angle_circle_y  = angle_circle_x * window_w_to_h;