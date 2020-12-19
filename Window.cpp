#include "Engine.hpp"

Engine::Window::Window(const Point &start, double width, double height, const Color &color) : 
    start_(start), width_(width), height_(height), back_color_(color)
{}

Engine::Window::~Window() {}

bool Engine::Window::check_mouse(const Event_t &event) 
{
    // std::cout << "check_mouse:-> x: " << event.x << ", y: " << event.y << std::endl;
    if (event.x < start_.x || event.y < start_.y 
        || event.x > start_.x + width_ || event.y > start_.y + height_) {
        return false;
    }

    for (auto it = sub_objects.rbegin(); it != sub_objects.rend(); ++it) {

        bool u = (*it)->check_mouse(event);
        if (u) {
            return true;
        }
    }

    return handle(event);
}

void Engine::Window::set_color(const Color& color)
{
    back_color_ = color;
}

void Engine::Window::set_viewport()
{
    // glViewport(start_.x * Engine::window_width, start_.y * Engine::window_height, width_ * Engine::window_width, height_ * Engine::window_height);
}

void Engine::Window::draw() 
{
    Engine::draw_rectangle(start_, width_, height_, back_color_); 

    draw_sub_windows();
}

void Engine::Window::draw_sub_windows()
{
    for (auto sub_object : sub_objects) {
        Window* sub_window = dynamic_cast<Window*>(sub_object);
        if (sub_window != nullptr) {
            // set_viewport();
            sub_window->draw();
        }
    }
}

bool Engine::Window::handle(const Event_t &event) 
{
    // std::cout << "WINDOW HANDLER, x: " << event.x << ", y: " << event.y << std::endl;
    return false;
}

bool Engine::Window::check_coordinates(double x, double y)
{
    return !(x < start_.x || y < start_.y || x > start_.x + width_ || y > start_.y + height_);
}

void Engine::Window::set_dragable(Dragable::Type type, double min_pos, double max_pos, Window* drag_window) 
{
    drag = new Dragable(this, type, min_pos, max_pos, drag_window);
}

void Engine::Window::unset_dragable()
{
    delete drag;
    drag = NULL;
}

void Engine::Window::move(const Point& delta) {
    for (auto child : sub_objects) {
        Window* child_window = dynamic_cast<Window*>(child);
        if (child_window) {
            child_window->move(delta);
        }
    }
    start_ += delta;
}

void Engine::Window::draged(double x) {}