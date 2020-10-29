#pragma once

#include "Object.hpp"

class Window : Object
{
private:
public:

    Point   start_;
    double  width_;
    double  height_;
    Color   back_color_;

    Window(const Point &start, double width, double height, const Color &color = Color(0, 0, 0)) : 
        start_(start), width_(width), height_(height), back_color_(color)
    {

    }

    void draw() {
        
    }

};