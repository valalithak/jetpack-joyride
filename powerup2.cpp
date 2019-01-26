#include "poweruptwo.h"
#include "main.h"
#include<bits/stdc++.h>

using namespace std;
// DIAMOND SHAPED POWERUP WHICH SHOULD APPEAR RANDOMLY AND GIVE BONUS TO PLAYER
Poweruptwo::Poweruptwo(color_t color) {
    this->active = true;
    int x_coord = 5 + 1;
    int y_coord =  5;
    this->position = glm::vec3(x_coord, y_coord, 0);
    this->size = 0.1;
    speed = 0.05;


    GLfloat vertex_buffer_data[18];

    vertex_buffer_data[0] = x_coord;
    vertex_buffer_data[1] = y_coord;
    vertex_buffer_data[2] = 0;

    vertex_buffer_data[3] = x_coord-0.4;
    vertex_buffer_data[4] = y_coord;
    vertex_buffer_data[5] = 0;

    vertex_buffer_data[6] = x_coord+0.4;
    vertex_buffer_data[7] = y_coord + 0.4;
    vertex_buffer_data[8] = 0;

    vertex_buffer_data[9] = x_coord+0.4;
    vertex_buffer_data[10] = y_coord + 0.4;
    vertex_buffer_data[11] = 0;

    vertex_buffer_data[12] = x_coord;
    vertex_buffer_data[13] = y_coord + 0.4;
    vertex_buffer_data[14] = 0;

    vertex_buffer_data[15] = x_coord;
    vertex_buffer_data[16] = y_coord;
    vertex_buffer_data[17] = 0;


    this->object = create3DObject(GL_TRIANGLES, 9, vertex_buffer_data, color, GL_FILL);
}

void Poweruptwo::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Poweruptwo::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
int c2 = 0;
int fl2 = 0;
void Poweruptwo::tick()
{

    //cout << "p2 x : " <<  this->position.x << " "  << "p2 y : " <<  this->position.y << endl;
    if(fl2 == 0)
    {

        this->position.x += this->speed;
        this->position.y += this->speed/4;
        c2++;
        if(c2%100 == 0)
            fl2 = 1;
    }
    if(fl2 == 1)
    {
        this->position.x += this->speed;
        this->position.y -= this->speed/2;

        c2++;
        if(c2%100 == 0)
            fl2 = 2;
    }

    if(fl2==2)
    {
        this->position.x -= this->speed;
        this->position.y += this->speed/2;
        c2++;
        if(c2%100 == 0)
            fl2 = 3;
    }
    if(fl2==3)
    {
        this->position.x -= this->speed;
        this->position.y -= this->speed/2;
        c2++;
        if(c2%100 == 0)
            fl2 = 0;
    }

}
