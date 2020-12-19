#pragma once

template <typename Functor>
Engine::Button_round<Functor>::Button_round(const Point &start, double radius_x, const Color &color, Functor functor)
    : Button<Functor>(start, 2 * radius_x, 2 * radius_x * window_w_to_h, color, functor)
{
    std::cout << "Round Button: " << start << ", radus_x: " << radius_x  << std::endl;
}

template <typename Functor>
void Engine::Button_round<Functor>::draw()
{
    Engine::draw_circle(Window::start_ + Point(Window::width_ / 2, Window::height_ / 2), Window::width_ / 2, Window::back_color_);
}