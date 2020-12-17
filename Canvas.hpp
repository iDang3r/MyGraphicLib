#pragma once 

#include "Window.hpp"

class Canvas : public Window
{
private:
public:
    
    Pixel_array     pixel_array_;
    Visible_part    visible_part_;

    const double zoom_coef = 1.2;

    Canvas(const Point &start, double width, double height) 
        : Window(start, width, height, COLORS::clear)
    {
        load_from_image("cute_image.jpg");
    }

    ~Canvas()
    {
        if (pixel_array_.start) {
            delete [] pixel_array_.start;
        }
    }

    bool load_from_image(const char* source) 
    {
        ws("LOADING IMAGE FROM:");
        ww(source);

        Image_container image_container;

        if (!image_container.load(source)) {
            return false;
        }

        if (pixel_array_.start) {
            delete [] pixel_array_.start;
            pixel_array_.start = nullptr;
        }

        image_container.get_pixel_array(pixel_array_.start, pixel_array_.width, pixel_array_.height);

        visible_part_.x = 0;
        visible_part_.y = 0;

        int width_px  = width_  * window_width;
        int height_px = height_ * window_height;

        visible_part_.width  = pixel_array_.width / 2;
        visible_part_.height = visible_part_.width * height_px / width_px;

        return true;
    }

    void save_to_image(const char* source)
    {
        ws("SAVING IMAGE TO:");
        ww(source);
    }

    void draw()
    {
        Window::draw();

        if (pixel_array_.start) {
            draw_image_by_pixel_array(start_, width_, height_, pixel_array_, visible_part_);
        }
        
        draw_sub_windows();
    }

    bool move(const Point& delta) 
    {
        int delta_x = visible_part_.width  * delta.x / width_;
        int delta_y = visible_part_.height * delta.y / height_;
        if (delta_x == 0 && delta_y == 0) {
            return false;
        }

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
        
        return true;
    }

    void draw_line(const Point &begin, const Point &end, const Color &color, int thickness)
    {
        int begin_x = visible_part_.width  * (0 + (begin.x - start_.x) / width_);
        int begin_y = visible_part_.height * (1 - (begin.y - start_.y) / height_);
        int end_x =   visible_part_.width  * (0 + (end.x   - start_.x) / width_);
        int end_y =   visible_part_.height * (1 - (end.y   - start_.y) / height_);

        begin_x += visible_part_.x;
        begin_y += visible_part_.y;
        end_x   += visible_part_.x;
        end_y   += visible_part_.y;

        if (std::abs(begin_x - end_x) >= std::abs(begin_y - end_y)) {

            if (begin_x > end_x) {
                std::swap(begin_x, end_x);
                std::swap(begin_y, end_y);
            }

            // draw one point, if Point_begin == Point_end
            for (int p_i = std::max(begin_x - thickness, 0); p_i <= std::min(begin_x + thickness, pixel_array_.width - 1); ++p_i) {
                for (int p_j = std::max(begin_y - thickness, 0); p_j <= std::min(begin_y + thickness, pixel_array_.height - 1); ++p_j) {
                    if (SQR(p_i - begin_x) + SQR(p_j - begin_y) <= SQR(thickness)) {
                        pixel_array_.start[p_j * pixel_array_.width + p_i] = color;
                    }
                }
            }

            for (int i = begin_x + 1; i <= end_x; ++i) {

                int j = begin_y + (end_y - begin_y) * (i - begin_x) / (end_x - begin_x);

                for (int p_i = std::max(i - thickness, 0); p_i <= std::min(i + thickness, pixel_array_.width - 1); ++p_i) {
                    for (int p_j = std::max(j - thickness, 0); p_j <= std::min(j + thickness, pixel_array_.height - 1); ++p_j) {
                        if (SQR(p_i - i) + SQR(p_j - j) <= SQR(thickness)) {
                            pixel_array_.start[p_j * pixel_array_.width + p_i] = color;
                        }
                    }
                }

            }

        } else {

            if (begin_y > end_y) {
                std::swap(begin_x, end_x);
                std::swap(begin_y, end_y);
            }

            for (int j = begin_y; j <= end_y; ++j) {

                int i = begin_x + (end_x - begin_x) * (j - begin_y) / (end_y - begin_y);

                for (int p_i = std::max(i - thickness, 0); p_i <= std::min(i + thickness, pixel_array_.width - 1); ++p_i) {
                    for (int p_j = std::max(j - thickness, 0); p_j <= std::min(j + thickness, pixel_array_.height - 1); ++p_j) {
                        if (SQR(p_i - i) + SQR(p_j - j) <= SQR(thickness)) {
                            pixel_array_.start[p_j * pixel_array_.width + p_i] = color;
                        }
                    }
                }

            }

        }
        

    }

    void zoom_up(const Point& point)
    {
        int point_x = visible_part_.width  * (0 + (point.x - start_.x) / width_);
        int point_y = visible_part_.height * (1 - (point.y - start_.y) / height_);

        visible_part_.width  /= zoom_coef;
        visible_part_.height /= zoom_coef;

        visible_part_.x += point_x * (1 - 1 / zoom_coef);
        visible_part_.y += point_y * (1 - 1 / zoom_coef);
    }

    void zoom_down(const Point& point)
    {
        int point_x = visible_part_.width  * (0 + (point.x - start_.x) / width_);
        int point_y = visible_part_.height * (1 - (point.y - start_.y) / height_);

        visible_part_.width  *= zoom_coef;
        visible_part_.height *= zoom_coef;

        visible_part_.x -= point_x * (zoom_coef - 1);
        visible_part_.y -= point_y * (zoom_coef - 1);

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
