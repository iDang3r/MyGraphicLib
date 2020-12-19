#include "Engine.hpp"

Engine::Image::Image(Point start, double width, double height, const char* source, const Color& color) :
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

    double k1 = (double)width_px / sprite_.getLocalBounds().width;
    double k2 = (double)height_px / sprite_.getLocalBounds().height;
    double k = std::min(k1, k2);
    if (k1 < k2) {
        start.y -= (height - k * sprite_.getLocalBounds().height / window_height) / 2;
        // ws("@@@@@");
    } else {
        start.x += (width - k * sprite_.getLocalBounds().width / window_width) / 2;
    }

    start.y += height;
    sprite_.setPosition(sf(start));
    sprite_.setScale(k, k);
}

void Engine::Image::draw()
{
    Window::draw();
    main_window_.draw(sprite_);
}