#pragma once

#include <queue>

class Event_t
{
private:
public:
    int     id;
    double  x;
    double  y;

    Event_t(int id) : id(id) {}
    Event_t(int id, double x, double y) : id(id), x(x), y(y) {}

};

class Event
{
private:
public:

    enum EVENT 
    {
        RESERVED,
        HOVERED,
        UNHOVERED,
        CLICK,
        RELEASE,
        DOUBLE_CLICK,
        MOUSE_MOVE,

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