#pragma once

#include <string>
// #include "Engine_OpenGL.hpp"
#include "Engine_SFML.hpp"

// using Engine_t = Engine_OpenGL;
using Engine_t = Engine_SFML;

class Engine : public Engine_t
{
private:
public:
    #include "Event.hpp"
    #include "Dragable.hpp"

    #include "Object.hpp"
    #include "Window.hpp"

    #include "System_window.hpp"
    #include "Button.hpp"
    #include "Button_round.hpp"
    // #include "Button_polished.hpp"
    #include "Label.hpp"
    #include "Image.hpp"
    #include "Scroll_bar.hpp"

    #include "Canvas.hpp"
    #include "Painter.hpp"

    #include "engine_fuctors.hpp"

    static int valid_id_;

    static std::set<Object*>                    system_windows;
    static std::map<int, Object*>               all_objects;
    static std::vector<std::set<Object*>>       subscribes;
    static std::set<Dragable*>                  drag_subscribes;

    static void event_processing()
    {
        wait_events();

        while (!Event::empty()) {
            Event_t event = Event::get();
            // std::cout << "Event: " << event.id << " " << event.x << " " << event.y << std::endl;

            if (event.id == Event::CLICK || event.id == Event::HOVERED) {// || event.id == Event::RELEASE) {
                for (auto sys_window : system_windows) {

                    bool u = sys_window->check_mouse(event);
                    if (u) {
                        break;
                    }
                }
            }

            if (event.id == Event::RELEASE || event.id == Event::UNHOVERED || event.id == Event::MOUSE_MOVE) {
                for (auto subscr_object : subscribes[event.id]) {
                    subscr_object->handle(event);
                }
            }

            if (event.id == Event::MOUSE_MOVE) {
                for (auto drag : drag_subscribes) {
                    drag->move(event);
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

    struct Coordinates_convertion 
    {
        Point  start;
        double width;
        double height;
    };

    static Coordinates_convertion convert_coordinates(const Point &start, double width, double height, Window* window) 
    {
        Coordinates_convertion ret = 
        {
            .start  = start,
            .width  = width,
            .height = height,
        };

        System_window* system_w = dynamic_cast<System_window*>(window);
        if (system_w == NULL) {
            ret.width  *= window->width_;
            ret.height *= window->height_;
            ret.start = Point(window->width_* start.x + window->start_.x, window->height_ * start.y + window->start_.y);
        } else {
            ret.width  *= system_w->real_width;
            ret.height *= system_w->real_height;
            ret.start = Point(system_w->real_width * start.x + system_w->start_.x, system_w->real_height * start.y + system_w->start_.y);
        }

        return ret;
    }

    static int create_system_window(const Point &start, double width, double height, const Color &color = COLORS::sys_window) 
    {
        System_window* new_sys_window = new System_window(start, width, height, color);
        system_windows.insert(new_sys_window);
    
        return new_sys_window->id_;
    }

    static int create_window(int window_id, const Point &start, double width, double height, const Color &color = COLORS::window) 
    {
        Window* window = dynamic_cast<Window*>(all_objects[window_id]);
        if (window == nullptr) {
            return -1;
        }

        Coordinates_convertion conv = convert_coordinates(start, width, height, window);
        Window* new_window = new Window(conv.start, conv.width, conv.height, color);
        
        window->sub_objects.push_back(new_window);

        return new_window->id_;
    }

    static int create_label(int window_id, const Point &start, double width, double height, const char* label) 
    {
        Window* window = dynamic_cast<Window*>(all_objects[window_id]);
        if (window == nullptr) {
            return -1;
        }

        Coordinates_convertion conv = convert_coordinates(start, width, height, window);
        Label* new_label = new Label(conv.start, conv.width, conv.height, label);
        
        window->sub_objects.push_back(new_label);

        return new_label->id_;
    }

    static int create_image(int window_id, const Point &start, double width, double height, const char* source_path) 
    {
        Window* window = dynamic_cast<Window*>(all_objects[window_id]);
        if (window == nullptr) {
            return -1;
        }

        Coordinates_convertion conv = convert_coordinates(start, width, height, window);
        Image* new_image = new Image(conv.start, conv.width, conv.height, source_path);
        
        window->sub_objects.push_back(new_image);

        return new_image->id_;
    }

    template <typename Functor>
    static int create_button(int window_id, const Point &start, double width, double height, Functor functor, const char* label, const char* img_source, const Color &color = COLORS::button) 
    {
        Window* window = dynamic_cast<Window*>(all_objects[window_id]);
        if (window == nullptr) {
            return -1;
        }

        Coordinates_convertion conv = convert_coordinates(start, width, height, window);
        Button<Functor>* new_button = new Button(conv.start, conv.width, conv.height, color, functor, label, img_source);
        
        window->sub_objects.push_back(new_button);

        return new_button->id_;
    }

    template <typename Functor>
    static int create_round_button(int window_id, const Point &start, double radius_x, Functor functor, const Color &color = COLORS::button) 
    {
        Window* window = dynamic_cast<Window*>(all_objects[window_id]);
        if (window == nullptr) {
            std::cout << "create_round_button: ";
            ww(window_id);
            return -1;
        }

        Coordinates_convertion conv = convert_coordinates(start, radius_x, radius_x * window_w_to_h, window);
        Button_round<Functor>* new_button = new Button_round(conv.start, conv.width, color, functor);
        
        window->sub_objects.push_back(new_button);

        return new_button->id_;
    }

    static int create_scroll_bar(int window_id, const Point &start, double width, double height) 
    {
        Window* window = dynamic_cast<Window*>(all_objects[window_id]);
        if (window == nullptr) {
            std::cout << "create_scroll_bar: ";
            ww(window_id);
            dump(DUMP_INFO, "False id");
            return -1;
        }

        Coordinates_convertion conv = convert_coordinates(start, width, height, window);
        Scroll_bar* new_scroll_bar = new Scroll_bar(conv.start, conv.width, conv.height);

        window->sub_objects.push_back(new_scroll_bar);

        return new_scroll_bar->id_;
    }

    static int set_window_color(int window_id, const Color &color)
    {
        Window* window = dynamic_cast<Window*>(all_objects[window_id]);
        if (window == nullptr) {
            dump(DUMP_INFO, "False window id to set color");
            return -1;
        }

        window->back_color_ = color;
    }

    static int create_canvas(int window_id, const Point &start, double width, double height) 
    {
        Window* window = dynamic_cast<Window*>(all_objects[window_id]);
        if (window == nullptr) {
            return -1;
        }

        Coordinates_convertion conv = convert_coordinates(start, width, height, window);
        Canvas* new_canvas = new Canvas(conv.start, conv.width, conv.height);
        
        window->sub_objects.push_back(new_canvas);

        return new_canvas->id_;
    }

    static int create_tool_manager(int window_id, const Point &start, double width, double height) 
    {
        Window* window = dynamic_cast<Window*>(all_objects[window_id]);
        if (window == nullptr) {
            return -1;
        }

        Coordinates_convertion conv = convert_coordinates(start, width, height, window);
        Tool_manager* new_tool_manager = new Tool_manager(conv.start, conv.width, conv.height);
        
        window->sub_objects.push_back(new_tool_manager);

        return new_tool_manager->id_;
    }

    static int create_painter(int window_id, const Point &start, double width, double height) 
    {
        Window* window = dynamic_cast<Window*>(all_objects[window_id]);
        if (window == nullptr) {
            return -1;
        }

        Coordinates_convertion conv = convert_coordinates(start, width, height, window);
        Painter* new_painter = new Painter(conv.start, conv.width, conv.height);
        
        window->sub_objects.push_back(new_painter);

        return new_painter->id_;
    }

    static void delete_window(int id) 
    {
        Object* obj = all_objects[id];
        if (obj == NULL) {
            dump(DUMP_INFO, "False object id to close");
            return;
        }
        obj->close();

        if (dynamic_cast<System_window*>(obj)) {
            system_windows.erase(obj);
        }
        // delete obj;
    }

};

int Engine::valid_id_ = 1;
std::set<Engine::Object*>                   Engine::system_windows;
std::map<int, Engine::Object*>              Engine::all_objects;
std::vector<std::set<Engine::Object*>>      Engine::subscribes(Event::num_event_types);
std::set<Engine::Dragable*>                 Engine::drag_subscribes;