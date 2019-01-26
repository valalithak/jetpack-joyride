#include "powerup.h"
#include "main.h"
#include<bits/stdc++.h>

using namespace std;
// DIAMOND SHAPED POWERUP WHICH SHOULD APPEAR RANDOMLY AND GIVE BONUS TO PLAYER
Powerup::Powerup(color_t color) {
    this->active = true;
    float x_coord = 15;
    float y_coord =  1.1;
    this->position = glm::vec3(x_coord, y_coord, 0);
    this->size = 0.2;
    // this->onground = true;
    speed = 0.08; // Speed of left-right key press in air


    GLfloat vertex_buffer_data[18];

    vertex_buffer_data[0] = x_coord;
    vertex_buffer_data[1] = y_coord;
    vertex_buffer_data[2] = 0;

    vertex_buffer_data[3] = x_coord-0.25;
    vertex_buffer_data[4] = y_coord + 0.25;
    vertex_buffer_data[5] = 0;

    vertex_buffer_data[6] = x_coord+0.25;
    vertex_buffer_data[7] = y_coord + 0.25;
    vertex_buffer_data[8] = 0;

    vertex_buffer_data[9] = x_coord-0.25;
    vertex_buffer_data[10] = y_coord + 0.25;
    vertex_buffer_data[11] = 0;

    vertex_buffer_data[12] = x_coord+0.25;
    vertex_buffer_data[13] = y_coord + 0.25;
    vertex_buffer_data[14] = 0;

    vertex_buffer_data[15] = x_coord;
    vertex_buffer_data[16] = y_coord+0.5;
    vertex_buffer_data[17] = 0;



    this->object = create3DObject(GL_TRIANGLES, 9, vertex_buffer_data, color, GL_FILL);
}

void Powerup::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Powerup::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
int c = 0;
int l = 0;
void Powerup::tick()
{

     if(l == 0)
    {

        this->position.x += this->speed;
        this->position.y += this->speed/4;
        c++;
        if(c>=100)
        {
            l = 1;
            c = 0;
        }
    }
    if(l == 1)
    {
        this->position.x += this->speed;
        this->position.y -= this->speed/4;

        c++;
        if(c>=100)
        {
            l = 2;
            c =0;
        }
    }

    if(l==2)
    {
        this->position.x -= this->speed;
        this->position.y += this->speed/4;
        c++;


        if(c>=100)
        {
            l = 3;
            c=0;
        }
    }
    if(l==3)
    {
        this->position.x -= this->speed;
        this->position.y -= this->speed/4;
        c++;
        if(c>=100)
        {
            l = 0;
            c=0;
        }
    }

}
