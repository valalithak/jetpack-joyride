#include "fire.h"
#include "main.h"
#include<bits/stdc++.h>

using namespace std;
// RECTANGLE OF FIRE FOR ENEMIES 1 AND 2
Fire::Fire(color_t color, float x1, float y1, float x2, float y2)
{
    this->beam = false;
    this->x1 = x1;
    this->x2 = x2;
    this->y1 = y1;
    this->y2 = y2;
    this->position = glm::vec3(min(x1,x2), min(y1,y2), 0);
    this->size = 0.2;
    this->radius = 0.2;
    this->touched = false;

    speed = 0.05;


    GLfloat vertex_buffer_data[18];

    vertex_buffer_data[0] = x1;
    vertex_buffer_data[1] = y1;
    vertex_buffer_data[2] = 0;

    vertex_buffer_data[3] = x2;
    vertex_buffer_data[4] = y2;
    vertex_buffer_data[5] = 0;

    vertex_buffer_data[6] = x1;
    vertex_buffer_data[7] = y1 + 0.3;
    vertex_buffer_data[8] = 0;

    vertex_buffer_data[9] = x1;
    vertex_buffer_data[10] = y1 + 0.3;
    vertex_buffer_data[11] = 0;

    vertex_buffer_data[12] = x2;
    vertex_buffer_data[13] = y2;
    vertex_buffer_data[14] = 0;

    vertex_buffer_data[15] = x2;
    vertex_buffer_data[16] = y2+0.3;
    vertex_buffer_data[17] = 0;


    float n = 360;
    float r = this->radius;
    float theta = 2*3.14159/n;


    this->object1 = create3DObject(GL_TRIANGLES, 9, vertex_buffer_data, color, GL_FILL);
}

void Fire::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    //draw3DObject(this->object2);
}

void Fire::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
int t = 0;
bool f = 0;

void Fire::tick()
{
    if(this->beam)
    {
        if(f==0)
        {
            
            t++;
            this->position.y += speed;
            if(t==100)
            {
                f = 1;
                t =0;
            }
        }
        if(f == 1)
        {

            t++;
            this->position.y -= speed;
            if(t==100)
            {
                f = 0;
                t = 0;
            }
        }
    }

    return;
}
