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

    Button(const Point &start, double width, double height, 
        const Color &color, Functor functor, const char* label = NULL)
        : Window(start, width, height, color), functor(functor), label(start, width, height, label)
    {
        std::cout << "Button: " << start << ", width: " << width << ", height: " << height << std::endl;
    }

    bool handle(const Event_t &event) 
    {
        // std::cout << "BUTTON HANDLER, x: " << event.x << ", y: " << event.y << std::endl;
        switch (event.id)
        {
        case Event::CLICK:

            pressed_ = true;
            back_color_.inverse();

            subscribes[Event::RELEASE].push_back(this);

            break;

        case Event::RELEASE:

            pressed_ = false;
            back_color_.inverse();

            if (check_coordinates(event.x, event.y)) {
                functor(this);
            }

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