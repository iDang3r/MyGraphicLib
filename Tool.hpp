#pragma once 

#include "Object.hpp"

class Tool : public Object
{
private:
public:

    enum Type {
        RESERVED,
        HAND,
        ZOOM_UP,
        ZOOM_DOWN,
        BRUSH,
        ERASER,
        SPRAY,
        FILL,
    } type;

    Color   color_      = COLORS::cyan;
    int     thickness_  = 3;
    bool    using_      = false;
    Point   fix_point   = Point(0.0, 0.0);

    bool is_active = false;

    Tool();

    Tool(const Color &color, int thickness, Type enum_type);

    ~Tool();
    
    void set_color(const Color &color);

    void set_thickness(int thickness);

    void set_active();

    void unset_activ();

    bool handle(const Event_t& event);

    bool check_mouse(const Event_t &event);

    virtual void use(Canvas &canvas, const Event_t &event) = 0;

};


class Hand_tool : public Tool
{
public:

    Hand_tool();

    void use(Canvas &canvas, const Event_t &event);

};

class Zoom_up_tool : public Tool
{
public:

    Zoom_up_tool();

    void use(Canvas &canvas, const Event_t &event);

};

class Zoom_down_tool : public Tool
{
public:

    Zoom_down_tool();

    void use(Canvas &canvas, const Event_t &event);

};

class Brush_tool : public Tool
{
public:

    Brush_tool();

    void use(Canvas &canvas, const Event_t &event);

};

