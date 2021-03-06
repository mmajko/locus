//
//  Text2D.cpp
//  locus
//
//  Created by Marián Hlaváč on 10/12/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#include "Text2D.hpp"

Text2D::Text2D(string text, TextRenderer* renderer, vec2 position, vec3 color, float scale) : vao(MeshVAO()), vbo(MeshVBO(GL_ARRAY_BUFFER, NULL, sizeof(GLfloat) * 6 * 4, GL_DYNAMIC_DRAW)), renderer(renderer), color(color), text(text), scale(scale), position(position) {
    vao.bind();
    vbo.bind(GL_ARRAY_BUFFER);
    vbo.addAttrib(0, 4, GL_FLOAT, 4, 0);
    align = ALIGN_LEFT;
}

void Text2D::draw() {
    draw(vec4(0, 1280.0f, 0, 720.0f));
}

void Text2D::draw(vec4 proj) {
    glDisable(GL_DEPTH_TEST);
    renderer->use();
    renderer->getShader()->setUniform("textColor", color);
    
    glActiveTexture(GL_TEXTURE0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    vao.bind();
     
    mat4 projection = glm::ortho(proj.x, proj.y, proj.z, proj.w);
    renderer->getShader()->setUniform("mvp", projection);
    
    float xadvanced = position.x;
    float finalHeight = 0;
    float xOff = 0;
    
    if (align == ALIGN_CENTER) {
        string::const_iterator c;
        for (c = text.begin(); c != text.end(); c++) {
            TextRendererChar trc = renderer->getCharacter(*c);
            GLfloat width = trc.size.x * scale;
            xOff -= width / 2.0f;
        }
    }
    
    string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {
        TextRendererChar trc = renderer->getCharacter(*c);
        
        // Quad generation
        GLfloat xpos = xadvanced + trc.bearing.x * scale + xOff;
        GLfloat ypos = position.y - (trc.size.y - trc.bearing.y) * scale;
        GLfloat width = trc.size.x * scale;
        GLfloat height = trc.size.y * scale;
        finalHeight = height;
        
        GLfloat vertices[6][4] = {
            {xpos, ypos + height, 0, 0},
            {xpos, ypos, 0, 1},
            {xpos + width, ypos, 1, 1},
            {xpos, ypos + height, 0, 0},
            {xpos + width, ypos, 1, 1},
            {xpos + width, ypos + height, 1, 0},
        };
        
        // Bind texture and sub vertices
        glBindTexture(GL_TEXTURE_2D, trc.textureId);
        vbo.subData(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
        
        // Draw quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        // Advance next glyph
        xadvanced += (trc.advance >> 6) * scale;
    }
    
    size = vec2(xadvanced - position.x, finalHeight);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_DEPTH_TEST);
    vao.unbind();
}

vec3 Text2D::getColor() {
    return color;
}

void Text2D::setColor(vec3 color) {
    this->color = color;
}

void Text2D::setText(string text) {
    this->text = text;
}

vec2 Text2D::getSize() {
    return size;
}

void Text2D::setPosition(vec2 position) {
    this->position = position;
}

void Text2D::setAlign(int align) {
    this->align = align;
}

void Text2D::setRenderer(TextRenderer* renderer) {
    this->renderer = renderer;
}
