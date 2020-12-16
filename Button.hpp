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
        const Color &color, Functor functor, const char* label = NULL, const char* img_source = NULL)
        : Window(start, width, height, color), functor(functor)
    {
        std::cout << "Button: " << start << ", width: " << width << ", height: " << height << std::endl;
        if (img_source != NULL) {
            Engine::create_image(id_, Point(0.0, 0.0), 1.0, 1.0, img_source);
        }
        if (label != NULL) {
            Engine::create_label(id_, Point(0.0, 0.0), 1.0, 1.0, label);
        }
        subscribes[Event::RELEASE].insert(this);
        subscribes[Event::UNHOVERED].insert(this);
    }

    ~Button()
    {
        // subscribes[Event::RELEASE].erase(this);
    }

    bool handle(const Event_t &event) 
    {
        // std::cout << "BUTTON HANDLER, x: " << event.x << ", y: " << event.y << std::endl;
        switch (event.id)
        {
        case Event::CLICK:
        case Event::DOUBLE_CLICK:
            ws("CLICK");
            pressed_ = true;
            Event::hover_disable = true;
            if (drag) {

                drag_subscribes.insert(drag);
                drag->set();

                break;
            }

            if (hovered_) {
                back_color_.de_lighter();
            }
            back_color_.inverse();
            break;

        case Event::RELEASE:
            if (pressed_ && drag) {
                pressed_ = false;
                Event::hover_disable = false;
                drag_subscribes.erase(drag);

                break;
            }
            
            if (pressed_) {
                pressed_ = false;
                Event::hover_disable = false;

                back_color_.inverse();
                hovered_ = false;
                if (check_coordinates(event.x, event.y)) {
                    functor(this);
                    hovered_ = true;
                    back_color_.lighter();
                }
            }
            break;

        case Event::HOVERED:
            if (!hovered_) {
                hovered_ = true;
                back_color_.lighter();
            }
            break;

        case Event::UNHOVERED:
            if (hovered_ && !pressed_ && !check_coordinates(event.x, event.y)) {
                hovered_ = false;   
                back_color_.de_lighter();
            }
            break;
        }

        return true;
    }

    

    // void draw()
    // {
    //     Window::draw();

    //     draw_sub_windows();
    // }


};