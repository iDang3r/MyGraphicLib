#pragma once

#include "Window.hpp"

class Label : public Window 
{
private:
public:

    const char* str_ = NULL;
    int         len_ = 0;

    Label(const Point &start, double width, double height, const char* str) :
        Window(start, width, height, COLORS::clear),  str_(str)
    {
        std::cout << "Label: " << start << ", width: " << width << ", height: " << height << std::endl;
        if (str_ != NULL) {
            len_ = strlen(str_);
        }
    }

    void draw()
    {
        draw_text(start_, width_, height_, str_, len_);
    }

};