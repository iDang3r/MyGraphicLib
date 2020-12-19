#pragma once

#include <string>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "Plugins/api.hpp"

#include <set>
// #include "Engine_OpenGL.hpp"
#include "Engine_SFML.hpp"

#include "ColorPanel/MyCPPClass.h"

// using Engine_t = Engine_OpenGL;
using Engine_t = Engine_SFML;

class Engine : public Engine_t
{
private:
public:
    #include "Event.hpp"

    #include "Object.hpp"
    #include "Window.hpp"

    #include "System_window.hpp"
    #include "Button.hpp"
    #include "Button_round.hpp"
    // #include "Button_polished.hpp"
    #include "Label.hpp"
    #include "Image.hpp"
    #include "Scroll_bar.hpp"

    #include "Painter.hpp"

    #include "engine_fuctors.hpp"

    static int valid_id_;

    static std::set<Object*>                    system_windows;
    static std::map<int, Object*>               all_objects;
    static std::vector<std::set<Object*>>       subscribes;
    static std::set<Window::Dragable*>          drag_subscribes;

    static void event_processing();

    static void render();

    struct Coordinates_convertion 
    {
        Point  start;
        double width;
        double height;
    };

    static Coordinates_convertion convert_coordinates(const Point &start, double width, double height, Window* window);

    static int create_system_window(const Point &start, double width, double height, const Color &color = COLORS::sys_window);

    static int create_window(int window_id, const Point &start, double width, double height, const Color &color = COLORS::window);

    static int create_label(int window_id, const Point &start, double width, double height, const char* label, const Color &color = COLORS::clear);

    static int create_image(int window_id, const Point &start, double width, double height, const char* source_path);

    template <typename Functor>
    static int create_button(int window_id, const Point &start, double width, double height, Functor functor, const char* label, const char* img_source, const Color &color = COLORS::button);

    template <typename Functor>
    static int create_round_button(int window_id, const Point &start, double radius_x, Functor functor, const Color &color = COLORS::button);

    template <typename Functor>
    static int create_slider(int window_id, const Point &start, double width, double height, int min_value, int max_value, Functor functor);

    static int create_scroll_bar(int window_id, const Point &start, double width, double height);

    static int set_window_color(int window_id, const Color &color);

    static int set_label_lefty(int label_id);

    static int set_label_text(int label_id, const char* str);

    static int create_canvas(int window_id, const Point &start, double width, double height);

    static int create_tool_manager(int window_id, const Point &start, double width, double height, Color& during_color, int& thickness, Canvas& canvas);

    static int create_palette(int window_id, const Point &start, double width, double height);

    static int create_thickness(int window_id, const Point &start, double width, double height);

    static int create_painter(int window_id, const Point &start, double width, double height);

    static void delete_window(int id);

    static bool is_window_exists(int id);

};

#include "Engine_tmpl.hpp"