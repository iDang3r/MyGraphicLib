// #pragma once
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <vector>

#include "Event.hpp"

class Object
{
private:
public:

    int id_;
    std::vector<Object*> sub_objects;

    Object();
    ~Object();

    virtual void draw();

    virtual bool handle(const Event_t& event);

    virtual bool check_mouse(const Event_t &event) = 0;

    virtual void close();

};

#endif // OBJECT_HPP