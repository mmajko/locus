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
    hasSpecularMap = false;
    textureType = TEXTURE_BASE;
}

Material::Material(Shader* shader, vec3 ambient, vec3 diffuse, vec3 specular) : Material(shader, nullptr, ambient, diffuse, specular) {
    hasTexture = false;
    hasSpecularMap = false;
    textureType = TEXTURE_BASE;
}

Material::Material(Shader* shader) : Material(shader, nullptr, vec3(0.1f), vec3(1), vec3(1)) {
    hasTexture = false;
    hasSpecularMap = false;
    textureType = TEXTURE_BASE;
}

Material::Material(Shader* shader, Texture* texture) : Material(shader, texture, vec3(0.1f), vec3(1), vec3(1)) {
    hasTexture = true;
    hasSpecularMap = false;
    textureType = TEXTURE_BASE;
}

Material::~Material() {
    delete shader;
}

Material* Material::fromFile(const string& filename) {
    ifstream file(filename);
    string vertFilename, fragFilename;
    float ambient, diffuse, specular;
    string textureFile, specularMapFile;
    
    file >> vertFilename >> fragFilename >> ambient >> diffuse >>
            specular >> textureFile >> specularMapFile;
    
    Shader* shader = Shader::fromFile(resourcePath() + vertFilename, resourcePath() + fragFilename);
    
    Material* material = new Material(shader, vec3(ambient), vec3(diffuse), vec3(specular));
    
    if (textureFile[0] != '!') {
        material->setTexture(Texture::loadFromFile(textureFile));
    }
    
    if (specularMapFile[0] != '!') {
        material->setSpecularMap(Texture::loadFromFile(specularMapFile));
    }
    
    return material;
}

Material* Material::clone() {
    return new Material(shader, texture, ambient, diffuse, specular);
}

void Material::use() {
    shader->use();
    if (hasTexture) {
        if (textureType == TEXTURE_BASE) texture->bind();
        if (textureType == TEXTURE_CUBEMAP) texture->bindCubemap();
        shader->setUniform("tex", (GLint)0);
    } else {
        Texture::unbind();
    }
    shader->setUniform("hasSpecmap", (GLboolean)hasSpecularMap);
    if (hasSpecularMap) {
        specularMap->bind(GL_TEXTURE1);
        shader->setUniform("specmap", (GLint)1);
    } else {
        Texture::unbind(GL_TEXTURE1);
    }
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

void Material::setTextureType(int textureType) {
    this->textureType = textureType;
}

void Material::setAnimatedUnlitProps(int tileDiv, float speed) {
    shader->setUniform("tileDiv", (GLuint)tileDiv);
    shader->setUniform("animSpeed", speed);
}

Texture* Material::getSpecularMap() {
    return specularMap;
}

void Material::setSpecularMap(Texture* texture) {
    this->specularMap = texture;
    hasSpecularMap = true;
}
