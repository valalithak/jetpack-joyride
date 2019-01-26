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
    void tick(float rx, float ry, float r1, float r2);

    void magTick(int type);
    double speed;
    double acc_g;
    bool onground;
    bool inring;
    float inring_radius;

private:
    VAO *object;
};

#endif // BALL_H
