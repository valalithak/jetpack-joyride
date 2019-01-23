#include "triangle.h"
#include "main.h"
#include<bits/stdc++.h>

using namespace std;

Triangle::Triangle(color_t color) {
    this->position = glm::vec3(0, 0, 0);
    this->size = 0.2;
    this->onground = true;
    speed = 0.2; // Speed of left-right key press in air
    speedVertical = 0.0; // Vertical speed in air - UP
    speedVerticalDown = 0.0; // Vertical speed in air - DOWN
    goDown = false;
    acc_g = 0.1; // Gravity acceleration
    initVelocity = 0.16;

    this->speedHoriz = 0.0;


    GLfloat vertex_buffer_data[9];

    int i = 0;

            vertex_buffer_data[i*9]   = -0.3f;
            vertex_buffer_data[i*9+1] = 0.0f;
            vertex_buffer_data[i*9+2] = 0.0f;
            vertex_buffer_data[i*9+3] = 0.3f;
            vertex_buffer_data[i*9+4] = 0.0f;
            vertex_buffer_data[i*9+5] = 0.0f;
            vertex_buffer_data[i*9+6] = 0.0f;
            vertex_buffer_data[i*9+7] = 0.5f;
            vertex_buffer_data[i*9+8] = 0.0f;



    this->object = create3DObject(GL_TRIANGLES, 9, vertex_buffer_data, color, GL_FILL);
}

void Triangle::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Triangle::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
