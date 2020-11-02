#pragma once

#include "Button.hpp"

template <typename Functor>
class Button_round : public Button<Functor>
{
private:
public:

    Button_round(const Point &start, double radus_x, const Color &color, Functor functor)
        : Button<Functor>(start, 2 * radus_x, 2 * radus_x * window_w_to_h, color, functor)
    {
        std::cout << "Round Button: " << start << ", radus_x: " << radus_x  << std::endl;
    }

    void draw()
    {
        draw_circle(Window::start_ + Point(Window::width_ / 2, Window::height_ / 2), Window::width_ / 2, Window::back_color_);
    }

};