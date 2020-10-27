#pragma once

#include <iostream>
#include <cstdio>

#include "Engine.hpp"

class App
{
private:
    Engine engine;

public:

    App() 
    {
        engine.init();
    }

    ~App() 
    {
        engine.terminate();
    }

    void run() 
    {
        while (engine.is_run()) {

            glfwWaitEvents();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the buffers

            glClearColor(H(0xFF), H(0xD0), H(0x7B), 0.3);

            engine.swap_buffers();
        }
        
    }

};
