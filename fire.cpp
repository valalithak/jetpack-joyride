#include "fire.h"
#include "main.h"
#include<bits/stdc++.h>

using namespace std;
// RECTANGLE OF FIRE FOR ENEMIES 1 AND 2
Fire::Fire(color_t color, float x1, float y1, float x2, float y2)
{
    this->active = true;
    this->position = glm::vec3(x1, y1, 0);
    this->size = 0.2;
    int cylinder_radius = 0.2;

    speed = 0.12;


    GLfloat vertex_buffer_data[18];

    vertex_buffer_data[0] = x1;
    vertex_buffer_data[1] = y1;
    vertex_buffer_data[2] = 0;

    vertex_buffer_data[3] = x2;
    vertex_buffer_data[4] = y2;
    vertex_buffer_data[5] = 0;

    vertex_buffer_data[6] = (x2+x1)/2;
    vertex_buffer_data[7] = (y2+y1)/2+0.1;
    vertex_buffer_data[8] = 0;

    vertex_buffer_data[9] = x1;
    vertex_buffer_data[10] = y1;
    vertex_buffer_data[11] = 0;

    vertex_buffer_data[12] = x2;
    vertex_buffer_data[13] = y2;
    vertex_buffer_data[14] = 0;

    vertex_buffer_data[15] = (x2+x1)/2;
    vertex_buffer_data[16] = (y2+y1)/2-0.1;
    vertex_buffer_data[17] = 0;



    this->object = create3DObject(GL_TRIANGLES, 9, vertex_buffer_data, color, GL_FILL);
}


void Fire::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Fire::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Fire::tick()
{
    return;
}
