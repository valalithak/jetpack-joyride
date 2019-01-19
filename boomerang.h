#include "main.h"

#ifndef BOOMERANG_H
#define BOOMERANG_H


class Boomerang {
public:
    Boomerang() {}
    Boomerang(color_t color);
    glm::vec3 position;
    float size;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    int count;
    int flag;
    float angle_rad;
    int degree;
    int radius_of_path;
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
