#pragma once 

#include "Window.hpp"

class Canvas : public Window
{
private:
public:
    
    Pixel_array     pixel_array_;
    Visible_part    visible_part_;

    const double zoom_coef = 1.2;

    Canvas(const Point &start, double width, double height);

    ~Canvas();

    bool load_from_image(const char* source);

    bool save_to_image(const char* source);

    void draw();

    bool move(const Point& delta);

    void draw_line(const Point &begin, const Point &end, const Color &color, int thickness);

    void zoom_up(const Point& point);

    void zoom_down(const Point& point);

    bool handle(const Event_t &event);

    int get_px_x(double x);

    int get_px_y(double y);

};
