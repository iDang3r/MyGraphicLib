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

class App
{
private:
    // Engine engine;

public:

    App() 
    {
        Engine::init();

        Engine::create_system_window(Point(0.4, 0.4), 1.1, 1.0);
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
