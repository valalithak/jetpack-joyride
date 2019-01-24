#include "main.h"

#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle {
public:
    Triangle() {}
    Triangle(color_t color);
    glm::vec3 position;
    float size;
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
    float speedHoriz;


private:
    VAO *object;
};

#endif
