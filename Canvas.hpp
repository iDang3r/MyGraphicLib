#pragma once 

#include "Window.hpp"

class Canvas : public Window
{
private:
public:
    
    Pixel_array     pixel_array_;
    Visible_part    visible_part_;

    Image_container* image_container = NULL;

    const double zoom_coef = 1.4;

    Canvas(const Point &start, double width, double height) 
        : Window(start, width, height, COLORS::white)
    {
        load_from_image("cute_image.jpg");
    }

    void load_from_image(const char* source) 
    {
        if (image_container) {
            dump(DUMP_INFO, "Image already exists");
            return;
        }

        image_container = new Image_container(source);

        image_container->get_pixel_array(pixel_array_.start, pixel_array_.width, pixel_array_.height);

        visible_part_.start_x = 0;
        visible_part_.start_y = 0;

        int width_px  = width_  * window_width;
        int height_px = height_ * window_height;

        visible_part_.width  = pixel_array_.width / 3;
        visible_part_.height = visible_part_.width * height_px / width_px + 1;
    }

    void draw()
    {
        Window::draw();

        if (image_container) {
            draw_image_by_pixel_array(start_, width_, height_, pixel_array_, visible_part_);
        }
        
        draw_sub_windows();
    }

    void move(const Point& delta) 
    {
        
    }


};
