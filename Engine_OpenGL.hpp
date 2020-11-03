#pragma once

#include <GLFW/glfw3.h>
#include <GL/freeglut.h>
#include "help_classes.hpp"
#include "OpenGL_helpful_functions.hpp"

#include "Engine_protocol.hpp"

class Engine_OpenGL : public Engine_protocol
{
private:

    static GLFWwindow* main_window_;
    
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) 
    {
        std::cout << "Key pressed: " << key << ", with scancode:  " << scancode << std::endl;
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(main_window_, GL_TRUE);
        }

        if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
            std::cout << "Q rescan\n";
        }

        if (key == GLFW_KEY_B && action == GLFW_PRESS) {
            std::cout << "B rescan\n";
        }

    }   

    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
    {
        if (xpos < 0 || ypos < 0 || xpos > window_width || ypos > window_height) {
            return;
        }
        // std::cout << "Cursor position by x: " << xpos << ", by y: " << ypos << std::endl;

        Point point(xpos / window_width, 1 - ypos / window_height);
        Event_t new_event(Event::HOVERED, point.x, point.y);

        Event::push(new_event);
    }

    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        // std::cout << "Mouse pressed button: " << button << ", with action:  " << action << std::endl;
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            std::cout << "Left mouse click!\n";

            double xpos = 0, ypos = 0;
            glfwGetCursorPos(main_window_, &xpos, &ypos);

            if (xpos < 0 || ypos < 0 || xpos > window_width || ypos > window_height) {
                return;
            }

            Point point(xpos / window_width, 1 - ypos / window_height);

            Event_t new_event(Event::RESERVED, point.x, point.y);

            switch (action)
            {
            case GLFW_RELEASE:
                new_event.id = Event::RELEASE;
                break;
            case GLFW_PRESS:
                new_event.id = Event::CLICK;
                break;
            case GLFW_REPEAT:
                new_event.id = Event::DOUBLE_CLICK;
                break;
            }
            Event::push(new_event);
        }

    }

    static void window_size_callback(GLFWwindow* window, int width, int height)
    {
        window_width    = width;
        window_height   = height;
        window_w_to_h   = (double)window_width / window_height;
        angle_circle_y  = angle_circle_x * window_w_to_h;
    }

public:

    static int init();
    static int terminate();

    static int is_run();

    static void draw_rectangle(Point start, double width, double height, const Color &color = Color(1.0, 1.0, 1.0))
    {
        start.OpenGL_fit();
        width *= 2;
        height *= 2;

        color.set();

        glBegin(GL_QUADS);
            
        glVertex2f(start.x,         start.y);
        glVertex2f(start.x + width, start.y);
        glVertex2f(start.x + width, start.y + height);
        glVertex2f(start.x,         start.y + height);
        
        glEnd();
    }

    static void draw_square(Point start, double width, const Color &color = Color(1.0, 1.0, 1.0)) 
    {
        start.OpenGL_fit();
        width *= 2;

        double height = width * window_w_to_h;

        draw_rectangle(start, width, height, color);
    }

    static void draw_circle(Point start, double radius, const Color &color = Color(1.0, 1.0, 1.0)) 
    {
        const int degree = 50;

        start.OpenGL_fit();
        radius *= 2;

        color.set();

        glBegin(GL_TRIANGLE_FAN); //BEGIN CIRCLE
        glVertex2f(start.x, start.y); // center of circle

        double coef     = 2 * Pi / degree;
        double radius_h = radius * window_w_to_h;
        for (int i = 0; i <= degree; i++) {
            glVertex2f(
            (start.x + (radius   * std::cos(i * coef))), 
            (start.y + (radius_h * std::sin(i * coef))));
        }
        glEnd(); //END
    }

    static void draw_text(const Point &start_, double width, double height, const char* str, int length)
    {
        if (str == NULL) {
            return;
        }

        // SPACE: 14.0  RETINA: 9.0
        double str_height = 9.0 / window_height;           
        // SPACE: 9.0   RETINA: 6.0
        double str_width  = length * 5.6 / window_width;    

        drawText(str, length, start_.x + width / 2 - str_width / 2, start_.y + height / 2 - str_height / 2);
    }

    static void before_rendering()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the buffers
        glClearColor(H(0xFF), H(0xD0), H(0x7B), 0.3);
    }

    static void after_rendering()
    {
        glFlush();
        glfwSwapBuffers(main_window_);
    }

    static void wait_events()
    {
        glfwWaitEvents();
    }

};

GLFWwindow* Engine_OpenGL::main_window_ = NULL;

int Engine_OpenGL::init() 
{
    if (!glfwInit()) {
        return -1;
    }

    main_window_ = glfwCreateWindow(window_width, window_height, "by DED_32", NULL, NULL);
    if (!main_window_) {
       glfwTerminate();
       return -1;
    }

    glfwMakeContextCurrent(main_window_);

    glfwSetKeyCallback          (main_window_, key_callback);
    glfwSetCursorPosCallback    (main_window_, cursor_position_callback);
    glfwSetMouseButtonCallback  (main_window_, mouse_button_callback);
    glfwSetWindowSizeCallback   (main_window_, window_size_callback);

    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version  = glGetString(GL_VERSION);  // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    // glEnable(GL_DEPTH_TEST);
    // glEnable(GL_POINT_SMOOTH);
    // glDepthFunc(GL_LESS);

    glTranslatef(-1.0, -1.0, 0);

    return 0;
}

int Engine_OpenGL::terminate() {
    glfwTerminate();
    return 0;
}

int Engine_OpenGL::is_run() {
    return !glfwWindowShouldClose(main_window_);
}