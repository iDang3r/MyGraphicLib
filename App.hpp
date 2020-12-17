#pragma once

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <string>
#include <cassert>

#include "Engine.hpp"
#include "button_functors.hpp"

class App
{
private:

public:

    App() 
    {
        Engine::init();

        int id = Engine::create_system_window(Point(0.01, 0.02), 0.25, 0.25);
        Engine::create_button(id, Point(0.05, 0.075), 0.15, 0.1, First_functor(), "button!", NULL);
        Engine::create_button(id, Point(0.5, 0.1), 0.08, 0.2, First_functor(), NULL, "pencil.png");
        Engine::create_scroll_bar(id, Point(0.98, 0.0), 0.02, 1.0);

        int paint_id = Engine::create_system_window(Point(0.3, 0.25), 0.65, 0.7);
        Engine::create_painter(paint_id, Point(0.0, 0.0), 1.0, 1.0);

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
