#include "dragon.h"
#include "main.h"
#include<bits/stdc++.h>

using namespace std;

Dragon::Dragon(float a, float b)
{
    this->position = glm::vec3(a, b, 0);
    //this->size = 0.2;
    // this->onground = true;
    speed = 0.08; // Speed of left-right key press in air
    color_t color1 = {0,0,0};
    color_t color2 = {200,0,0};
    float side = 0.5;
    GLfloat buffer_face[18];

    buffer_face[0] = a+3;
    buffer_face[1] = b+3;
    buffer_face[2] = 0;

    buffer_face[3] = a+side/2+3;
    buffer_face[4] = b + side/2+3;
    buffer_face[5] = 0;

    buffer_face[6] = a+3;
    buffer_face[7] = b+side+3;
    buffer_face[8] = 0;

    buffer_face[9]  =a+3;
    buffer_face[10] = b+side+3;
    buffer_face[11] = 0;

    buffer_face[12] = a+3;
    buffer_face[13] = b+3;
    buffer_face[14] = 0;

    buffer_face[15] = a-side/2+3;
    buffer_face[16] = b + side/2+3;
    buffer_face[17] = 0;



    this->object1 = create3DObject(GL_TRIANGLES, 9, buffer_face, color1, GL_FILL);
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


   this->object2 = create3DObject(GL_TRIANGLES, 360*3, buffer_body, color2, GL_FILL);
}

void Dragon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Dragon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Dragon::tick()
{

//    cout << "flag: " << fl << " " << "count: " << c << endl;



}
