#include "balloon.h"
#include "main.h"
#include<bits/stdc++.h>

using namespace std;

Balloon::Balloon(float x, float y)
{
    this->position = glm::vec3(x, y, 0);
    this->radius =  0.15;// 0.2 for player
    this->appear = false;
    color_t color = { 51, 51, 255 };
    speed = 0.1; // Speed of left-right key press in air


    float n = 360;
    float r = this->radius;
    float theta = 2*3.14159/n;

    GLfloat vertex_buffer_data[360*9];

    int i;
    for(i=0; i<n; i++)
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


    this->object = create3DObject(GL_TRIANGLES, 360*3, vertex_buffer_data, color, GL_FILL);
}

void Balloon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Balloon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
int w = 0; //count
int q = 0; //flag
void Balloon::tick()
{

    if(this->appear)
    {
            if(q==0)
            {
                w++;
                this->position.x += this->speed;
                this->position.y += this->speed;
                if(w==50)
                {
                    w = 0;
                    q = 1;
                }
            }
            if(q==1)
            {
                w++;
                this->position.x += this->speed;
                this->position.y -= this->speed;
                if(this->position.y <= 0.7)
                {
                    w = 0;
                    q = 0;
                    this->appear = false;
                }
            }
    }


}
