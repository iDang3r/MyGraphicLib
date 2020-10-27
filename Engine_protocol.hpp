#pragma once

class Engine_protocol 
{
private:
    int valid_id_ = 1;

public:
    Engine_protocol()                   = default;
    ~Engine_protocol()                  = default;

    virtual int init()                  = 0;
    virtual int create_window()         = 0;

    virtual int is_run()                = 0;


    virtual int delete_window(int id)   = 0;
    virtual int terminate()             = 0;
};