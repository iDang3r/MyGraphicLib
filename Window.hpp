#pragma once

#include "Object.hpp"

class Window : public Object
{
private:
public:

    Point   start_;
    double  width_;
    double  height_;
    Color   back_color_;

    Dragable* drag = NULL;

    bool    pressed_    = false;
    bool    hovered_    = false;

    Window(const Point &start, double width, double height, const Color &color = COLORS::window) : 
        start_(start), width_(width), height_(height), back_color_(color)
    {
        
    }

    bool check_mouse(const Event_t &event) 
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

    void set_color(const Color& color)
    {
        back_color_ = color;
    }

    virtual void set_viewport()
    {
        // glViewport(start_.x * Engine::window_width, start_.y * Engine::window_height, width_ * Engine::window_width, height_ * Engine::window_height);
    }

    void draw() 
    {
        Engine::draw_rectangle(start_, width_, height_, back_color_); 

        draw_sub_windows();
    }

    void draw_sub_windows()
    {
        for (auto sub_object : sub_objects) {
            Window* sub_window = dynamic_cast<Window*>(sub_object);
            if (sub_window != nullptr) {
                // set_viewport();
                sub_window->draw();
            }
        }
    }

    bool handle(const Event_t &event) 
    {
        // std::cout << "WINDOW HANDLER, x: " << event.x << ", y: " << event.y << std::endl;
        return false;
    }

    bool check_coordinates(double x, double y)
    {
        return !(x < start_.x || y < start_.y || x > start_.x + width_ || y > start_.y + height_);
    }

    void set_dragable(Dragable::Type type, double min_pos, double max_pos) 
    {
        drag = new Dragable(this, type, min_pos, max_pos);
    }

    void unset_dragable()
    {
        delete drag;
        drag = NULL;
    }

    void move(const Point& delta) {
        for (auto child : sub_objects) {
            Window* child_window = dynamic_cast<Window*>(child);
            if (child_window) {
                child_window->move(delta);
            }
        }
        start_ += delta;
    }

};