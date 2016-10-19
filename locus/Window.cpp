//
//  Window.cpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "Window.hpp"

Window::Window(int width, int height) : width(width), height(height) {
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
    if (!window) {
        glfwTerminate();
    }
    
    glfwSwapInterval(1);
}

GLFWwindow* Window::getWindow() {
    return window;
}

void Window::attachScene(Scene *scene) {
    this->scene = scene;
}

void Window::activate() {
    glfwMakeContextCurrent(window);
    
    
    glClearColor(0.2f, 0.75f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void Window::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for (Object* obj : scene->getChildren()) {
        obj->draw();
    }
    
    glfwSwapBuffers(window);
}

bool Window::hasBeenClosed() {
    return glfwWindowShouldClose(window);
}
