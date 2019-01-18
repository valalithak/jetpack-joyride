#include "coin.h"
#include "main.h"

Coin::Coin(float x, float minHeight)
{

    this->alive = true;
    int max_angle = 40;
    this->rotation = (rand()%(1+2*max_angle)) - max_angle;
    this->rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));

    float diff = 2.0 - minHeight;
    float multiplier = ((float) rand()) / (float) RAND_MAX;
    float y = minHeight + diff*multiplier;

    float Radii[3] = {0.09,0.1,0.2};
    color_t Colors[3] = {COLOR_ORANGE, COLOR_YELLOW, COLOR_RED};

    this->position = glm::vec3(x, y, 0);

    float diff2 = 0.02;
    float multiplier2 = ((float) rand()) / (float) RAND_MAX;

    this->type = rand()%3;
    this->radius = Radii[this->type];

    float n = 360;
    float r = this->radius;
    float theta = 2*3.14159/n;

    int numTriangles = 3000;

    GLfloat vertex_buffer_data[numTriangles*9];

    int i;
    for(i=0; i<numTriangles; i++)
    {
            float angleBefore = theta * (i+20);
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

            vertex_buffer_data[i*9] = x2;
            vertex_buffer_data[i*9+1] = y2;
            vertex_buffer_data[i*9+2] = z2;
            vertex_buffer_data[i*9+3] = x1;
            vertex_buffer_data[i*9+4] = y1;
            vertex_buffer_data[i*9+5] = z1;
            vertex_buffer_data[i*9+6] = x;
            vertex_buffer_data[i*9+7] = y;
            vertex_buffer_data[i*9+8] = z;
    }

    this->object = create3DObject(GL_TRIANGLES, numTriangles*3, vertex_buffer_data, Colors[this->type], GL_FILL);
}

void Coin::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


void Coin::tick() {
    //this->position.x += this->speed;
}
