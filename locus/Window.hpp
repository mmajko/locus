//
//  Window.hpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Scene.hpp"

class Window {
public:
    Window(int width, int height);
    GLFWwindow* getWindow();
    void attachScene(Scene* scene);
    void activate();
    void draw();
    bool hasBeenClosed();
private:
    int width;
    int height;
    GLFWwindow* window;
    Scene* scene;
};

#endif /* Window_hpp */
