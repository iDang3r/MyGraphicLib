#pragma once

#include "Window.hpp"

class System_window : public Window
{
private:
public:

    System_window(const Point &start, double width, double height, const Color &color = Color(0.1, 0.1, 0.1)) :
        Window(start, width, height, color) 
    {}

    void draw() {

        Point draw_start = start_;
        draw_start.x += angle_circle_r;
        draw_start.y += height_ - angle_circle_r;

        Engine::draw_circle(draw_start, angle_circle_r, COLORS::sys_window_top);



        start_.y += angle_circle_r;
        Engine::draw_rectangle(start_, width_, height_ - 2 * angle_circle_r, back_color_);


        
        
    }

    bool handle() {
        return true;
    }

};