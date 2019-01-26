#include "main.h"

#ifndef ICE_H
#define ICE_H


class Ice {
public:
    Ice() {}
    Ice(float x, float y);
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
