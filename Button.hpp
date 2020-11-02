#pragma once

#include "Window.hpp"

template <typename Functor>
class Button : public Window {
private:
public:

    Functor functor;

    Button(int window_id, const Point &start, double width, double height, 
        const Color &color, Functor functor)
        : Window(start, width, height, color), functor(functor)
    {
        std::cout << "Button: " << start << ", width: " << width << ", height: " << height << std::endl;
    }

    bool handle(const Event_t &event) {

        switch (event.id)
        {
        case Event::CLICK:
            
            std::cout << "CLICKED!!!!!!!!!!!!!!!!!!" << std::endl;
            std::cout << "BUTTON HANDLER, x: " << event.x << ", y: " << event.y << std::endl;

            functor(this);

            break;
        }

    }


};