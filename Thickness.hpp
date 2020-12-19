#pragma once

#include <string>

#include "Window.hpp"
#include "Slider.hpp"

class Thickness_functor;

class Thickness : public Window
{
public:
    static const int min_thickness = 1;
    static const int max_thickness = 61;

    int thickness = 3;
    int label_id  = 0;
    int slider_id = 0;

    Thickness(const Point &start, double width, double height);

    ~Thickness();

    void update(double x);

};

class Thickness_functor
{
public:
    Thickness* thickness;

    Thickness_functor(Thickness* thickness);

    void operator()(double got_from_Slider);

};