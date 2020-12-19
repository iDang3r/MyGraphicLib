#pragma once 

#include <vector>
#include <string>

#include "Tool.hpp"
#include "Plugin.hpp"

#include "Window.hpp"
#include "Canvas.hpp"

#include "File_manager.hpp"

class Set_tool;
class Open_image;
class Save_image;

class Tool_manager : public Window
{
private:
public:
    int active_tool = 0;
    std::vector<std::pair<Tool*, int>> tools;
    Color& during_color;
    int& thickness;

    Tool_manager(const Point &start, double width, double height, Color& during_color, int& thickness, Canvas& canvas);

    void use_tool(Canvas &canvas, const Event_t &event);

    void set_active_tool(int new_active_tool);

    void add_tool(const Point &point, double width, Tool* tool, const char* source);

    template <typename Functor>
    void add_bttn(const Point &point, double width, const Functor &functor, const char* source);

    void add_plug(const Point &point, double width, const std::string &plug_name);

};

class Set_tool
{
public:
    Tool_manager*   tool_manager;
    int             tool;

    Set_tool(Tool_manager* tool_manager, int tool);

    void operator()(Engine::Button<Set_tool>* button);
};

class Directory_view;
class Open_image_functor;

class Open_image
{
public:
    Canvas&         canvas;
    int             sys_window_id   = 0;
    Directory_view* dir_view        = nullptr;

    Open_image(Canvas& canvas);

    void operator()(Engine::Button<Open_image>* button);

};

class Input_box;

class Save_image
{
public:
    Canvas&         canvas;
    int             sys_window_id   = 0;
    Directory_view* dir_view        = nullptr;
    Input_box*      input_box       = nullptr;
    std::string     input_str       = "Test";

    Save_image(Canvas& canvas);

    void operator()(Engine::Button<Save_image>* button);

};

class Save_image_functor
{
public:
    Canvas&       canvas;
    File_manager* file_manager;
    std::string&  file_name;
    int           sys_window_id;

    Directory_view* dir_view;
    Input_box*      input_box;

    Save_image_functor(Canvas& canvas, File_manager* file_manager, std::string& file_name, int sys_window_id, Directory_view* dir_view, Input_box* input_box);

    void operator()(Engine::Button<Save_image_functor>* button);
};

class Open_image_functor
{
public:
    Canvas&       canvas;
    File_manager* file_manager;
    int&          file_id;
    int           sys_window_id;

    Directory_view* dir_view;

    Open_image_functor(Canvas& canvas, File_manager* file_manager, int& file_id, int sys_window_id, Directory_view* dir_view);

    void operator()(Engine::Button<Open_image_functor>* button);
};

class Directory_view : public Object
{
public:

    int             label_id = 0;
    int             curr_dir_id = 0;
    File_manager*   file_manager = nullptr;
    int             during_subdir_num = 0;

    Directory_view(int id, const Point &start, double width, double height, File_manager* file_manager, int curr_dir_id);

    void update_directory();

    bool handle(const Event_t& event);

    bool check_mouse(const Event_t &event);

    ~Directory_view();

};

class Input_box : public Object
{
public:

    int             label_id = 0;
    std::string&    str;

    Input_box(int id, const Point &start, double width, double height, std::string& str);

    ~Input_box();

    void update_label();

    bool handle(const Event_t& event);

    bool check_mouse(const Event_t &event);

};