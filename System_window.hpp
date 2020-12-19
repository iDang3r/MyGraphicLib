#pragma once

#include "Window.hpp"

class System_window : public Window
{
private:
public:
    double real_width;
    double real_height;

    System_window(const Point &start, double width, double height, const Color &color = COLORS::sys_window);

    void draw();
    
};