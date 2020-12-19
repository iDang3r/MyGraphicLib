#pragma once 

#include "Window.hpp"

class Functor_empty;

template <typename Functor>
class Slider : public Window
{
public:
    int min_value;
    int max_value;
    int value;

    static constexpr double offset    = 0.045;
    static constexpr double thickness = 0.057;

    double line_width;
    double line_height;
    double radius_x;

    Functor functor;

    int slider_id = 0;

    Slider(const Point &start, double width, double height, int min_value, int max_value, Functor functor)
        : Window(start, width, height, COLORS::clear), min_value(min_value), max_value(max_value), value(min_value), functor(functor)
    {
        line_width  = 1.0 - 4 * offset;
        line_height = thickness;
        radius_x    = offset;

        // Engine::create_window(id_, Point(0.0, 0.5 - line_height / 2.0), 1.0, line_height, COLORS::red);
        int line_id = Engine::create_window(id_, Point(2 * radius_x, 0.5 - line_height / 2.0), line_width, line_height, COLORS::sys_window);
        Window* line = dynamic_cast<Window*>(all_objects[line_id]);

        slider_id = Engine::create_round_button(id_, Point(0.5 - radius_x, 0.5 - radius_x * width_ / height_ * window_w_to_h), radius_x, Functor_empty(), COLORS::sys_window_top);
        Window* slider = dynamic_cast<Window*>(all_objects[slider_id]);
        slider->set_dragable(Dragable::HORIZONTAL, start_.x + offset * width_, start_.x + (1 - offset) * width_, this);


    }

    void draged(double x)
    {
        functor(x);
    }

};

class Functor_empty
{
public:
    void operator()(Engine::Button<Functor_empty>* button) {}
};