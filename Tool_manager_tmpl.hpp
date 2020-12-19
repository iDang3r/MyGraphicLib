#pragma once

template <typename Functor>
void Engine::Tool_manager::add_bttn(const Point &point, double width, const Functor &functor, const char* source)
{
    double k = 0.1;
    double d_x = k * width;
    double d_y = k * width / height_ * width_ * Engine::window_w_to_h;
    Engine::create_button(id_, point, width, width / height_ * width_ * Engine::window_w_to_h, functor, NULL, source, COLORS::tool);
}