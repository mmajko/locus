//
//  SpotLight.hpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#ifndef SpotLight_hpp
#define SpotLight_hpp

#include "Object.hpp"

class SpotLight : public Object {
public:
    SpotLight(string name, vec3 position, vec3 rotation, vec3 color, float constant, float linear, float quadratic, float cutOff, float outerCutOff);
    float getConstant();
    float getLinear();
    float getQuadratic();
    float getCutOff();
    float getOuterCutOff();
    void setColor(vec3 color);
    vec3 getColor();
private:
    vec3 color;
    float constant;
    float linear;
    float quadratic;
    float cutOff;
    float outerCutOff;
};

#endif /* SpotLight_hpp */
