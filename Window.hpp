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

    Window(const Point &start, double width, double height, const Color &color = COLORS::window) : 
        start_(start), width_(width), height_(height), back_color_(color)
    {

    }

    void draw() {

        w(back_color_);
        Engine::draw_rectangle(start_, width_, height_, back_color_);
        
    }

    bool handle() {
        return true;
    }

};