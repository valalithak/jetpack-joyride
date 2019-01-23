#include "boomerang.h"
#include "main.h"
#include<bits/stdc++.h>
#include<math.h>

using namespace std;

Boomerang::Boomerang(color_t color) {
    this->collided = false;
    this->finish = true;
    this->radius_of_path = 20;
    this->position = glm::vec3(this->radius_of_path, 1, 0); // mod of x coordinate here will be the radius of trajectory
    this->size = 0.2;
    this->onground = true;
    speed = 0.2; // Speed of left-right key press in air
    acc_g = 0.1; // Gravity acceleration

    count = 0;
    flag = 0;
    angle_rad = 3.14159/180;
    degree = 360;
    GLfloat vertex_buffer_data[18];



            vertex_buffer_data[0]   = -1;
            vertex_buffer_data[1] = 1;
            vertex_buffer_data[2] = 0.0f;

            vertex_buffer_data[3] = -0.4f+0.1f;
            vertex_buffer_data[4] = 1.3f;
            vertex_buffer_data[5] = 0.0f;

            vertex_buffer_data[6] = -0.4f+0.1f;
            vertex_buffer_data[7] = 1.5f;
            vertex_buffer_data[8] = 0.0f; // left triangle

            vertex_buffer_data[9] = 0.2f+0.2f;
            vertex_buffer_data[10] = 1;
            vertex_buffer_data[11] = 0.0f;

            vertex_buffer_data[12] = -0.4f+0.1f;
            vertex_buffer_data[13] = 1.3f;
            vertex_buffer_data[14] = 0.0f;

            vertex_buffer_data[15] = -0.4f+0.1f;
            vertex_buffer_data[16] = 1.5f;
            vertex_buffer_data[17] = 0.0f;  // right triangle



    this->object = create3DObject(GL_TRIANGLES, 9, vertex_buffer_data, color, GL_FILL);
}

void Boomerang::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

//void Boomerang::set_position(float x, float y) {
//    this->position = glm::vec3(x, y, 0);
//}

void Boomerang::tick() {

    if(flag==0)
    {
        this->position.x -= this->speed/2;
        count++;
        if(count==100){
            flag = 1;
            count = 0;
        }
    }
    if(flag==1)
    {
        this->position.x -= this->speed/4;
        this->position.y -= this->speed/4;
        count++;
        if(count==20){
            flag = 6;
            count = 0;
        }
    }
    if(flag==6)
    {
        this->position.y -= this->speed/5;
        count++;
        if(count==5)
        {
            flag = 2;
            count = 0;
        }
    }
    if(flag==2)
    {
        this->position.x += this->speed/4;
        this->position.y -= this->speed/4;
        count++;
        if(count==20){
            flag = 3;
            count = 0;
        }
    }
    if(flag==3)
    {
        this->position.x += this->speed/2;
        count++;
        if(count==100){
            flag = 4;
            count = 0;
            this->finish = true;
        }

    }





}
