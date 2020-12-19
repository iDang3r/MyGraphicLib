#pragma once

#include "Window.hpp"
#include "Canvas.hpp"

class Palette_functor;

class Palette : public Window
{
public:

    Color color;
    bool is_color_table_active = false;

    Palette(const Point &start, double width, double height);
};

class Palette_functor
{
public:
    int window_id;
    Palette* palette;

    Palette_functor(int color_window_id, Palette* palette);

    void operator()(Engine::Button<Palette_functor>* button);
};