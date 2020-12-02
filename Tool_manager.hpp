#pragma once 

#include "Tool.hpp"
#include "Window.hpp"

class Tool_manager : public Window
{
private:
public:
    Tool_manager(const Point &start, double width, double height) :
        Window(start, width, height, COLORS::tool_manager)
    {
        
    }

};

