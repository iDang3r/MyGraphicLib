#pragma once

#include "Window.hpp"

#include "Canvas.hpp"
#include "Tool_manager.hpp"
#include "Palette.hpp"
#include "Thickness.hpp"

class Painter : public Window
{
private:
public:
    Canvas*         canvas       = nullptr;
    Tool_manager*   tool_manager = nullptr;
    Palette*        palette      = nullptr;
    Thickness*      thickness    = nullptr;

    Painter(const Point &start, double width, double height) :
        Window(start, width, height, COLORS::painter)
    {
        subscribes[Event::MOUSE_MOVE].insert(this);

        int canvas_id = Engine::create_canvas(id_, Point(0.02, 0.02), 0.8, 0.96);
        canvas = dynamic_cast<Canvas*>(all_objects[canvas_id]);

        int palette_id = Engine::create_palette(id_, Point(0.84, 0.84), 0.14, 0.14);
        palette = dynamic_cast<Palette*>(all_objects[palette_id]);

        int thickness_id = Engine::create_thickness(id_, Point(0.84, 0.72), 0.14, 0.10);
        thickness = dynamic_cast<Thickness*>(all_objects[thickness_id]);

        int tool_manger_id = Engine::create_tool_manager(id_, Point(0.84, 0.02), 0.14, 0.68, palette->color, thickness->thickness, *canvas);
        tool_manager = dynamic_cast<Tool_manager*>(all_objects[tool_manger_id]);
    }

    ~Painter()
    {
        subscribes[Event::MOUSE_MOVE].erase(this);
    }

    bool handle(const Event_t &event)
    {
        if (event.id == Event::MOUSE_MOVE) {
            tool_manager->use_tool(*canvas, event);
            return true;
        }
        return false;
    }

    bool check_mouse(const Event_t &event) 
    {
        if (event.x < start_.x || event.y < start_.y 
            || event.x > start_.x + width_ || event.y > start_.y + height_) {
            return false;
        }

        if (canvas->check_mouse(event) || event.id == Event::RELEASE) {
            tool_manager->use_tool(*canvas, event);
            return true;
        }

        tool_manager->check_mouse(event);
        palette->check_mouse(event);
        thickness->check_mouse(event);

        return handle(event);
    }

};