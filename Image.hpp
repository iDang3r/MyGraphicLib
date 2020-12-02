#pragma once 

#include "Window.hpp"

class Image : public Window 
{
private:
    sf::Image   img_;
    sf::Texture texture_;
    sf::Sprite  sprite_;
public:
    
    Image(Point start, double width, double height, const char* source, const Color& color = COLORS::clear) :
        Window(start, width, height, color) 
    {
        if (!img_.loadFromFile(source)) {
            dump(DUMP_INFO, "error: image open from source");
            ww(source);
        }

        texture_.loadFromImage(img_);
        sprite_.setTexture(texture_);

        int width_px  = width  * window_width;
        int height_px = height * window_height;

        double k = 0;
        if (sprite_.getLocalBounds().width / width > sprite_.getLocalBounds().height / height) {
            k = (double)width_px / sprite_.getLocalBounds().width;
            start.y -= (height - k * sprite_.getLocalBounds().height / window_height) / 2;
            ws("@@@@@");
        } else {
            k = (double)height_px / sprite_.getLocalBounds().height;
            start.x += (width - k * sprite_.getLocalBounds().width / window_width) / 2;
        }

        start.y += height;
        sprite_.setPosition(sf(start));
        sprite_.setScale(k, k);
    }

    void draw()
    {
        Window::draw();
        main_window_.draw(sprite_);
    }

};