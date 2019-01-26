#include "dragon_face.h"
#include "main.h"
#include<bits/stdc++.h>

using namespace std;

Dragon_face::Dragon_face(float a, float b, color_t color1)
{
    this->position = glm::vec3(a, b, 0);

    speed = 0.08; // Speed of left-right key press in air

    float side = 1.1;
    GLfloat buffer_face[18];

    buffer_face[0] = a;
    buffer_face[1] = b;
    buffer_face[2] = 0;

    buffer_face[3] = a+side/2;
    buffer_face[4] = b + side/2;
    buffer_face[5] = 0;

    buffer_face[6] = a;
    buffer_face[7] = b+side;
    buffer_face[8] = 0;

    buffer_face[9]  = a;
    buffer_face[10] = b+side;
    buffer_face[11] = 0;

    buffer_face[12] = a;
    buffer_face[13] = b;
    buffer_face[14] = 0;

    buffer_face[15] = a-side/2;
    buffer_face[16] = b + side/2;
    buffer_face[17] = 0;



    this->object1 = create3DObject(GL_TRIANGLES, 9, buffer_face, color1, GL_FILL);

}

void Dragon_face::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);

}

void Dragon_face::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
int v = 0;
int g= 0;
void Dragon_face::tick()
{

    if(g==0)
    {
        this->position.y += this->speed;
        v++;
        if(v==50)
        {
            v = 0;
            g = 1;
        }
    }
    if(g==1)
    {
        this->position.y -= this->speed;
        v++;
        if(v==50)
        {
            v = 0;
            g = 0;
        }
    }



}
