#pragma once

#include <string>
#include "Window.hpp"

class Label : public Window 
{
private:
public:

    std::string str_;
    int         len_ = 0;
    int         font_size_ = 20;

    enum Position {
        reserved,
        lefty,
        middle,
        rightly,
    } position;

    Label(const Point &start, double width, double height, const char* str, const Color&color = COLORS::clear) :
        Window(start, width, height, color),  str_(str), position(middle)
    {
        std::cout << "Label: " << start << ", width: " << width << ", height: " << height << std::endl;
        
        len_ = str_.length();
    }

    void set_lefty()
    {
        position = lefty;
    }

    void set_text(const char* str)
    {
        str_ = str;
        len_ = str_.length();
    }

    void draw()
    {
        Window::draw();

        if (position == middle) {
            draw_text(start_, width_, height_, str_.c_str(), font_size_);
        } else if (position == lefty) {
            draw_text_lefty(start_, width_, height_, str_.c_str(), font_size_);
        }
        
    }

};