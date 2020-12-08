#pragma once 

#include "Tool.hpp"
#include "Window.hpp"

class Set_tool;

class Tool_manager : public Window
{
private:
public:
    int active_tool = 0;
    std::vector<std::pair<Tool*, int>> tools;

    Tool_manager(const Point &start, double width, double height) :
        Window(start, width, height, COLORS::tool_manager)
    {
        double up_size = 0.02 + 0.35 / height_ * width_ * Engine::window_w_to_h;
        add_tool(Point(0.1,  0.02),           0.35, new Zoom_down_tool(), "zoom_down.png");
        add_tool(Point(0.55, 0.02),           0.35, new Zoom_up_tool(),   "zoom_up.png");
        add_tool(Point(0.1,  0.02 + up_size), 0.35, new Hand_tool(),      "hand.png");
        add_tool(Point(0.55, 0.02 + up_size), 0.35, new Brush_tool(),     "brush.png");

        set_active_tool(0);
    }

    void use_tool(Canvas &canvas, const Event_t &event)
    {
        tools[active_tool].first->use(canvas, event);
    }

    void set_active_tool(int new_active_tool)
    {
        Engine::set_window_color(tools[active_tool].second, COLORS::clear);
        active_tool = new_active_tool;
        Engine::set_window_color(tools[active_tool].second, COLORS::red);
    }

    void add_tool(const Point &point, double width, Tool* tool, const char* source)
    {
        double k = 0.1; // frame size
        double d_x = k * width;
        double d_y = k * width / height_ * width_ * Engine::window_w_to_h;
        int frame_id = Engine::create_window(id_, point - Point(d_x, d_y), width + 2 * d_x, width / height_ * width_ * Engine::window_w_to_h + 2 * d_y, COLORS::clear);
        tools.push_back({tool, frame_id});
        Engine::create_button(id_, point, width, width / height_ * width_ * Engine::window_w_to_h, Set_tool(this, tools.size() - 1), NULL, source, COLORS::tool);
    }

};

class Set_tool
{
public:
    Tool_manager*   tool_manager;
    int             tool;

    Set_tool(Tool_manager* tool_manager, int tool) : tool_manager(tool_manager), tool(tool) {}

    void operator()(Engine::Button<Set_tool>* button)
    {
        tool_manager->set_active_tool(tool);
    }
};