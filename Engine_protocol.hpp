#pragma once

class Engine_protocol 
{
private:
public:
    static constexpr int        window_width    = 1920;
    static constexpr int        window_height   = 1080;
    static constexpr double     window_w_to_h   = (double)window_width / window_height;

    static constexpr double     Pi              = M_PI;

    Engine_protocol()                   = default;
    ~Engine_protocol()                  = default;

    virtual int init()                  = 0;
    virtual int terminate()             = 0;

    virtual int is_run()                = 0;
    
};