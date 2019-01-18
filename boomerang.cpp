#include "boomerang.h"
#include "main.h"
#include<bits/stdc++.h>

using namespace std;

Boomerang::Boomerang(color_t color) {
    this->position = glm::vec3(-2, 0, 0);
    //this->size = 0.2;
    //this->onground = true;
    //speed = 0.2; // Speed of left-right key press in air
    //speedVertical = 0.0; // Vertical speed in air - UP
    //speedVerticalDown = 0.0; // Vertical speed in air - DOWN
    //goDown = false;
    //acc_g = 0.1; // Gravity acceleration
    //initVelocity = 0.16;

    //this->speedHoriz = 0.0;


    GLfloat vertex_buffer_data[18];



            vertex_buffer_data[0]   = -1-0.5f;
            vertex_buffer_data[1] = 1;
            vertex_buffer_data[2] = 0.0f;

            vertex_buffer_data[3] = -0.4f;
            vertex_buffer_data[4] = 1.5f;
            vertex_buffer_data[5] = 0.0f;

            vertex_buffer_data[6] = -0.4f;
            vertex_buffer_data[7] = 1.8f;
            vertex_buffer_data[8] = 0.0f; // left triangle

            vertex_buffer_data[9] = 0.2f+0.5f;
            vertex_buffer_data[10] = 1;
            vertex_buffer_data[11] = 0.0f;

            vertex_buffer_data[12] = -0.4f;
            vertex_buffer_data[13] = 1.5f;
            vertex_buffer_data[14] = 0.0f;

            vertex_buffer_data[15] = -0.4f;
            vertex_buffer_data[16] = 1.8f;
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

//void Boomerang::tick() {
    //this->ground = false;
    /*if(this->onground == false)
    {
        this->position.y -= acc_g;
        //cout << 1 << endl;
    }
    if(this->position.y >= (floorHeight + 19*this->size)/screen_zoom){
        this->position.y = (floorHeight + 19*this->size)/screen_zoom;
        cout << 2 << endl;
    }
    if(this->position.y <= 0){
        this->onground = true;

    }*/

//}
