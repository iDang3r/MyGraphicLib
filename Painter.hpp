#pragma once

#include "Window.hpp"

#include "Canvas.hpp"
#include "Tool_manager.hpp"

class Painter : Window
{
private:
public:

    Painter(const Point &start, double width, double height) :
        Window(start, width, height, COLORS::painter)
    {
        
    }

};