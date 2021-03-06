//
//  Camera.cpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "Camera.hpp"

#include "iostream"

#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(string name, vec3 position, vec3 rotation) : Object(name, position, rotation, vec3(1.0f)) {
    this->isDrawable = false;
}

mat4 Camera::getViewMatrix() {
    return toMat4(rotation) * translate(-position);
}

mat4 Camera::getProjectionMatrix() {
    // TODO: Make this parametric
    return perspective( radians(90.0f), 16.0f / 9.0f, 0.01f, 100.0f);
}

void Camera::holdBoundaries(vec3 center, vec3 size) {
    if (position.x > center.x + size.x/2.0f) {
        position.x -= (position.x - (center.x + size.x/2.0f)) / 2.0f;
    }
    if (position.x < center.x - size.x/2.0f) {
        position.x -= (position.x - (center.x - size.x/2.0f)) / 2.0f;
    }
    if (position.y > center.y + size.y/2.0f) {
        position.y -= (position.y - (center.y + size.y/2.0f)) / 2.0f;
    }
    if (position.y < center.y - size.y/2.0f) {
        position.y -= (position.y - (center.y - size.y/2.0f)) / 2.0f;
    }
    if (position.z > center.z + size.z/2.0f) {
        position.z -= (position.z - (center.z + size.z/2.0f)) / 2.0f;
    }
    if (position.z < center.z - size.z/2.0f) {
        position.z -= (position.z - (center.z - size.z/2.0f)) / 2.0f;
    }
}

void Camera::avoidBoundaries(vec3 center, float size) {
    float dist = distance(position, center);
    
    if (dist < size) {
        vec3 relative = position - center;
        position += relative * 0.05f;
    }
}
