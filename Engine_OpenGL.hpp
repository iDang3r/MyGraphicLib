#pragma once

#include "Engine.hpp"

#include <GLFW/glfw3.h>
#include <GL/freeglut.h>
#include "helpful_functions.hpp"

class Engine_OpenGL : Engine_protocol
{
private:

    GLFWwindow* main_window_ = NULL;
    
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    std::cout << "Key pressed: " << key << ", with scancode:  " << scancode << std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
        std::cout << "Q rescan\n";
    }

	if (key == GLFW_KEY_B && action == GLFW_PRESS) {
        std::cout << "B rescan\n";
    }

}

public:

    Engine_OpenGL()  = default;
    ~Engine_OpenGL() = default;

    int init();
    int create_window();

    int is_run();

    int delete_window(int id);
    int terminate();
};

int Engine_OpenGL::init() 
{
    if (!glfwInit()) {
        return -1;
    }

    main_window_ = glfwCreateWindow(1920, 1080, "by DED_32", NULL, NULL);
    if (!main_window_) {
       glfwTerminate();
       return -1;
    }

    glfwMakeContextCurrent(main_window_);
    glfwSetKeyCallback(main_window_, key_callback);

    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version  = glGetString(GL_VERSION);  // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_POINT_SMOOTH);
    glDepthFunc(GL_LESS);

    return 0;
}

int Engine_OpenGL::terminate() {
    glfwTerminate();
    return 0;
}

int Engine_OpenGL::create_window() {

}

int Engine_OpenGL::delete_window(int id) {

}

int Engine_OpenGL::is_run() {
    return !glfwWindowShouldClose(main_window_);
}