#pragma once

#include "Window.hpp"

class System_window : public Window
{
private:
public:

    System_window(const Point &start, double width, double height, const Color &color = Color(0.1, 0.1, 0.1)) :
        Window(start, width, height, color) 
    {}

    void draw() {

        Engine::draw_rectangle(start_, width_, height_, back_color_);
        
        
    }

    bool handle() {
        return true;
    }

};