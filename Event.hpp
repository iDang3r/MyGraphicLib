#pragma once

#include <queue>

class Event_t
{
private:
public:
    int     id;
    double  x;
    double  y;

    char    letter;

    Event_t(int id) : id(id) {}
    Event_t(int id, double x, double y) : id(id), x(x), y(y) {}
    Event_t(int id, char letter) : id(id), letter(letter) {}

};

class Event
{
private:
public:

    enum EVENT_ID 
    {
        RESERVED,
        HOVERED,
        UNHOVERED,
        CLICK,
        RELEASE,
        DOUBLE_CLICK,
        MOUSE_MOVE,

        BUTTON_UP,
        BUTTON_DOWN,
        BUTTON_LEFT,
        BUTTON_RIGHT,

        BUTTON_ENTER,
        BUTTON_ESCAPE,
        BUTTON_BACKSPACE,

        BUTTON_LETTER,

        // don't touch
        num_event_types
    };

    static bool hover_disable;
    static std::queue<Event_t> queue;

    static bool empty()
    {
        return queue.empty();
    }

    static Event_t get() 
    {
        Event_t ret = queue.front();
        queue.pop();
        if (hover_disable && (ret.id == HOVERED || ret.id == UNHOVERED)) {
            ret.id = RESERVED;
        }
        return ret;
    }

    static void push(const Event_t &event) 
    {
        queue.push(event);
    }

};
std::queue<Event_t> Event::queue;
bool Event::hover_disable = false;