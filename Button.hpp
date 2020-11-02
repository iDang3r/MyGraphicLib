#pragma once

#include "Window.hpp"

template <typename Functor>
class Button : public Window 
{
private:
public:

    Functor     functor;
    const char* label;

    Button(int window_id, const Point &start, double width, double height, 
        const Color &color, Functor functor, const char* label = NULL)
        : Window(start, width, height, color), functor(functor), label(label)
    {
        std::cout << "Button: " << start << ", width: " << width << ", height: " << height << std::endl;
    }

    bool handle(const Event_t &event) 
    {
        switch (event.id)
        {
        case Event::CLICK:
            
            std::cout << "BUTTON HANDLER, x: " << event.x << ", y: " << event.y << std::endl;

            functor(this);

            break;
        }

        return true;
    }

    void draw()
    {
        Window::draw();

        if (label != NULL) {

            int length = strlen(label);
            double str_height = 14.0 / window_height;
            double str_width  = length * 9.0 / window_width;

            drawText(label, length, start_.x + width_ / 2 - str_width / 2, start_.y + height_ / 2 - str_height / 2);
        }
    }


};