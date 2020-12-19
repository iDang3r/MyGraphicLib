#include "Engine.hpp"

Engine::Tool_manager::Tool_manager(const Point &start, double width, double height, Color& during_color, int& thickness, Canvas& canvas) :
    Window(start, width, height, COLORS::tool_manager), during_color(during_color), thickness(thickness)
{
    File_manager f_manager("Plugins");
    std::vector<std::string> plugin_names;

    for (int i = 2; i < f_manager.get_dir_size(); ++i) {
        if (f_manager.is_subdir_dir(i)) {
            plugin_names.push_back(f_manager.get_subdir_name(i));
            ws(plugin_names.back());
        }
    }

    Engine::create_label(id_, Point(0.0, 0.88), 1.0, 0.1, "Tools");

    double up_size = 0.02 + 0.35 / height_ * width_ * Engine::window_w_to_h;
    add_tool(Point(0.1,  0.02),               0.35, new Zoom_down_tool(), "zoom_down.png");
    add_tool(Point(0.55, 0.02),               0.35, new Zoom_up_tool(),   "zoom_up.png");

    add_tool(Point(0.1,  0.02 + 1 * up_size), 0.35, new Hand_tool(),      "hand.png");
    add_tool(Point(0.55, 0.02 + 1 * up_size), 0.35, new Brush_tool(),     "brush.png");

    add_bttn(Point(0.1,  0.02 + 2 * up_size), 0.35, Open_image(canvas),   "open.png");
    add_bttn(Point(0.55, 0.02 + 2 * up_size), 0.35, Save_image(canvas),   "save.png");

    int num = 6;

    for (int i = 0; i < plugin_names.size(); ++i, ++num) {
        if (num & 1) {
            add_plug(Point(0.1,  0.02 + (num / 2) * up_size), 0.35, plugin_names[i]);
        } else {
            add_plug(Point(0.55, 0.02 + (num / 2) * up_size), 0.35, plugin_names[i]);
        }
    }


    // add_plug(Point(0.1,  0.02 + 3 * up_size), 0.35, "BoxBlur");
    // add_plug(Point(0.55, 0.02 + 3 * up_size), 0.35, "ColorFilter");

    // add_plug(Point(0.1,  0.02 + 4 * up_size), 0.35, "GaussianBlur");

    set_active_tool(0);
}

void Engine::Tool_manager::use_tool(Canvas &canvas, const Event_t &event)
{
    tools[active_tool].first->set_color(during_color);
    tools[active_tool].first->set_thickness(thickness);
    tools[active_tool].first->use(canvas, event);
}

void Engine::Tool_manager::set_active_tool(int new_active_tool)
{
    Engine::set_window_color(tools[active_tool].second, COLORS::clear);
    active_tool = new_active_tool;
    Engine::set_window_color(tools[active_tool].second, COLORS::red);
}

void Engine::Tool_manager::add_tool(const Point &point, double width, Tool* tool, const char* source)
{
    double k = 0.1; // frame size
    double d_x = k * width;
    double d_y = k * width / height_ * width_ * Engine::window_w_to_h;
    int frame_id = Engine::create_window(id_, point - Point(d_x, d_y), width + 2 * d_x, width / height_ * width_ * Engine::window_w_to_h + 2 * d_y, COLORS::clear);
    tools.push_back({tool, frame_id});
    Engine::create_button(id_, point, width, width / height_ * width_ * Engine::window_w_to_h, Set_tool(this, tools.size() - 1), NULL, source, COLORS::tool);
}

void Engine::Tool_manager::add_plug(const Point &point, double width, const std::string &plug_name)
{
    double k = 0.1; // frame size
    double d_x = k * width;
    double d_y = k * width / height_ * width_ * Engine::window_w_to_h;
    int frame_id = Engine::create_window(id_, point - Point(d_x, d_y), width + 2 * d_x, width / height_ * width_ * Engine::window_w_to_h + 2 * d_y, COLORS::clear);
    tools.push_back({new Plugin(plug_name), frame_id});
    Engine::create_button(id_, point, width, width / height_ * width_ * Engine::window_w_to_h, Set_tool(this, tools.size() - 1), NULL, ("Plugins/" + plug_name + "/icon.png").c_str(), COLORS::tool);
}

// ----------------------- CLASS SET_TOOL ----------------------- //

Engine::Set_tool::Set_tool(Tool_manager* tool_manager, int tool) : tool_manager(tool_manager), tool(tool) {}

void Engine::Set_tool::operator()(Engine::Button<Set_tool>* button)
{
    tool_manager->set_active_tool(tool);
}

// ----------------------- CLASS OPEN_IMAGE ----------------------- //

Engine::Open_image::Open_image(Canvas& canvas) : canvas(canvas) {}

void Engine::Open_image::operator()(Engine::Button<Open_image>* button)
{
    if (Engine::is_window_exists(sys_window_id)) {
        return;
    }
    sys_window_id = Engine::create_system_window(Point(0.03, 0.65), 0.25, 0.2);

    File_manager* file_manager = new File_manager("./Images");

    int curr_dir_id = Engine::create_label(sys_window_id, Point(0.03, 0.7), 0.93, 0.2, (file_manager->get_current_dir()).c_str(), COLORS::white);
    Engine::set_label_lefty(curr_dir_id);

    dir_view = new Directory_view(sys_window_id, Point(0.03, 0.45), 0.93, 0.2, file_manager, curr_dir_id);

    Engine::create_button(sys_window_id, Point(0.35, 0.1), 0.3, 0.3, Open_image_functor(canvas, file_manager, dir_view->during_subdir_num, sys_window_id, dir_view), "OPEN", NULL, COLORS::tool);
}

// ----------------------- CLASS SAVE_IMAGE ----------------------- //

Engine::Save_image::Save_image(Canvas& canvas) : canvas(canvas) {}

void Engine::Save_image::operator()(Engine::Button<Save_image>* button)
{
    if (Engine::is_window_exists(sys_window_id)) {
        return;
    }
    sys_window_id = Engine::create_system_window(Point(0.03, 0.36), 0.25, 0.25);

    File_manager* file_manager = new File_manager("./Images");

    int curr_dir_id = Engine::create_label(sys_window_id, Point(0.03, 0.76), 0.93, 0.16, (file_manager->get_current_dir()).c_str(), COLORS::white);
    Engine::set_label_lefty(curr_dir_id);

    dir_view  = new Directory_view(sys_window_id, Point(0.03, 0.56), 0.93, 0.16, file_manager, curr_dir_id);
    input_box = new Input_box     (sys_window_id, Point(0.03, 0.36), 0.93, 0.16, input_str);

    Engine::create_button(sys_window_id, Point(0.35, 0.08), 0.3, 0.24, Save_image_functor(canvas, file_manager, input_str, sys_window_id, dir_view, input_box), "SAVE", NULL, COLORS::tool);
}

// ----------------------- CLASS SAVE_IMAGE_FUNCTOR ----------------------- //

Engine::Save_image_functor::Save_image_functor(Canvas& canvas, File_manager* file_manager, std::string& file_name, int sys_window_id, Directory_view* dir_view, Input_box* input_box) 
    : canvas(canvas), file_manager(file_manager), file_name(file_name), sys_window_id(sys_window_id), dir_view(dir_view), input_box(input_box)
{}

void Engine::Save_image_functor::operator()(Engine::Button<Save_image_functor>* button)
{
    if (canvas.save_to_image((file_manager->get_current_dir() + "/" + file_name).c_str())) {
        delete dir_view;
        delete input_box;
        Engine::delete_window(sys_window_id);
    }
}

// ----------------------- CLASS OPEN_IMAGE_FUNCTOR ----------------------- //

Engine::Open_image_functor::Open_image_functor(Canvas& canvas, File_manager* file_manager, int& file_id, int sys_window_id, Directory_view* dir_view) 
    : canvas(canvas), file_manager(file_manager), file_id(file_id), sys_window_id(sys_window_id), dir_view(dir_view)
{}

void Engine::Open_image_functor::operator()(Engine::Button<Open_image_functor>* button)
{
    if (!file_manager->is_subdir_file(file_id)) {
        dump(DUMP_INFO, "can open file only");
        return;
    }

    if (canvas.load_from_image((file_manager->get_current_dir() + "/" + file_manager->get_subdir_name(file_id)).c_str())) {
        delete dir_view;
        Engine::delete_window(sys_window_id);
    }
}

// ----------------------- CLASS DIRECTORY_VIEW ----------------------- //

Engine::Directory_view::Directory_view(int id, const Point &start, double width, double height, File_manager* file_manager, int curr_dir_id)
    : file_manager(file_manager), curr_dir_id(curr_dir_id)
{
    label_id = Engine::create_label(id, start, width, height, file_manager->get_subdir_name(during_subdir_num).c_str(), COLORS::white);
    Engine::set_label_lefty(label_id);

    update_directory();

    Engine::subscribes[Event::BUTTON_UP].insert(this);
    Engine::subscribes[Event::BUTTON_DOWN].insert(this);
    Engine::subscribes[Event::BUTTON_ENTER].insert(this);
}

void Engine::Directory_view::update_directory()
{
    std::string str = "can't detect type of directory: ";
    if (file_manager->is_subdir_dir(during_subdir_num)) {
        str = "directory: ";
    } else if (file_manager->is_subdir_file(during_subdir_num)) {
        str = "file: ";
    }

    str += file_manager->get_subdir_name(during_subdir_num);
    Engine::set_label_text(label_id, str.c_str());
    Engine::set_window_color(label_id, COLORS::white);

    Engine::set_label_text(curr_dir_id, file_manager->get_current_dir().c_str());
}

bool Engine::Directory_view::handle(const Event_t& event)
{
    switch (event.id)
    {
    case Event::BUTTON_UP: {

        ws("Directory_view --> BUTTON_UP");

        during_subdir_num = std::max(during_subdir_num - 1, 0);

        update_directory();

        break;
    }

    case Event::BUTTON_DOWN: {

        ws("Directory_view --> BUTTON_DOWN");

        during_subdir_num = std::min(during_subdir_num + 1, file_manager->get_dir_size() - 1);

        update_directory();

        break;
    }
        
    case Event::BUTTON_ENTER: {

        ws("Directory_view --> BUTTON_ENTER");

        if (!file_manager->is_subdir_dir(during_subdir_num)) {
            Engine::set_window_color(label_id, COLORS::red);
            break;
        }

        file_manager->go_to_subdir(during_subdir_num);

        during_subdir_num = 0;
        update_directory();

        break;
    }

    }

    return true;
}

bool Engine::Directory_view::check_mouse(const Event_t &event)
{
    return false;
}

Engine::Directory_view::~Directory_view()
{
    dump(DUMP_INFO, "Directory_view destructing");
    Engine::subscribes[Event::BUTTON_UP].erase(this);
    Engine::subscribes[Event::BUTTON_DOWN].erase(this);
    Engine::subscribes[Event::BUTTON_ENTER].erase(this);
}

// ----------------------- CLASS INPUT_BOX ----------------------- //

Engine::Input_box::Input_box(int id, const Point &start, double width, double height, std::string& str)
    : str(str)
{
    label_id = Engine::create_label(id, start, width, height, str.c_str(), COLORS::white);
    Engine::set_label_lefty(label_id);

    update_label();

    // Engine::subscribes[Event::BUTTON_ENTER].insert(this);
    Engine::subscribes[Event::BUTTON_BACKSPACE].insert(this);
    Engine::subscribes[Event::BUTTON_LETTER].insert(this);

}

Engine::Input_box::~Input_box()
{
    // Engine::subscribes[Event::BUTTON_ENTER].erase(this);
    Engine::subscribes[Event::BUTTON_BACKSPACE].erase(this);
    Engine::subscribes[Event::BUTTON_LETTER].erase(this);
}

void Engine::Input_box::update_label()
{
    Engine::set_label_text(label_id, ("File name: " + str).c_str());
}

bool Engine::Input_box::handle(const Event_t& event)
{
    switch (event.id)
    {
        
    case Event::BUTTON_BACKSPACE: {

        if (!str.empty()) {
            str.pop_back();
            update_label();
        }

        break;
    }

    case Event::BUTTON_LETTER: {

        str.push_back(event.letter);
        update_label();

        break;
    }

    }

    return true;
}

bool Engine::Input_box::check_mouse(const Event_t &event)
{
    return false;
}