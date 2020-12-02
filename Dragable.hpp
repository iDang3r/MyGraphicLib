#pragma once 

// #include "help_classes.hpp"

class Window;

class Dragable
{
private:
public:

    enum Type {
        VERTICAL,
        HORIZONTAL,
        ALL,
    } type;

    Point fix_point;
    double min_pos;
    double max_pos;

    Window* window;
    Window* drag_window;

    Dragable(Window* window, Type type, double min_pos, double max_pos, Window* drag_window = NULL) : 
        window(window), type(type), fix_point(0.0, 0.0), min_pos(min_pos), max_pos(max_pos), drag_window(drag_window)
    {

    }
    
    void set() 
    {
        fix_point = get_mouse_pos();
    }

    double move(const Event_t &event)
    {
        Point delta(0.0, 0.0);

        if (type == VERTICAL) {

            double delta_y = event.y - fix_point.y;
            if (delta_y > 0 && window->start_.y + window->height_ < max_pos) {
                delta.y = std::min(delta_y, max_pos - (window->start_.y + window->height_));
                fix_point = Point(event.x, event.y);
            }

            if (delta_y < 0 && window->start_.y > min_pos) {
                delta.y = std::max(delta_y, min_pos - window->start_.y);
                fix_point = Point(event.x, event.y);
            }

            window->move(delta);

            return delta.y;

        } else if (type == HORIZONTAL) {

        } else {
            dump(DUMP_INFO, "NOT SUPPORTABLE");
            abort();
        }

        return 0.0;
    }

};