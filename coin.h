#include "main.h"

#ifndef COIN_H
#define COIN_H


class Coin {
public:
    Coin() {}
    Coin(float x, float minHeight);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void block_draw(glm::mat4 VP);
    void tick();
    float radius;
    double speed;
    bool alive;
    int type;
    float rotation;
    glm::mat4 rotate;
    glm::mat4 rotMatrix;
private:
    VAO *object;
    VAO *block_object;
};

#endif
