#include "boomerang.h"
#include "main.h"
#include<bits/stdc++.h>
#include<math.h>

using namespace std;

Boomerang::Boomerang(color_t color) {
    this->radius_of_path = 2;
    this->position = glm::vec3(-this->radius_of_path, 0, 0); // mod of x coordinate here will be the radius of trajectory
    this->size = 0.2;
    this->onground = true;
    speed = 0.2; // Speed of left-right key press in air
    acc_g = 0.1; // Gravity acceleration

    count = 0;
    flag = 0;
    angle_rad = 3.14159/180;
    degree = 180;
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

void Boomerang::tick() {

    if(degree!=0 && flag == 0)
    {
        this->position.x = this->radius_of_path*cos(angle_rad*degree)/screen_zoom;
        this->position.y = this->radius_of_path*sin(angle_rad*degree)/screen_zoom;
        degree--;
        //cout << 2*cos(angle_rad*degree) << " " << 2*sin(angle_rad*degree) << endl;
        //cout << degree << " " <<  flag << " " << "loop1" <<  endl;
    }

    if(degree%180 == 0 && this->position.y > (floorHeight)/screen_zoom)
    {
        if(flag==0)
            flag = 1;
        else if(flag==2)
            flag =0;
        this->position.y -= acc_g;

        //cout << degree << " " <<  flag << " " << "loop2" <<  endl;
    }
    if(flag > 0 && this->position.y <= floorHeight/screen_zoom){

        degree = 0;

        if(flag == 1)
            flag = 2;
        else if(flag == 2)
        {
            flag = 0;
            degree = 180;
        }
        //cout << degree << " " <<  flag << " " << "loop3" <<  endl;
    }
    if(flag == 2 && degree <= 180)
    {
        this->position.x = 2*cos(angle_rad*degree);
        this->position.y = 2*sin(angle_rad*degree);
        degree++;
        //cout << degree << " " <<  flag << " " << "loop4" <<  endl;
    }

}
