
#include "Engine.hpp"

#include <iostream>

Engine::Object::Object() : id_(Engine::valid_id_++)
{
    Engine::all_objects[id_] = this;
    std::cout << "Object_id: " << id_ << std::endl;
}

Engine::Object::~Object() {}

void Engine::Object::draw() {}

bool Engine::Object::handle(const Event_t& event)
{
    return false;
}

void Engine::Object::close()
{
    for (auto child : sub_objects) {
        child->close();

        // TODO
        // Have to delete from subscribes !!!
        // delete child;
    }
    Engine::all_objects[id_] = NULL;
}