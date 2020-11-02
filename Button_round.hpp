#pragma once

#include "Button.hpp"

template <typename Functor>
class Button_round : public Button 
{
private:
public:

    Button_round(int window_id, const Point &start, double radus_x,
        const Color &color, Functor functor)
        : Window(start, 2 * radus_x, 2 * radus_x * window_w_to_h, color), functor(functor)
    {
        std::cout << "Round Button: " << start << ", radus_x: " << radus_x  << std::endl;
    }

};