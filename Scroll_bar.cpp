#include "Engine.hpp"

Engine::Scroll_bar::Scroll_bar(const Point &start, double width, double height) : 
    Window(start, width, height, COLORS::clear)
{
    is_vertical = (width < height);

    Engine::create_button(id_, Point(0.0, 0.0), 1.0, 1.0, Scroll_background(), NULL, NULL, COLORS::scroll_back);

    if (is_vertical) {

        int down_id = Engine::create_button(id_, Point(0.0, 0.0),               1.0, arrows_size, Scroll_down(), NULL, NULL, COLORS::scroll_slider);
        int up_id   = Engine::create_button(id_, Point(0.0, 1.0 - arrows_size), 1.0, arrows_size, Scroll_up(),   NULL, NULL, COLORS::scroll_slider);
        Window* arrow_up   = dynamic_cast<Window*>(all_objects[up_id]);
        Window* arrow_down = dynamic_cast<Window*>(all_objects[down_id]);

        int slider_id = Engine::create_button(id_, Point(0.0, 0.4), 1.0, 2 * arrows_size, Scroll_slider(), NULL, NULL, COLORS::scroll_slider);
        Window* slider = dynamic_cast<Window*>(all_objects[slider_id]);

        slider->set_dragable(Dragable::VERTICAL, arrow_down->start_.y + arrow_down->height_, arrow_up->start_.y);

    } else {

        int down_id = Engine::create_button(id_, Point(0.0, 0.0),               arrows_size, 1.0, Scroll_down(), NULL, NULL, COLORS::scroll_slider);
        int up_id   = Engine::create_button(id_, Point(1.0 - arrows_size, 0.0), arrows_size, 1.0, Scroll_up(),   NULL, NULL, COLORS::scroll_slider);
        Window* arrow_up   = dynamic_cast<Window*>(all_objects[up_id]);
        Window* arrow_down = dynamic_cast<Window*>(all_objects[down_id]);

        int slider_id = Engine::create_button(id_, Point(0.0, 0.4), 1.0, 2 * arrows_size, Scroll_slider(), NULL, NULL, COLORS::scroll_slider);
        Window* slider = dynamic_cast<Window*>(all_objects[slider_id]);

        /* TODO */ exit(1);

    }

    
    
}