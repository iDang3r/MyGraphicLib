#pragma once 

#include "Window.hpp"

class Image : public Window 
{
private:
    sf::Image   img_;
    sf::Texture texture_;
    sf::Sprite  sprite_;
public:
    
    Image(Point start, double width, double height, const char* source, const Color& color = COLORS::clear);

    void draw();

};