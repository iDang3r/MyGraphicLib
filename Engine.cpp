#include "Engine.hpp"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void Engine::event_processing()
{
    wait_events();

    while (!Event::empty()) {
        Event_t event = Event::get();
        // std::cout << "Event: " << event.id << " " << event.x << " " << event.y << std::endl;

        if (event.id == Event::CLICK || event.id == Event::HOVERED) {
            for (auto sys_window : system_windows) {

                bool u = sys_window->check_mouse(event);
                if (u) {
                    break;
                }
            }
            continue;
        }

        if (event.id == Event::MOUSE_MOVE) {
            for (auto drag : drag_subscribes) {
                drag->move(event);
            }
        }
        
        for (auto subscr_object : subscribes[event.id]) {
            subscr_object->handle(event);
        }
        
    }
}

void Engine::render() 
{
    before_rendering();

    for (auto sys_window : system_windows) {
        sys_window->draw();
    }

    after_rendering();
}

Engine::Coordinates_convertion Engine::convert_coordinates(const Point &start, double width, double height, Window* window) 
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

int Engine::create_system_window(const Point &start, double width, double height, const Color &color) 
{
    System_window* new_sys_window = new System_window(start, width, height, color);
    system_windows.insert(new_sys_window);

    return new_sys_window->id_;
}

int Engine::create_window(int window_id, const Point &start, double width, double height, const Color &color) 
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

int Engine::create_label(int window_id, const Point &start, double width, double height, const char* label, const Color &color) 
{
    Window* window = dynamic_cast<Window*>(all_objects[window_id]);
    if (window == nullptr) {
        return -1;
    }

    Coordinates_convertion conv = convert_coordinates(start, width, height, window);
    Label* new_label = new Label(conv.start, conv.width, conv.height, label, color);
    
    window->sub_objects.push_back(new_label);

    return new_label->id_;
}

int Engine::create_image(int window_id, const Point &start, double width, double height, const char* source_path) 
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

int Engine::create_scroll_bar(int window_id, const Point &start, double width, double height) 
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

int Engine::set_window_color(int window_id, const Color &color)
{
    Window* window = dynamic_cast<Window*>(all_objects[window_id]);
    if (window == nullptr) {
        dump(DUMP_INFO, "False window id to set color");
        return -1;
    }

    window->back_color_ = color;

    return 0;
}

int Engine::set_label_lefty(int label_id)
{
    Label* label = dynamic_cast<Label*>(all_objects[label_id]);
    if (label == nullptr) {
        dump(DUMP_INFO, "False label id to set lefty");
        return -1;
    }
    
    label->set_lefty();

    return 0;
}

int Engine::set_label_text(int label_id, const char* str)
{
    Label* label = dynamic_cast<Label*>(all_objects[label_id]);
    if (label == nullptr) {
        dump(DUMP_INFO, "False label id to set text");
        return -1;
    }
    
    label->set_text(str);

    return 0;
}

int Engine::create_canvas(int window_id, const Point &start, double width, double height) 
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

int Engine::create_tool_manager(int window_id, const Point &start, double width, double height, Color& during_color, int& thickness, Canvas& canvas) 
{
    Window* window = dynamic_cast<Window*>(all_objects[window_id]);
    if (window == nullptr) {
        return -1;
    }

    Coordinates_convertion conv = convert_coordinates(start, width, height, window);
    Tool_manager* new_tool_manager = new Tool_manager(conv.start, conv.width, conv.height, during_color, thickness, canvas);
    
    window->sub_objects.push_back(new_tool_manager);

    return new_tool_manager->id_;
}

int Engine::create_palette(int window_id, const Point &start, double width, double height) 
{
    Window* window = dynamic_cast<Window*>(all_objects[window_id]);
    if (window == nullptr) {
        return -1;
    }

    Coordinates_convertion conv = convert_coordinates(start, width, height, window);
    Palette* new_palette = new Palette(conv.start, conv.width, conv.height);
    
    window->sub_objects.push_back(new_palette);

    return new_palette->id_;
}

int Engine::create_thickness(int window_id, const Point &start, double width, double height) 
{
    Window* window = dynamic_cast<Window*>(all_objects[window_id]);
    if (window == nullptr) {
        return -1;
    }

    Coordinates_convertion conv = convert_coordinates(start, width, height, window);
    Thickness* new_thickness = new Thickness(conv.start, conv.width, conv.height);
    
    window->sub_objects.push_back(new_thickness);

    return new_thickness->id_;
}

int Engine::create_painter(int window_id, const Point &start, double width, double height) 
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

void Engine::delete_window(int id) 
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

bool Engine::is_window_exists(int id)
{
    return NULL != all_objects[id];
}

int Engine::valid_id_ = 1;
std::set<Engine::Object*>                   Engine::system_windows;
std::map<int, Engine::Object*>              Engine::all_objects;
std::vector<std::set<Engine::Object*>>      Engine::subscribes(Event::num_event_types);
std::set<Engine::Window::Dragable*>         Engine::drag_subscribes;

