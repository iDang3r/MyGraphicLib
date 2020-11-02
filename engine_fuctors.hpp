#pragma once

class Close_system_window
{
public:
    void operator()(Engine::Button<Close_system_window>* button)
    {
        std::cout << "Close system window" << std::endl;
    }
};