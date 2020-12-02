#pragma once

class Close_system_window
{
private:
    int id;
public:
    Close_system_window(int id) : id(id) {}

    void operator()(Engine::Button<Close_system_window>* button)
    {
        std::cout << "Close system window with id: " << id << std::endl;
        Engine::delete_window(id);
    }
};

class Scroll_background
{
public:

    Scroll_background() {}

    void operator()(Engine::Button<Scroll_background>* button)
    {
        ws("Scroll_bar: background");
    }

};

class Scroll_down
{
public:

    Scroll_down() {}

    void operator()(Engine::Button<Scroll_down>* button)
    {
        ws("Scroll_bar: down arrow");
    }

};

class Scroll_up
{
public:

    Scroll_up() {}

    void operator()(Engine::Button<Scroll_up>* button)
    {
        ws("Scroll_bar: up arrow");
    }

};

class Scroll_slider
{
public:

    Scroll_slider() {}

    void operator()(Engine::Button<Scroll_slider>* button)
    {
        ws("Scroll_bar: slider");
    }

};