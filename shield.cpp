#include "shield.h"
#include "main.h"
#include<bits/stdc++.h>

using namespace std;

Shield::Shield(color_t color) {
    this->position = glm::vec3(0, 0, 0);
    this->in_action = false;







    GLfloat vertex_buffer_data[9];

    int i = 0;

            vertex_buffer_data[i*9]   = 0.0f;
            vertex_buffer_data[i*9+1] = 0.0f;
            vertex_buffer_data[i*9+2] = 0.0f;
            vertex_buffer_data[i*9+3] = 0.0f;
            vertex_buffer_data[i*9+4] = -0.2f;
            vertex_buffer_data[i*9+5] = 0.0f;
            vertex_buffer_data[i*9+6] = 1.0f;
            vertex_buffer_data[i*9+7] = -0.1f;
            vertex_buffer_data[i*9+8] = 0.0f;



    this->object = create3DObject(GL_TRIANGLES, 9, vertex_buffer_data, color, GL_FILL);
}

void Shield::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Shield::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
bool in_action = false;
int timerr = 0;
void Shield::tick()
{
    if(this->in_action)
    {
        timerr++;
        if(timerr==250)
                this->in_action = false;
    }


}
