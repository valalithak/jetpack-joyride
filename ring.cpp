#include "ring.h"
#include "main.h"
#include<bits/stdc++.h>

using namespace std;

Ring::Ring(float x, float y)
{
    this->position = glm::vec3(x, y, 0);
    this->radius1 =  1.5;// 0.2 for player
    this->radius2 =  0.8;// 0.2 for player
    color_t color1 = { 102, 0, 51 };
    color_t color2 = { 135,150,235 };

    float n = 180;
    float r = this->radius1;
    float theta = 2*3.14159/n;

    GLfloat vertex_buffer_data[180*9];

    int i;
    for(i=n/2; i<n; i++)
    {
        float angleBefore = theta * i;
        float angle = angleBefore + theta;

        float x = r * cos(angle);
        float y = r * sin(angle);
        float z = 0.0f;

        float x1 = r * cos(angleBefore);
        float y1 = r * sin(angleBefore);
        float z1 = 0.0f;

        float x2 = 0.0f;
        float y2 = 0.0f;
        float z2 = 0.0f;

        vertex_buffer_data[i*9] = x2;
        vertex_buffer_data[i*9+1] = y2;
        vertex_buffer_data[i*9+2] = z2;
        vertex_buffer_data[i*9+3] = x1;
        vertex_buffer_data[i*9+4] = y1;
        vertex_buffer_data[i*9+5] = z1;
        vertex_buffer_data[i*9+6] = x;
        vertex_buffer_data[i*9+7] = y;
        vertex_buffer_data[i*9+8] = z;
    }
    GLfloat vertex_buffer_data_2[180*9];

    float w2 = this->radius2;
    for(int j=n/2; j<n; j++)
    {
        float angleBefore2 = theta * j;
        float angle2 = angleBefore2 + theta;

        float x2 = w2 * cos(angle2);
        float y2 = w2 * sin(angle2);
        float z2 = 0.0f;

        float x12 = w2 * cos(angleBefore2);
        float y12 = w2 * sin(angleBefore2);
        float z12 = 0.0f;

        float x22 = 0.0f;
        float y22 = 0.0f;
        float z22 = 0.0f;

        vertex_buffer_data_2[j*9] = x22;
        vertex_buffer_data_2[j*9+1] = y22;
        vertex_buffer_data_2[j*9+2] = z22;
        vertex_buffer_data_2[j*9+3] = x12;
        vertex_buffer_data_2[j*9+4] = y12;
        vertex_buffer_data_2[j*9+5] = z12;
        vertex_buffer_data_2[j*9+6] = x2;
        vertex_buffer_data_2[j*9+7] = y2;
        vertex_buffer_data_2[j*9+8] = z2;
    }


    this->object1 = create3DObject(GL_TRIANGLES, 180*3, vertex_buffer_data, color1, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 180*3, vertex_buffer_data_2, color2, GL_FILL);
}

void Ring::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Ring::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}


void Ring::tick()
{
    return;
}
