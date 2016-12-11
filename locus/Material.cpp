//
//  Material.cpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include <vector>
#include <fstream>
#include <string>
#include <streambuf>
#include <iostream>

#include "Material.hpp"
#include "ResourcePath.hpp"

using namespace std;

Material::Material(Shader* shader, Texture* texture, vec3 ambient, vec3 diffuse, vec3 specular) : shader(shader), texture(texture), ambient(ambient), diffuse(diffuse), specular(specular) {
    hasTexture = true;
}

Material::Material(Shader* shader, vec3 ambient, vec3 diffuse, vec3 specular) : Material(shader, nullptr, ambient, diffuse, specular) {
    hasTexture = false;
}

Material::Material(Shader* shader) : Material(shader, nullptr, vec3(1), vec3(1), vec3(1)) {
    hasTexture = false;
}

Material::Material(Shader* shader, Texture* texture) : Material(shader, texture, vec3(1), vec3(1), vec3(1)) {
    hasTexture = true;
}

Material::~Material() {
    delete shader;
}

Material* Material::fromFile(const string& filename) {
    ifstream file(filename);
    string vertFilename, fragFilename;
    
    file >> vertFilename >> fragFilename;
    Shader* shader = Shader::fromFile(resourcePath() + vertFilename, resourcePath() + fragFilename);
    return new Material(shader, vec3(1, 1, 1), vec3(1, 1, 1), vec3(1, 1, 1));
}

Material* Material::clone() {
    return new Material(shader, texture, ambient, diffuse, specular);
}

void Material::use() {
    shader->use();
    if (hasTexture) texture->bind();
}

Shader* Material::getShader() {
    return shader;
}

Texture* Material::getTexture() {
    return texture;
}

void Material::setTexture(Texture* texture) {
    this->texture = texture;
    hasTexture = true;
}

void Material::unsetTexture() {
    this->texture = nullptr;
    hasTexture = false;
}

void Material::updateMVP(mat4 modelTransform, mat4 viewTransform, mat4 projectionTransform) {
    shader->setUniform("M", modelTransform);
    shader->setUniform("V", viewTransform);
    shader->setUniform("P", projectionTransform);
}

void Material::updateVP(mat4 viewTransform, mat4 projectionTransform) {
    shader->setUniform("V", viewTransform);
    shader->setUniform("P", projectionTransform);
}

void Material::updateM(mat4 modelTransform) {
    shader->setUniform("M", modelTransform);
}
