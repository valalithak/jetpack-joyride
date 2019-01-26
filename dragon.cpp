#include "dragon.h"
#include "main.h"
#include<bits/stdc++.h>

using namespace std;

Dragon::Dragon(float a, float b, color_t color1)
{
    this->position = glm::vec3(a, b, 0);
    speed = 0.08;

    float side = 0.5;

    float n = 360;
    float r = b/4;
    float theta = 2*3.14159/n;

    GLfloat buffer_body[360*9];

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

            buffer_body[i*9] = x2;
            buffer_body[i*9+1] = y2;
            buffer_body[i*9+2] = z2;
            buffer_body[i*9+3] = x1;
            buffer_body[i*9+4] = y1;
            buffer_body[i*9+5] = z1;
            buffer_body[i*9+6] = x;
            buffer_body[i*9+7] = y;
            buffer_body[i*9+8] = z;
    }


   this->object2 = create3DObject(GL_TRIANGLES, 360*3, buffer_body, color1, GL_FILL);
}

void Dragon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object2);
}

void Dragon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
int u = 0; // count
int n = 0; // flag
void Dragon::tick()
{
        if(n==0)
        {
            this->position.y += this->speed;
            u++;
            if(u==50)
            {
                u = 0;
                n = 1;
            }
        }
        if(n==1)
        {
            this->position.y -= this->speed;
            u++;
            if(u==50)
            {
                u = 0;
                n = 0;
            }
        }


}
