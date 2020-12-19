#pragma once

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

    double range;

    Window* window;
    Window* drag_window;

    Dragable(Window* window, Type type, double min_pos, double max_pos, Window* drag_window = NULL) : 
        window(window), type(type), fix_point(0.0, 0.0), min_pos(min_pos), max_pos(max_pos), drag_window(drag_window),
        range(max_pos - min_pos)
    {
        if (type == VERTICAL) {

            range -= window->height_;

        } else if (type == HORIZONTAL) {

            range -= window->width_;

        } else {
            dump(DUMP_INFO, "NOT SUPPORTABLE");
            abort();
        }
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

            double delta_x = event.x - fix_point.x;
            if (delta_x > 0 && window->start_.x + window->width_ < max_pos) {
                delta.x = std::min(delta_x, max_pos - (window->start_.x + window->width_));
                fix_point = Point(event.x, event.y);
            }

            if (delta_x < 0 && window->start_.x > min_pos) {
                delta.x = std::max(delta_x, min_pos - window->start_.x);
                fix_point = Point(event.x, event.y);
            }

            window->move(delta);
            if (drag_window) {
                if (type == VERTICAL) {
                    drag_window->draged((window->start_.y - min_pos) / range);
                }
                if (type == HORIZONTAL) {
                    drag_window->draged((window->start_.x - min_pos) / range);
                }
            }

            return delta.x;

        } else {
            dump(DUMP_INFO, "NOT SUPPORTABLE");
            abort();
        }

        return 0.0;
    }

};