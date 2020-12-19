#include "Engine.hpp"

Engine::Tool::Tool()
{
    subscribes[Event::RELEASE].insert(this);
}

Engine::Tool::Tool(const Color &color, int thickness, Type enum_type) : color_(color), thickness_(thickness), type(enum_type) 
{
    subscribes[Event::RELEASE].insert(this);
}

Engine::Tool::~Tool() 
{
    subscribes[Event::RELEASE].erase(this);
}

void Engine::Tool::set_color(const Color &color) 
{
    color_ = color;
}

void Engine::Tool::set_thickness(int thickness) 
{
    thickness_ = thickness;
}

void Engine::Tool::set_active()
{
    is_active = true;
}

void Engine::Tool::unset_activ()
{
    is_active = false;
}

bool Engine::Tool::handle(const Event_t& event) 
{
    if (event.id == Event::RELEASE) {
        using_ = false;
        return true;
    }
    return false;
}

bool Engine::Tool::check_mouse(const Event_t &event)
{
    return false;
}

// ----------------- HAND TOOL ----------------- //

Engine::Hand_tool::Hand_tool() : Tool(COLORS::clear, 0.0, Tool::HAND) {}

void Engine::Hand_tool::use(Canvas &canvas, const Event_t &event)
{
    // ws("USING HAND");
    if (event.id == Event::CLICK) {
        ws("Hand click");
        fix_point = Point(event.x, event.y);
        using_ = true;
        Event::hover_disable = true;
        return;
    }

    if (using_ && event.id == Event::MOUSE_MOVE) {
        if (canvas.move(Point(event.x, event.y) - fix_point)) {
            fix_point = Point(event.x, event.y);
        }
        return;
    }

    if (using_ && event.id == Event::RELEASE) {
        ws("UN_Hand");
        using_ = false;
        Event::hover_disable = false;
        return;
    }

}

// ----------------- ZOOM_UP TOOL ----------------- //

Engine::Zoom_up_tool::Zoom_up_tool() : Tool(COLORS::clear, 0.0, Tool::ZOOM_UP) {}

void Engine::Zoom_up_tool::use(Canvas &canvas, const Event_t &event)
{
    if (event.id == Event::CLICK) {
        canvas.zoom_up(Point(event.x, event.y));
        return;
    }

}

// ----------------- ZOOM_DOWN TOOL ----------------- //

Engine::Zoom_down_tool::Zoom_down_tool() : Tool(COLORS::clear, 0, Tool::ZOOM_DOWN) {}

void Engine::Zoom_down_tool::use(Canvas &canvas, const Event_t &event)
{
    if (event.id == Event::CLICK) {
        canvas.zoom_down(Point(event.x, event.y));
        return;
    }

}

// ----------------- BRUSH TOOL ----------------- //

Engine::Brush_tool::Brush_tool() : Tool(COLORS::black, 10, Tool::BRUSH) {}

void Engine::Brush_tool::use(Canvas &canvas, const Event_t &event)
{
    if (event.id == Event::CLICK) {
        fix_point = Point(event.x, event.y);
        canvas.draw_line(fix_point, fix_point, color_, thickness_);
        using_ = true;
        Event::hover_disable = true;
        return;
    }

    if (using_ && event.id == Event::MOUSE_MOVE) {
        canvas.draw_line(fix_point, Point(event.x, event.y), color_, thickness_);
        fix_point = Point(event.x, event.y);
        return;
    }

    if (using_ && event.id == Event::RELEASE) {
        using_ = false;
        Event::hover_disable = false;
        return;
    }
}