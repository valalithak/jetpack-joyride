#include "main.h"

#ifndef DRAGON_FACE_H
#define DRAGON_FACE_H


class Dragon_face {
public:
    Dragon_face() {}
    Dragon_face(float a, float b, color_t color1);
    glm::vec3 position;
    float size;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;


private:
    VAO *object1;

};

#endif
