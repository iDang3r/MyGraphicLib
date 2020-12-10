#pragma once

#include "Window.hpp"

class Palette_functor;

class Palette : public Window
{
public:

    Color color;
    bool is_color_table_active = false;

    Palette(const Point &start, double width, double height)
        : Window(start, width, height, COLORS::tool_manager), color(COLORS::red)
    {
        Engine::create_label(id_, Point(0.0, 0.5), 1.0, 0.5, "Palette");
        int color_window_id = Engine::create_window(id_, Point(0.05, 0.05), 0.90, 0.45, color);
        Engine::create_button(id_, Point(0.05, 0.05), 0.90, 0.45, Palette_functor(color_window_id, this), NULL, NULL, COLORS::clear);
    }
};

class Palette_functor
{
public:
    int window_id;
    Palette* palette;

    Palette_functor(int color_window_id, Palette* palette) : window_id(color_window_id), palette(palette) {}

    void operator()(Engine::Button<Palette_functor>* button)
    {
        ws("SET PALETTE COLOR");
        // Engine::set_window_color(window_id, COLORS::blue);
        // palette->color = COLORS::blue;

        if (palette->is_color_table_active) {

            FILE* in = fopen("DATA.txt", "r");
            fscanf(in, "%lf %lf %lf", &palette->color.r, &palette->color.g, &palette->color.b);
            fclose(in);

            Engine::set_window_color(window_id, palette->color);

        } else {
            ws("START");

            palette->is_color_table_active = true;

            pid_t pid = fork();
            if (pid == 0) {
                execl("test_palette", "test_palette", NULL);

                exit(0);
            }

        }

        // MyCPPClass Q;
        // Q.runPalette();
        
        ws("END");

    }
};