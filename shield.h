#include "main.h"

#ifndef SHIELD_H
#define SHIELD_H

class Shield {
public:
    Shield() {}
    Shield(color_t color);
    glm::vec3 position;
    float size;
    float called;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();

    void magTick(int type);
    double speed;
    double speedVertical;
    double speedVerticalDown;
    bool goDown;
    double acc_g;
    double initVelocity;
    bool onground;
    bool in_action;
    float speedHoriz;


private:
    VAO *object;
};

#endif
