#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, float rad, color_t color);
    glm::vec3 position;
    float radius;
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

#endif // BALL_H
