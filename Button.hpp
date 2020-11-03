#pragma once

#include "Window.hpp"
#include "Label.hpp"

template <typename Functor>
class Button : public Window 
{
private:
public:

    Functor functor;

    Button(const Point &start, double width, double height, 
        const Color &color, Functor functor, const char* label = NULL)
        : Window(start, width, height, color), functor(functor)
    {
        std::cout << "Button: " << start << ", width: " << width << ", height: " << height << std::endl;
        if (label != NULL) {
            // Engine::create_label(id_, start, width, height, label);
        }
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
                hovered_ = true;
            }

            break;

        case Event::HOVERED:

            hovered_ = true;

            break;
        }

        return true;
    }

    void draw()
    {
        if (hovered_ && !pressed_) {
            back_color_.lighter();
            draw();
            back_color_.de_lighter();
            hovered_ = false;
        } else {
            draw();
        }

    }


};