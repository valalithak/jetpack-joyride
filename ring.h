#include "main.h"

#ifndef RING_H
#define RING_H


class Ring {

    public:
        Ring() {}
        Ring(float x, float y);
        glm::vec3 position;
        float radius1;
        float radius2;
        void draw(glm::mat4 VP);
        void set_position(float x, float y);
        void tick();

    private:
        VAO *object1;
        VAO *object2;
};

#endif // BALL_H
