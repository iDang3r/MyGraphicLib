#include "Engine_OpenGL.hpp"

#include "Event.hpp"
#include "Window.hpp"

using Engine_t = Engine_OpenGL;

class Engine : public Engine_OpenGL
{
private:
    int valid_id_ = 1;

public:

    int create_window();
    int delete_window(int id);

};