#pragma once

#include "Window.hpp"
#include "Label.hpp"

template <typename Functor>
class Button : public Window 
{
private:
public:

    Functor functor;
    Label   label;

    Button(int window_id, const Point &start, double width, double height, 
        const Color &color, Functor functor, const char* label = NULL)
        : Window(start, width, height, color), functor(functor), label(start, width, height, label)
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
        label.draw();
    }


};