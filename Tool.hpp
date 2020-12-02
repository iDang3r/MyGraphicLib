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

    Color   color_;
    double  thickness_;
    bool    using_      = false;  
    Point   fix_point   = Point(0.0, 0.0);

    Tool(const Color &color, double thickness, Type enum_type) : color_(color), thickness_(thickness), type(enum_type) 
    {
        subscribes[Event::RELEASE].insert(this);
        subscribes[Event::MOUSE_MOVE].insert(this);
    }

    ~Tool() 
    {
        subscribes[Event::RELEASE].erase(this);
        subscribes[Event::MOUSE_MOVE].erase(this);
    }
    
    void set_color(const Color &color) 
    {
        color_ = color;
    }

    void set_thickness(double thickness) 
    {
        thickness_ = thickness;
    }

    virtual void use(const Canvas &canvas, Event_t event) = 0;

};


class Hand_tool : public Tool
{
public:

    Hand_tool() : Tool(COLORS::clear, 0.0, Tool::HAND) 
        {}

    void use(const Canvas &canvas, Event_t event)
    {
        if (event.id == Event::CLICK) {
            fix_point = Point(event.x, event.y);
            using_ = true;
            return;
        }

        if (using_ && event.id == Event::MOUSE_MOVE) {
            canvas.move(Point(event.x, event.y) - fix_point);
            fix_point = Point(event.x, event.y);
            return;
        }

        if (using_ && event.id == Event::RELEASE) {
            using_ = false;
            return;
        }

    }

};
