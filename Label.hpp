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

    Label(const Point &start, double width, double height, const char* str, const Color&color = COLORS::clear);

    void set_lefty();

    void set_text(const char* str);

    void draw();

};