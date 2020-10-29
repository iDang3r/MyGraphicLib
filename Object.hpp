#pragma once

class Object
{
private:
public:

    std::unordered_set<Object*> sub_objects;

    virtual void draw()     = 0;

    virtual bool handle()   = 0;

};