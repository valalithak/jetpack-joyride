#include "main.h"

#ifndef FIRE_H
#define FIRE_H


class Fire {
public:
    Fire() {}
    Fire(color_t color, float x1, float y1, float x2, float y2);
    glm::vec3 position;
    float size;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    double acc_g;
    bool touched;
    bool beam;
    float radius;
    float x1;
    float x2;
    float y1;
    float y2;



private:
    VAO *object1;
    VAO *object2;
};

#endif
