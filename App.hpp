#pragma once

#include <iostream>
#include <cstdio>

#include "Engine_OpenGL.hpp"

using Engine_t = Engine_OpenGL;

class App
{
private:
    static Engine_t Engine;

public:

    static void init() 
    {
        Engine.init();
    }

    static void terminate() 
    {
        Engine.terminate();
    }

    static void run() 
    {
        while (Engine.is_run()) {

            glfwWaitEvents();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the buffers

            glClearColor(H(0xFF), H(0xD0), H(0x7B), 0.3);

        }
        
    }

};
