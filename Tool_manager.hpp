#pragma once 

#include "Tool.hpp"
#include "Window.hpp"

class Set_tool;

class Tool_manager : public Window
{
private:
public:
    int active_tool;
    std::vector<Tool*> tools;

    Tool_manager(const Point &start, double width, double height) :
        Window(start, width, height, COLORS::tool_manager)
    {
        active_tool = 0;
        double up_size = 0.02 + 0.35 / height_ * width_ * Engine::window_w_to_h;
        add_tool(Point(0.1,  0.02),           0.35, new Zoom_down_tool(), "zoom_down.png");
        add_tool(Point(0.55, 0.02),           0.35, new Zoom_up_tool(),   "zoom_up.png");
        add_tool(Point(0.1,  0.02 + up_size), 0.35, new Hand_tool(),      "hand.png");
        add_tool(Point(0.55, 0.02 + up_size), 0.35, new Brush_tool(),     "brush.png");
    }

    void use_tool(Canvas &canvas, const Event_t &event)
    {
        tools[active_tool]->use(canvas, event);
    }

    void set_active_tool(int new_active_tool)
    {
        active_tool = new_active_tool;
    }

    void add_tool(const Point &point, double width, Tool* tool, const char* source)
    {
        tools.push_back(tool);
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