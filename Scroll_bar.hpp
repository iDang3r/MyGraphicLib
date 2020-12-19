#pragma once 

#include "Window.hpp"

class Scroll_bar : public Window
{
private:
    bool is_vertical;

    double slider_position;
    double slider_size = 0.4;

    int degrees = 20;
    int pos = 0;

    const double arrows_size = 0.07;

public:

    Scroll_bar(const Point &start, double width, double height);

};