#pragma once

class Object
{
private:
public:

    int id_;
    std::set<Object*> sub_objects;

    Object() : id_(Engine::valid_id_++)
    {
        Engine::all_objects[id_] = this;
        std::cout << "Object_id: " << id_ << std::endl;
    }

    virtual void draw() {}

    virtual bool handle(const Event_t& event)
    {
        return false;
    }

};