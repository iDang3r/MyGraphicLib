#include "Engine.hpp"

#include "help_classes.hpp"

Engine::System_window::System_window(const Point &start, double width, double height, const Color &color) :
    real_width(width), real_height(height), Window(start, width, height, color)
{
    // std::cout << "Sys_window: " << start << ", width: " << width << ", height: " << height << std::endl;
    double k = 0.65;
    Engine::create_round_button(id_, Point(angle_circle_x / width, 1.0 - (1 + k) * angle_circle_y / height), k * angle_circle_x / width, Close_system_window(id_), COLORS::red);
    real_height -= 2 * angle_circle_y;
}

void Engine::System_window::draw() {

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
    draw_start.y += height_ - 2 * angle_circle_y;
    Engine::draw_rectangle(draw_start, width_, angle_circle_y, COLORS::sys_window_top);

    draw_start = start_;
    draw_start.y += angle_circle_y;
    Engine::draw_rectangle(draw_start, width_, height_ - 3 * angle_circle_y, back_color_);

    draw_start = start_;
    draw_start.x += angle_circle_x;
    draw_start.y += angle_circle_y;
    Engine::draw_circle(draw_start, angle_circle_x, back_color_);

    draw_start = start_;
    draw_start.x += width_ - angle_circle_x;
    draw_start.y += angle_circle_y;
    Engine::draw_circle(draw_start, angle_circle_x, back_color_);
    
    draw_start = start_;
    draw_start.x += angle_circle_x;
    Engine::draw_rectangle(draw_start, width_ - 2 * angle_circle_x, angle_circle_y, back_color_);

    draw_sub_windows();
}