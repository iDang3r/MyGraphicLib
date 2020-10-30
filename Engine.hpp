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

    static std::map<int, Object*> objects;

    static void event_processing()
    {
        glfwWaitEvents();

        while (!Event::empty()) {
            Event_t event = Event::get();
            std::cout << "Event: " << event.id << " " << event.x << " " << event.y << std::endl;

            for (auto& object : objects) {
                
            }
        }
    }

    static void render() 
    {
        before_rendering();

        for (auto object : objects) {
            object.second->draw();
        }

        after_rendering();
    }

    static int create_window(const Point &start, double width, double height, const Color &color = COLORS::window) {

        Window* new_window = new Window(start, width, height, color);
        objects[valid_id_] = dynamic_cast<Object*>(new_window);

        return valid_id_++;
    }

    static int create_system_window(const Point &start, double width, double height, const Color &color = COLORS::sys_window) {

        System_window* new_sys_window = new System_window(start, width, height, color);
        objects[valid_id_] = dynamic_cast<Object*>(new_sys_window);
    
        return valid_id_++;
    }

    static int delete_window(int id);

};

int Engine::valid_id_ = 1;
std::map<int, Engine::Object*> Engine::objects;