#pragma once 

#include "Tool.hpp"
#include "Window.hpp"

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
        tools.push_back(new Hand_tool());
        tools.push_back(new Zoom_up_tool());
    }

    void use_tool(Canvas &canvas, const Event_t &event)
    {
        // ws("USE active tool");
        tools[active_tool]->use(canvas, event);
    }

    void add_tool()
    {
        
    }

};

