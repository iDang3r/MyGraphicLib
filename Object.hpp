#pragma once

class Object
{
private:
public:

    int id_;
    std::vector<Object*> sub_objects;

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

    virtual bool check_mouse(const Event_t &event) = 0;

    virtual void close()
    {
        for (auto child : sub_objects) {
            child->close();

            // TODO
            // Have to delete from subscribes !!!
            // delete child;
        }
        all_objects[id_] = NULL;
    }

};