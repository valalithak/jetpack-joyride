#include "main.h"

#ifndef BALLOON_H
#define BALLOON_H


class Balloon {
public:
    Balloon() {}
    Balloon(float x, float y);
    glm::vec3 position;
    float radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bool appear;
    float speed;

private:
    VAO *object;
};

#endif // BALL_H
