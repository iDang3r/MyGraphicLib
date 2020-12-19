#pragma once

#include "Button.hpp"

template <typename Functor>
class Button_round : public Button<Functor>
{
private:
public:

    Button_round(const Point &start, double radius_x, const Color &color, Functor functor);

    void draw();

};