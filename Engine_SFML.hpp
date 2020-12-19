#pragma once

#include <SFML/Graphics.hpp>
#include "Engine_protocol.hpp"
// #include "SFML_special/ResourcePath.hpp"

#include "Image_container.hpp"

class Engine_SFML : public Engine_protocol
{
private:
public:
    static sf::RenderWindow main_window_;
    static sf::Font         font;
    static sf::Clock        clock;

    static float Framerate;
    static uint8_t frame_cx;

    static int init();

    static int terminate();

    static int is_run();

    static void before_rendering();

    static void after_rendering();

    static sf::Vector2f sf(Point point);

    static sf::Color sf(const Color &color);

    static Point get_mouse_pos();

    static void draw_rectangle(Point start, double width, double height, const Color &color = Color(1.0, 1.0, 1.0));

    static void draw_square(Point start, double width, const Color &color = Color(1.0, 1.0, 1.0));
    
    static void draw_circle(Point start, double radius, const Color &color = Color(1.0, 1.0, 1.0));

    static void draw_text(const Point &start_, double width, double height, const char* str, int font_size = 20, int length = 0);

    static void draw_text_lefty(const Point &start_, double width, double height, const char* str, int font_size = 20, int length = 0);

    static void draw_image_by_pixel_array(Point start, double width, double height, const Pixel_array &pix_arr, Visible_part vis_part);

};
