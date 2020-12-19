#include <dlfcn.h>
#include <memory>
#include "dump.h"

#include "Plugins/api.hpp"

#include "Engine.hpp"

Engine::Plugin::Plugin(const std::string &name)
{
    dl_ptr = dlopen(("Plugins/" + name + "/" + name + ".so").c_str(), RTLD_NOW);

    if (nullptr == dl_ptr) {
        dump(DUMP_INFO, dlerror());
        exit(1);
    }

    PluginAPI::Plugin* (*get_plugin)() = 
        reinterpret_cast<PluginAPI::Plugin* (*)()>(dlsym(dl_ptr, "get_plugin"));

    if (nullptr == get_plugin) {
        dump(DUMP_INFO, dlerror());
        dlclose(dl_ptr);
        exit(1);
    }

    plugin = get_plugin();

    plugin->init();

    // subscribes[Event::RELEASE].insert(this);

    plugin->properties[PluginAPI::TYPE::THICKNESS].int_value = 10;
}

Engine::Plugin::~Plugin()
{
    // subscribes[Event::RELEASE].erase(this);

    if (plugin) {
        plugin->deinit();
    } else {
        dump(DUMP_INFO, "UNKNOWN ERROR");
    }

    if (dl_ptr) {
        dlclose(dl_ptr);
    } else {
        dump(DUMP_INFO, "UNKNOWN ERROR");
    }
}

void Engine::Plugin::set_thickness(int thickness) 
{
    plugin->properties[PluginAPI::TYPE::THICKNESS].int_value = thickness;
}

void Engine::Plugin::set_color(const Color &color)
{
    plugin->properties[PluginAPI::TYPE::PRIMARY_COLOR].int_value = color;
}

// bool Engine::Plugin::handle(const Event_t& event)
// {
//     if (event.id == Event::RELEASE) {
//         using_ = false;
//         return true;
//     }
//     return false;
// }

// bool Engine::Plugin::check_mouse(const Event_t &event)
// {
//     return false;
// }

void Engine::Plugin::use(Canvas &canvas, const Event_t &event)
{
    if (event.id == Event::CLICK) {
        using_ = true;

        ws("PLUGIN CLICK!");

        PluginAPI::Canvas plug_canvas = {
            .pixels = reinterpret_cast<uint8_t*>(canvas.pixel_array_.start),
            .width  = static_cast<size_t>(canvas.pixel_array_.width),
            .height = static_cast<size_t>(canvas.pixel_array_.height),
        };
        PluginAPI::Position plug_pos = {canvas.get_px_x(event.x), canvas.get_px_y(event.y)};

        set_thickness(thickness_);
        set_color(color_);

        ws("start_apply");
        plugin->start_apply(plug_canvas, plug_pos);
        ws("start done");

        Event::hover_disable = true;
        return;
    }

    if (using_ && event.id == Event::MOUSE_MOVE) {
        
        return;
    }

    if (using_ && event.id == Event::RELEASE) {


        using_ = false;
        Event::hover_disable = false;
        return;
    }
}