#pragma once

class Object
{
private:
public:

    std::set<Object*> sub_objects;

    virtual void draw() {}

    virtual bool handle(const Event_t& event)
    {
        return false;
    }

};