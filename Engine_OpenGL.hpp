#pragma once

#include "Engine_protocol.hpp"

#include <GLFW/glfw3.h>
#include <GL/freeglut.h>
#include "helpful_functions.hpp"
#include "OpenGL_help_classes.hpp"

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
        std::cout << "Cursor position by x: " << xpos << ", by y: " << ypos << std::endl;

        Point point(2 * xpos / window_width, 2 - 2 * ypos / window_height);
        std::cout << point << std::endl;
    }

    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        std::cout << "Mouse pressed button: " << button << ", with action:  " << action << std::endl;
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
            std::cout << "Left mouse click!\n";

            double xpos = 0, ypos = 0;
            glfwGetCursorPos(main_window_, &xpos, &ypos);

            if (xpos < 0 || ypos < 0 || xpos > window_width || ypos > window_height) {
                return;
            }

            Point point(2 * xpos / window_width, 2 - 2 * ypos / window_height);
            Event::push(Event_t(Event::CLICK, point.x, point.y)); 
        }
    }

public:

    static int init();
    static int terminate();

    static int is_run();

    static void draw_rectangle(const Point& start, double width, double height, const Color &color = Color(1.0, 1.0, 1.0))
    {
        color.set();

        glBegin(GL_QUADS);
            
        glVertex2f(start.x,         start.y);
        glVertex2f(start.x + width, start.y);
        glVertex2f(start.x + width, start.y + height);
        glVertex2f(start.x,         start.y + height);
        
        glEnd();
    }

    static void draw_square(const Point& start, double width, const Color &color = Color(1.0, 1.0, 1.0)) 
    {
        double height = width * window_w_to_h;

        draw_rectangle(start, width, height, color);
    }

    static void draw_circle(const Point& start, double radius, const Color &color = Color(1.0, 1.0, 1.0)) {
        const int degree = 50;

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

    glfwSetKeyCallback(main_window_, key_callback);
    glfwSetCursorPosCallback(main_window_, cursor_position_callback);
    glfwSetMouseButtonCallback(main_window_, mouse_button_callback);

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