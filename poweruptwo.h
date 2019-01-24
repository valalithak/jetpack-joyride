#include "main.h"

#ifndef POWERUPTWO_H
#define POWERUPTWO_H


class Poweruptwo {
public:
    Poweruptwo() {}
    Poweruptwo(color_t color);
    glm::vec3 position;
    float size;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    double acc_g;
    bool active;
    //int count;
    //bool fl;

private:
    VAO *object;
};

#endif
