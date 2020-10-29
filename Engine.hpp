#pragma once

#include "Engine_OpenGL.hpp"

#include "Event.hpp"

using Engine_t = Engine_OpenGL;

class Engine : public Engine_OpenGL
{
private:
public:
    #include "Object.hpp"
    #include "Window.hpp"
    #include "System_window.hpp"
    #include "Button.hpp"

    static int valid_id_;

    static std::set<Object*> objects;

    static void render() {

        // glLoadIdentity();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the buffers

        glClearColor(H(0xFF), H(0xD0), H(0x7B), 0.3);

        Engine::draw_square(Point(0.1, 0.1), 0.4);

        Engine::draw_circle(Point(1, 1), 0.5);

        for (auto object : objects) {
            object->draw();
        }

        glFlush();

    }

    static int create_window(const Point &start, double width, double height, const Color &color = COLORS::window) {

        Window* new_window = new Window(start, width, height, color);
        objects.insert(dynamic_cast<Object*>(new_window));
    }

    static int create_system_window(const Point &start, double width, double height, const Color &color = COLORS::sys_window) {

        System_window* new_sys_window = new System_window(start, width, height, color);
        objects.insert(dynamic_cast<Object*>(new_sys_window));
    }

    static int delete_window(int id);

};

int Engine::valid_id_ = 1;
std::set<Engine::Object*> Engine::objects;