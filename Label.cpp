#include "Engine.hpp"

Engine::Label::Label(const Point &start, double width, double height, const char* str, const Color&color) :
    Window(start, width, height, color),  str_(str), position(middle)
{
    std::cout << "Label: " << start << ", width: " << width << ", height: " << height << std::endl;
    
    len_ = str_.length();
}

void Engine::Label::set_lefty()
{
    position = lefty;
}

void Engine::Label::set_text(const char* str)
{
    str_ = str;
    len_ = str_.length();
}

void Engine::Label::draw()
{
    Window::draw();

    if (position == middle) {
        draw_text(start_, width_, height_, str_.c_str(), font_size_);
    } else if (position == lefty) {
        draw_text_lefty(start_, width_, height_, str_.c_str(), font_size_);
    }
    
}