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

    bool    hovered_ = false;

    Window(const Point &start, double width, double height, const Color &color = COLORS::window) : 
        start_(start), width_(width), height_(height), back_color_(color)
    {

    }

    virtual bool check_mouse(const Event_t &event) {

        if (event.x > width_ || event.y > height_) {
            return false;
        }

        for (auto object : sub_objects) {
            Window* window = dynamic_cast<Window*>(object);
            if (window == nullptr) {
                continue;
            }

            Event_t new_event(event.id, event.x - window->start_.x, event.y - window->start_.y);
            if (new_event.x < 0 || new_event.y < 0) {
                continue;
            }

            bool u = window->check_mouse(new_event);

            if (u) {
                return true;
            }
        }

        return handle(event);
    }

    void draw() 
    {
        Engine::draw_rectangle(start_, width_, height_, back_color_);   
    }

    bool handle(const Event_t &event) 
    {
        
        return true;
    }

};