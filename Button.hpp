#pragma once

#include "Window.hpp"

template <typename Functor>
class Button : public Window 
{
private:
public:

    Functor functor;

    Button(const Point &start, double width, double height, 
        const Color &color, Functor functor, const char* label = NULL, const char* img_source = NULL);

    ~Button();

    bool handle(const Event_t &event);

};