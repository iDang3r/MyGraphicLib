#include "Engine.hpp"

Engine::Thickness::Thickness(const Point &start, double width, double height)
    :  Window(start, width, height, COLORS::tool_manager)
{
    label_id = Engine::create_label(id_, Point(0.0, 0.4), 1.0, 0.6, "Thickness");
    update(0.5);

    slider_id = Engine::create_slider(id_, Point(0.0, 0.0), 1.0, 0.5, min_thickness, max_thickness, Thickness_functor(this));

}

Engine::Thickness::~Thickness() {}

void Engine::Thickness::update(double x) // x \in [0, 1]
{
    thickness = (max_thickness - min_thickness) * x + min_thickness;
    Engine::set_label_text(label_id, ("Thickness: " + std::to_string(thickness)).c_str());
}

Engine::Thickness_functor::Thickness_functor(Thickness* thickness) : thickness(thickness) {}

void Engine::Thickness_functor::operator()(double got_from_Slider)
{
    thickness->update(got_from_Slider);
}