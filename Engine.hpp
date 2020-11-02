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
    #include "Button_round.hpp"
    #include "Label.hpp"

    #include "engine_fuctors.hpp"

    static int valid_id_;

    static std::set<Object*>        system_windows;
    static std::map<int, Object*>   all_objects;

    static void event_processing()
    {
        wait_events();

        while (!Event::empty()) {
            Event_t event = Event::get();
            // std::cout << "Event: " << event.id << " " << event.x << " " << event.y << std::endl;

            for (auto sys_window : system_windows) {
                Window* window = dynamic_cast<Window*>(sys_window);
                if (window == nullptr) {
                    continue;
                }

                bool u = window->check_mouse(event);
                if (u) {
                    break;
                }
            }
        }
    }

    static void render() 
    {
        before_rendering();

        for (auto sys_window : system_windows) {
            sys_window->draw();
        }

        after_rendering();
    }

    static int create_window(const Point &start, double width, double height, const Color &color = COLORS::window) 
    {
        Window* new_window = new Window(start, width, height, color);
        // all_objects[new_window->id_] = dynamic_cast<Object*>(new_window);

        return new_window->id_;
    }

    static int create_system_window(const Point &start, double width, double height, const Color &color = COLORS::sys_window) 
    {
        System_window* new_sys_window = new System_window(start, width, height, color);
        // all_objects[new_sys_window->id_] = dynamic_cast<Object*>(new_sys_window);
        system_windows.insert(new_sys_window);
    
        return new_sys_window->id_;
    }

    template <typename Functor>
    static int create_button(int window_id, const Point &start, double width, double height, Functor functor, const char* label, const Color &color = COLORS::button) 
    {
        Window* window = dynamic_cast<Window*>(all_objects[window_id]);
        if (window == nullptr) {
            return -1;
        }

        double button_width  = width  * window->width_;
        double button_height = height * window->height_;
        Point  button_start(start.x + window->start_.x, start.y + window->start_.y);
        Button<Functor>* new_button = new Button(button_start, button_width, button_height, color, functor, label);
        
        window->sub_objects.insert(new_button);
        // all_objects[new_button->id_] = dynamic_cast<Object*>(new_button);

        return new_button->id_;
    }

    template <typename Functor>
    static int create_round_button(int window_id, const Point &start, double radius_x, Functor functor, const Color &color = COLORS::button) 
    {
        Window* window = dynamic_cast<Window*>(all_objects[window_id]);
        if (window == nullptr) {
            std::cout << "create_round_button: ";
            w(window_id);
            return -1;
        }

        double button_width  = radius_x *                 window->width_;
        double button_height = radius_x * window_w_to_h * window->height_;
        Point  button_start(start.x + window->start_.x, start.y + window->start_.y);
        Button_round<Functor>* new_button = new Button_round(button_start, radius_x, color, functor);
        
        window->sub_objects.insert(new_button);
        // all_objects[new_button->id_] = dynamic_cast<Object*>(new_button);

        return new_button->id_;
    }

    static int delete_window(int id);

};

int Engine::valid_id_ = 1;
std::set<Engine::Object*>       Engine::system_windows;
std::map<int, Engine::Object*>  Engine::all_objects;