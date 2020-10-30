#pragma once

#include "Window.hpp"

class Button : public Window {
private:
public:

    bool handle(const Event_t &event) {

        switch (event.id)
        {
        case Event::CLICK:
            
            std::cout << "CLICKED!!!!!!!!!!!!!!!!!!" << std::endl;

            break;
        }

    }


};