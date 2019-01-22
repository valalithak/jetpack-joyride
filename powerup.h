#include "main.h"

#ifndef POWERUP_H
#define POWERUP_H


class Powerup {
public:
    Powerup() {}
    Powerup(color_t color);
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
