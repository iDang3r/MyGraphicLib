template <typename Functor>
int Engine::create_button(int window_id, const Point &start, double width, double height, Functor functor, const char* label, const char* img_source, const Color &color) 
{
    Window* window = dynamic_cast<Window*>(all_objects[window_id]);
    if (window == nullptr) {
        return -1;
    }

    Coordinates_convertion conv = convert_coordinates(start, width, height, window);
    Button<Functor>* new_button = new Button(conv.start, conv.width, conv.height, color, functor, label, img_source);
    
    window->sub_objects.push_back(new_button);

    return new_button->id_;
}

template <typename Functor>
int Engine::create_round_button(int window_id, const Point &start, double radius_x, Functor functor, const Color &color) 
{
    Window* window = dynamic_cast<Window*>(all_objects[window_id]);
    if (window == nullptr) {
        std::cout << "create_round_button: ";
        ww(window_id);
        return -1;
    }

    Coordinates_convertion conv = convert_coordinates(start, radius_x, radius_x * window_w_to_h, window);
    Button_round<Functor>* new_button = new Button_round(conv.start, conv.width, color, functor);
    
    window->sub_objects.push_back(new_button);

    return new_button->id_;
}

template <typename Functor>
int Engine::create_slider(int window_id, const Point &start, double width, double height, int min_value, int max_value, Functor functor) 
{
    Window* window = dynamic_cast<Window*>(all_objects[window_id]);
    if (window == nullptr) {
        return -1;
    }

    Coordinates_convertion conv = convert_coordinates(start, width, height, window);
    Slider<Functor>* new_slider = new Slider(conv.start, conv.width, conv.height, min_value, max_value, functor);
    
    window->sub_objects.push_back(new_slider);

    return new_slider->id_;
}

#include "Button_templ.hpp"
#include "Button_round_templ.hpp"
#include "Tool_manager_tmpl.hpp"