//
//  FreeCamera.hpp
//  locus
//
//  Created by Marián Hlaváč on 24/11/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#ifndef FreeCamera_hpp
#define FreeCamera_hpp

#define MOUSE_SENSITIVITY 4.0f
#define MAX_VELOCITY 20.0f
#define FRICTION 0.09f

#include "Camera.hpp"
#include "Window.hpp"
#include <glm/gtc/quaternion.hpp>

class FreeCamera : public Camera {
public:
    FreeCamera(string name, vec3 position, vec3 rotation);
    void update(Window* window, float deltaTime);
private:
    vec2 velocity;
};

#endif /* FreeCamera_hpp */
