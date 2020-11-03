#pragma once

#include "Button.hpp"

template <typename Functor>
class Button_polished : public Button<Functor>
{
private:
public:

    Button_polished(const Point &start, double width, double height, 
        const Color &color, Functor functor, const char* label = NULL)
        : Button<Functor>(start, width, height, color, functor, label)
    {
        std::cout << "Polished Button: " << start << ", radus_x: " << radus_x  << std::endl;
    }

    void draw()
    {
        Point draw_start = start_;
        draw_start.x += angle_circle_x;
        draw_start.y += height_ - angle_circle_y;
        Engine::draw_circle(draw_start, angle_circle_x, color);

        draw_start = start_;
        draw_start.x += width_  - angle_circle_x;
        draw_start.y += height_ - angle_circle_y;
        Engine::draw_circle(draw_start, angle_circle_x, color);

        // draw_start = start_;
        // draw_start.x += angle_circle_x;
        // draw_start.y += height_ - angle_circle_y;
        // Engine::draw_rectangle(draw_start, width_ - 2 * angle_circle_x, angle_circle_y, COLORS::sys_window_top);

        // draw_start = start_;
        // draw_start.y += height_ - 2 * angle_circle_y;
        // Engine::draw_rectangle(draw_start, width_, angle_circle_y, COLORS::sys_window_top);

        draw_start = start_;
        draw_start.y += angle_circle_y;
        Engine::draw_rectangle(draw_start, width_, height_ - 3 * angle_circle_y, back_color_);

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

};