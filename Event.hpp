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
        HOVER,
        CLICK,
    };

    static std::queue<Event_t> queue;

    static bool empty()
    {
        return queue.empty();
    }

    static Event_t get() 
    {
        Event_t ret = queue.front();
        queue.pop();
        return ret;
    }

    static void push(const Event_t &event) 
    {
        queue.push(event);
    }

};
std::queue<Event_t> Event::queue;