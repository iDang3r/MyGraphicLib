#pragma once

#include "Tool.hpp"

class Plugin : public Tool
{
private:
public:
    void*               dl_ptr = nullptr;
    PluginAPI::Plugin*  plugin = nullptr;

    bool                using_ = false;  

    Plugin(const std::string &name);

    ~Plugin();

    void set_thickness(int thickness);

    void set_color(const Color &color);

    // bool handle(const Event_t& event);

    // bool check_mouse(const Event_t &event);

    void use(Canvas &canvas, const Event_t &event);

};