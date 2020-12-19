#pragma once

#include "help_classes.hpp"

#include "Object.hpp"

class Window : public Object
{
private:
public:
    #include "Dragable.hpp"

    Point   start_;
    double  width_;
    double  height_;
    Color   back_color_;

    Dragable* drag = NULL;

    bool    pressed_    = false;
    bool    hovered_    = false;

    Window(const Point &start, double width, double height, const Color &color = COLORS::window);

    ~Window();

    bool check_mouse(const Event_t &event);

    void set_color(const Color& color);

    virtual void set_viewport();

    void draw();

    void draw_sub_windows();

    bool handle(const Event_t &event);

    bool check_coordinates(double x, double y);

    void set_dragable(Dragable::Type type, double min_pos, double max_pos, Window* drag_window = NULL);

    void unset_dragable();

    void move(const Point& delta);

    virtual void draged(double x);

};