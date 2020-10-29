#pragma once

class Engine_protocol 
{
private:
public:
    static constexpr int        window_width    = 1920;
    static constexpr int        window_height   = 1080;
    static constexpr double     window_w_to_h   = (double)window_width / window_height;

    static constexpr double     Pi              = M_PI;
    static constexpr double     angle_circle_r  = 0.03;

    Engine_protocol()   = default;
    ~Engine_protocol()  = default;

    static int init()       {}
    static int terminate()  {}

    static int is_run()     {}
    
};