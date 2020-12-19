#include "Event.hpp"

Event_t::Event_t(int id) : id(id) {}
Event_t::Event_t(int id, double x, double y) : id(id), x(x), y(y) {}
Event_t::Event_t(int id, char letter) : id(id), letter(letter) {}


bool Event::empty()
{
    return queue.empty();
}

Event_t Event::get() 
{
    Event_t ret = queue.front();
    queue.pop();
    if (hover_disable && (ret.id == HOVERED || ret.id == UNHOVERED)) {
        ret.id = RESERVED;
    }
    return ret;
}

void Event::push(const Event_t &event) 
{
    queue.push(event);
}

std::queue<Event_t> Event::queue;
bool Event::hover_disable = false;