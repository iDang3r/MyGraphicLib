#pragma once

// #include "Button.hpp"

class First_functor
{
public:
    void operator()(Engine::Button<First_functor>* button)
    {
        std::cout << "----------------------> FUNCTOR was called" << std::endl;
    }
};