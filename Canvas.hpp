#pragma once 

#include "Window.hpp"

class Canvas : public Window
{
private:
public:
    
    Pixel_array     pixel_array_;
    Visible_part    visible_part_;

    Image_container* image_container = NULL;

    const double zoom_coef = 1.2;

    Canvas(const Point &start, double width, double height) 
        : Window(start, width, height, COLORS::clear)
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

        visible_part_.x = 0;
        visible_part_.y = 0;

        int width_px  = width_  * window_width;
        int height_px = height_ * window_height;

        visible_part_.width  = pixel_array_.width / 2;
        visible_part_.height = visible_part_.width * height_px / width_px;
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
        int delta_x = visible_part_.width  * delta.x / width_;
        int delta_y = visible_part_.height * delta.y / height_;
        delta_x *= -1;

        if (delta_x > 0) {
            visible_part_.x = std::min(visible_part_.x + delta_x, pixel_array_.width - visible_part_.width);
        } else {
            visible_part_.x = std::max(visible_part_.x + delta_x, 0);
        }

        if (delta_y > 0) {
            visible_part_.y = std::min(visible_part_.y + delta_y, pixel_array_.height - visible_part_.height);
        } else {
            visible_part_.y = std::max(visible_part_.y + delta_y, 0);
        }
    }

    void draw_line(const Point &begin, const Point &end, const Color &color, int thickness)
    {
        int begin_x = visible_part_.width  *      (begin.x - start_.x) / width_;
        int begin_y = visible_part_.height * (1 - (begin.y - start_.y) / height_);
        int end_x =   visible_part_.width  *      (end.x   - start_.x) / width_;
        int end_y =   visible_part_.height * (1 - (end.y   - start_.y) / height_);

        begin_x += visible_part_.x;
        begin_y += visible_part_.y;
        end_x   += visible_part_.x;
        end_y   += visible_part_.y;

        if (begin_x > end_x) {
            std::swap(begin_x, end_x);
            std::swap(begin_y, end_y);
        }

        if (end_x - begin_x) {
            return;
        }

        for (int i = begin_x; i <= end_x; ++i) {

            int j = begin_y + (end_y - begin_y) * (i - begin_x) / (end_x - begin_x);

            for (int p_i = std::max(i - thickness, 0); p_i <= std::min(i + thickness, pixel_array_.width); ++p_i) {
                for (int p_j = std::max(j - thickness, 0); p_j <= std::min(j + thickness, pixel_array_.height); ++p_j) {
                    if (SQR(p_i - i) + SQR(p_j - j) <= SQR(thickness)) {
                        pixel_array_.start[p_i * pixel_array_.width + p_j] = color;
                    }
                }
            }

        }

        // ww(begin_x);
        // ww(begin_y);
        // ww(visible_part_.width);
        // ww(visible_part_.height);



    }

    void zoom_up(const Point& point)
    {
        int point_x = visible_part_.width  * point.x / width_;
        int point_y = visible_part_.height * point.y / height_;



        visible_part_.width  /= zoom_coef;
        visible_part_.height /= zoom_coef;
    }

    void zoom_down(const Point& point)
    {
        int point_x = visible_part_.width  * point.x / width_;
        int point_y = visible_part_.height * point.y / height_;



        visible_part_.width  *= zoom_coef;
        visible_part_.height *= zoom_coef;

        if (visible_part_.x + visible_part_.width > pixel_array_.width) {
            visible_part_.x = pixel_array_.width - visible_part_.width;
        }

        if (visible_part_.y + visible_part_.height > pixel_array_.height) {
            visible_part_.y = pixel_array_.height - visible_part_.height;
        }

        if (visible_part_.x < 0) {
            visible_part_.x = 0;
            if (visible_part_.width > pixel_array_.width) {
                visible_part_.width = pixel_array_.width;
                visible_part_.height = visible_part_.width * height_ / width_ / window_w_to_h;
            }
        }

        if (visible_part_.y < 0) {
            visible_part_.y = 0;
            if (visible_part_.height > pixel_array_.height) {
                visible_part_.height = pixel_array_.height;
                visible_part_.width = visible_part_.height / height_ * width_ * window_w_to_h;
            }
        }
    }

    bool handle(const Event_t &event)
    {
        if (event.id == Event::CLICK) {
            return true;
        }

        return false;
    }


};
