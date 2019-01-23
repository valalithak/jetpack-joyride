#include "fire.h"
#include "main.h"
#include<bits/stdc++.h>

using namespace std;
// RECTANGLE OF FIRE FOR ENEMIES 1 AND 2
Fire::Fire(color_t color, float x1, float y1, float x2, float y2)
{
    this->beam = false;
    this->position = glm::vec3(x1, y1, 0);
    this->size = 0.2;
    this->radius = 0.2;
    speed = 0.12;


    GLfloat vertex_buffer_data[18];

    vertex_buffer_data[0] = x1;
    vertex_buffer_data[1] = y1;
    vertex_buffer_data[2] = 0;

    vertex_buffer_data[3] = x2;
    vertex_buffer_data[4] = y2;
    vertex_buffer_data[5] = 0;

    vertex_buffer_data[6] = x1;
    vertex_buffer_data[7] = y1 + 0.15;
    vertex_buffer_data[8] = 0;

    vertex_buffer_data[9] = x1;
    vertex_buffer_data[10] = y1 + 0.15;
    vertex_buffer_data[11] = 0;

    vertex_buffer_data[12] = x2;
    vertex_buffer_data[13] = y2;
    vertex_buffer_data[14] = 0;

    vertex_buffer_data[15] = x2;
    vertex_buffer_data[16] = y2+0.15;
    vertex_buffer_data[17] = 0;


    float n = 360;
    float r = this->radius;
    float theta = 2*3.14159/n;

        /*GLfloat vertex_buffer_data2[360*9];

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

                vertex_buffer_data2[i*9] = x2;
                vertex_buffer_data2[i*9+1] = y2;
                vertex_buffer_data2[i*9+2] = z2;
                vertex_buffer_data2[i*9+3] = x1;
                vertex_buffer_data2[i*9+4] = y1;
                vertex_buffer_data2[i*9+5] = z1;
                vertex_buffer_data2[i*9+6] = x;
                vertex_buffer_data2[i*9+7] = y;
                vertex_buffer_data2[i*9+8] = z;
        }


        this->object2 = create3DObject(GL_TRIANGLES, 360*3, vertex_buffer_data, color, GL_FILL);*/
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
            float var = (rand()%3)/10 + 0.1;
            t++;
            this->position.y += var;
            if(t==100)
            {
                f = 1;
                t =0;
            }
        }
        if(f == 1)
        {
            float var = (rand()%3)/10 + 0.1;
            t++;
            this->position.y -= var;
            if(t==100)
            {
                f = 0;
                t =0;
            }
        }
    }

    return;
}
