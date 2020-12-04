#pragma once

#include "Window.hpp"

#include "Canvas.hpp"
#include "Tool_manager.hpp"

class Painter : public Window
{
private:
public:
    Canvas*         canvas;
    Tool_manager*   tool_manager;

    Painter(const Point &start, double width, double height) :
        Window(start, width, height, COLORS::painter)
    {
        subscribes[Event::MOUSE_MOVE].insert(this);

        int tool_manger_id = Engine::create_tool_manager(id_, Point(0.84, 0.02), 0.14, 0.96);
        tool_manager = dynamic_cast<Tool_manager*>(all_objects[tool_manger_id]);

        int canvas_id = Engine::create_canvas(id_, Point(0.02, 0.02), 0.8, 0.96);
        canvas = dynamic_cast<Canvas*>(all_objects[canvas_id]);
    }

    ~Painter()
    {
        subscribes[Event::MOUSE_MOVE].erase(this);
    }

    bool handle(const Event_t &event)
    {
        if (event.id == Event::MOUSE_MOVE) {
            tool_manager->use_tool(*canvas, event);
        }
    }

    bool check_mouse(const Event_t &event) 
    {
        if (event.x < start_.x || event.y < start_.y 
            || event.x > start_.x + width_ || event.y > start_.y + height_) {
            return false;
        }

        // for (auto it = sub_objects.rbegin(); it != sub_objects.rend(); ++it) {

        //     bool u = (*it)->check_mouse(event);
        //     if (u) {
        //         return true;
        //     }
        // }

        if (canvas->check_mouse(event) || event.id == Event::RELEASE) {
            tool_manager->use_tool(*canvas, event);
            return true;
        }

        tool_manager->check_mouse(event);

        return handle(event);
    }

};