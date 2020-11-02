#pragma once

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <queue>

#include "Engine.hpp"
#include "button_functors.hpp"

class App
{
private:

public:

    App() 
    {
        Engine::init();

        int id;
        id = Engine::create_system_window(Point(0.2, 0.3), 0.55, 0.5);
        Engine::create_button(id, Point(0.05, 0.075), 0.1, 0.075, First_functor());
    }

    ~App() 
    {
        Engine::terminate();
    }

    void run() 
    {
        while (Engine::is_run()) {

            Engine::event_processing();

            Engine::render();

        }
        
    }

};
