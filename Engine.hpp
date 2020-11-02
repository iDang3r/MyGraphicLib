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

    static std::map<int, Object*> system_windows;

    static void event_processing()
    {
        wait_events();

        while (!Event::empty()) {
            Event_t event = Event::get();
            std::cout << "Event: " << event.id << " " << event.x << " " << event.y << std::endl;

            for (auto& sys_window : system_windows) {
                Window* window = dynamic_cast<Window*>(sys_window.second);
                if (window == nullptr) {
                    continue;
                }

                // Event_t new_event(event.id, event.x - window->start_.x, event.y - window->start_.y);
                // if (new_event.x < 0 || new_event.y < 0) {
                //     continue;
                // }

                // bool u = window->check_mouse(new_event);
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
            sys_window.second->draw();
        }

        // Engine::draw_circle(Point(1.0, 1.0), 0.3);

        after_rendering();
    }

    static int create_window(const Point &start, double width, double height, const Color &color = COLORS::window) 
    {
        Window* new_window = new Window(start, width, height, color);
        system_windows[valid_id_] = dynamic_cast<Object*>(new_window);

        return valid_id_++;
    }

    static int create_system_window(const Point &start, double width, double height, const Color &color = COLORS::sys_window) 
    {
        System_window* new_sys_window = new System_window(start, width, height, color);
        system_windows[valid_id_] = dynamic_cast<Object*>(new_sys_window);
    
        return valid_id_++;
    }

    template <typename Functor>
    static int create_button(int window_id, const Point &start, double width, double height, Functor functor, const Color &color = COLORS::button) 
    {
        Window* window = dynamic_cast<Window*>(system_windows[window_id]);
        if (window == nullptr) {
            return -1;
        }

        double button_width  = width  * window->width_;
        double button_height = height * window->height_;
        Point  button_start(start.x + window->start_.x, start.y + window->start_.y);
        Button<Functor>* new_button = new Button(window_id, button_start, button_width, button_height, color, functor);
        
        window->sub_objects.insert(new_button);

        return valid_id_++;
    }

    static int delete_window(int id);

};

int Engine::valid_id_ = 1;
std::map<int, Engine::Object*> Engine::system_windows;