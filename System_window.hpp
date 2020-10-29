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
        draw_start.x += angle_circle_x;
        draw_start.y += height_ - angle_circle_y;
        Engine::draw_circle(draw_start, angle_circle_x, COLORS::sys_window_top);

        draw_start = start_;
        draw_start.x += width_  - angle_circle_x;
        draw_start.y += height_ - angle_circle_y;
        Engine::draw_circle(draw_start, angle_circle_x, COLORS::sys_window_top);

        draw_start = start_;
        draw_start.x += angle_circle_x;
        draw_start.y += height_ - angle_circle_y;
        Engine::draw_rectangle(draw_start, width_ - 2 * angle_circle_x, angle_circle_y, COLORS::sys_window_top);

        draw_start = start_;
        draw_start.y += angle_circle_y;
        Engine::draw_rectangle(draw_start, width_, height_ - 2 * angle_circle_y, back_color_);

        draw_start = start_;
        draw_start.x += angle_circle_x;
        draw_start.y += angle_circle_y;
        Engine::draw_circle(draw_start, angle_circle_x, back_color_);

        draw_start = start_;
        draw_start.x += width_  - angle_circle_x;
        draw_start.y += angle_circle_y;
        Engine::draw_circle(draw_start, angle_circle_x, back_color_);
        
        draw_start = start_;
        draw_start.x += angle_circle_x;
        Engine::draw_rectangle(draw_start, width_ - 2 * angle_circle_x, angle_circle_y, back_color_);
    }

    bool handle() {
        return true;
    }

};