#include "main.h"
#include "timer.h"
#include "ball.h"
#include "ground.h"
#include "triangle.h"
#include "boomerang.h"
#include "powerup.h"
#include "poweruptwo.h"
#include "fire.h"
#include "magnet.h"
#include "score.h"
#include "coin.h"
#include "balloon.h"
#include "ring.h"
#include "dragon.h"
#include "dragon_face.h"
#include "ice.h"
#include<bits/stdc++.h>
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

#define NUM_COINS 250
#define NUM_FIRES 8 // 4 fire beams and 4 fire lines
Ring ring;
Ball player;
Fire fire[NUM_FIRES];
Triangle tr;
Boomerang bmr;
Powerup p_up;
Poweruptwo p_up2;
Ground ground;
Magnet magnet;
Coin coins[NUM_COINS];
Score sc[3];
Balloon balloon;

Dragon dr;
Dragon eye1;
Dragon eye2;
Dragon_face face;
Ice ice;

float floorHeight = -0.7;
int i, j;
int score = 0;
int tick_count = 0;
int scu, sct, sch;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ground.draw(VP);
    ring.draw(VP);
    player.draw(VP);
    tr.draw(VP);
    if(balloon.appear){
        balloon.draw(VP);
        cout << "balloon x : " << balloon.position.x << " " << "balloon y : " << balloon.position.y << endl;
    }
    magnet.draw(VP);
    sc[0].draw(VP);
    sc[1].draw(VP);
    sc[2].draw(VP);
    if(p_up.active)
        p_up.draw(VP);
    if(p_up2.active)
        p_up2.draw(VP);
    dr.draw(VP);
    face.draw(VP);
    eye1.draw(VP);
    eye2.draw(VP);
    if(ice.appear)
        ice.draw(VP);

    for(j=0; j<NUM_FIRES;j++){
        if(fire[j].touched == false)
        fire[j].draw(VP);
    }


    if(bmr.collided == false && bmr.finish == false && player.position.x > 8)
        bmr.draw(VP);


    for(i=0; i<NUM_COINS; i++)
    {
        if(coins[i].position.y > 5/ screen_zoom)
            coins[i].position.y = (rand()%2 +2)/screen_zoom;
        if(coins[i].alive) {coins[i].draw(VP);}
    }

}

void tick_input(GLFWwindow *window) {
    int A  = glfwGetKey(window, GLFW_KEY_A);
    int D = glfwGetKey(window, GLFW_KEY_D);
    int B = glfwGetKey(window, GLFW_KEY_B);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    if (A) {
        player.position.x -= 0.3*player.speed;
        tr.position.x -= 0.3*player.speed;

    }
    if (D) {
        player.position.x += 0.3*player.speed;
        tr.position.x += 0.3*player.speed;
    }
    if (B) {
        balloon.position.x = player.position.x;
        balloon.position.y = player.position.y;
        balloon.appear = true;
    }
    if (space) {
        player.onground = false;
        player.position.y += player.speed;
        tr.onground = false;
        tr.position.y += player.speed;
    }

    int LEFT  = glfwGetKey(window, GLFW_KEY_LEFT);
    int RIGHT = glfwGetKey(window, GLFW_KEY_RIGHT);
    int UP = glfwGetKey(window, GLFW_KEY_UP);
    int DOWN = glfwGetKey(window, GLFW_KEY_DOWN);

    int flag=0;
    if (LEFT) {
        flag=1;
        pan_left();
    }
    if (RIGHT) {
        flag=1;
        pan_right();
    }
    if (UP) {
        flag=1;
        pan_up();
    }
    if (DOWN) {
        flag=1;
        pan_down();
    }

    if(flag) reset_screen();
}

void pan_left()
{
    screen_center_x -= 0.1;
    float left = screen_center_x - 4/screen_zoom;
    if(left < -40.0)
    {
        screen_center_x = -40.0 + 4/screen_zoom;
    }
}

void pan_right()
{
    screen_center_x += 0.1;
    float right = screen_center_x + 4/screen_zoom;
    if(right > 40.0)
    {
        screen_center_x = 40.0 - 4/screen_zoom;
    }
}

void pan_up()
{
    screen_center_y += 0.1;
    float up = screen_center_y + 4/screen_zoom;
    if(up > 40.0)
    {
        screen_center_y = 40.0 - 4/screen_zoom;
    }
}

void pan_down()
{
    screen_center_y -= 0.1;
    float down = screen_center_y - 4/screen_zoom;
    if(down < -40.0)
    {
        screen_center_y = -40.0 + 4/screen_zoom;
    }
}

void tick_elements()
{
    face.position.x = dr.position.x;
    face.position.y = dr.position.y+0.75;
    eye1.position.x = face.position.x-0.3;
    eye1.position.y = face.position.y +0.6;
    eye2.position.x = eye1.position.x+0.6;
    eye2.position.y = eye1.position.y;




    magnet.tick();
    if(magnet.field == true && player.inring == false)
    {
        if(player.position.y > 2)
        {
            player.position.y -= 0.02;
        }
        if(player.position.y < 2)
        {
            player.position.y += 0.02;
        }
        if(player.position.x < magnet.position.x)
        {
            player.position.x += 0.02;
        }
        if(player.position.x > magnet.position.x)
        {
            player.position.x -= 0.02;
        }

    }


    balloon.tick();
    if(player.position.x > dr.position.x - 5)
        ice.appear = true;

    ice.tick();

    //cout << "balloon : " << balloon.position.y << " " << balloon.appear << endl;
    player.tick(ring.position.x, ring.position.y, ring.radius1, ring.radius2);
    {
        tr.position.x = player.position.x;
        tr.position.y = player.position.y - 0.7;
        sc[0].position.x = player.position.x;
        sc[1].position.x = player.position.x - 0.5;
        sc[2].position.x = player.position.x - 1;
    }
    p_up.tick();//tr.tick();
    p_up2.tick();
    for(i=0; i<NUM_FIRES; i++)
        fire[i].tick();
    if(player.position.x > bmr.radius_of_path - 5 && bmr.finish == false)
    {
        bmr.tick();

        if(abs(player.position.x - bmr.position.x) < 1.5*player.radius && (-(player.position.y - bmr.position.y) < 1.5*player.radius)){
                bmr.collided = true;
                cout << "first" << endl;
        }

        if (abs(player.position.x - bmr.position.x) < 1.8*player.radius && player.position.y == 0.7 && bmr.position.y < 0) {
                bmr.collided = true;
                cout << "second" << endl;
        }
        if(bmr.collided == true)// && bmr.finish == false)
        {
            score -= 20;
            cout << "Boomerang collision" << endl;

            if(score>999)
                score = 999;
            //if(score<0)
            //    score = 0;

            scu = score%10;
            sct = (score/10)%10;
            sch = (score/100)%10;
            bmr.finish = true;
        }
        // cout << player.position.x << " " << p_up.position.x << endl;
        // cout << player.position.y << " " << p_up.position.y << endl;
    }
    // PATH OF PLAYER IN RING
    if(player.position.x >= ring.position.x - ring.radius1 && player.position.x <=ring.position.x - ring.radius2 && player.position.y >= ring.position.y){
        cout << " ring matched " << endl;
        player.inring = true;
    }

    if((player.position.y > 0.7))
    {
        for(i=0; i<NUM_COINS; i++)
        {
            if(coins[i].alive && detect_collision(i, 0))
            {
                    cout << "coins collided" << endl;
                    score+= coins[i].score;
                    if(score>999)
                        score = 999;
                    //if(score<0)
                    //    score = 0;

                    scu = score%10;
                    sct = (score/10)%10;
                    sch = (score/100)%10;
                    coins[i].alive = false;
            }

        }

    }

    for(i=0; i<NUM_FIRES; i++)
    {
        //while(player.position.x > 4*i + 3)
        //    i++;
        if(detect_collision(i,1) && fire[i].touched == false )
        {
            fire[i].touched = true;
            score -= 5;
            cout << "fire collision location" << endl;
            cout << fire[i].x1 << " " << fire[i].y1 << endl;
            cout << fire[i].x2 << " " << fire[i].y2 << endl;
            cout << player.position.x << " " << player.position.y << endl;
            if(score>999)
                score = 999;
            //if(score<0)
            //    score = 0;
            scu = score%10;
            sct = (score/10)%10;
            sch = (score/100)%10;
            break;
        }
    }


    if(p_up.active && detect_collision_bonus(1))
    {
        score += 20;
        cout << "collidded bonus 1" << endl;
        if(score>999)
            score = 999;

        scu = score%10;
        sct = (score/10)%10;
        sch = (score/100)%10;
        //cout << "collided" << endl;
        p_up.active = false;
    }
    if(p_up2.active && detect_collision_bonus(2))
    {
        score += 20;
        cout << "collidded bonus 2" << endl;
        if(score>999)
            score = 999;

        scu = score%10;
        sct = (score/10)%10;
        sch = (score/100)%10;
        //cout << "collided" << endl;
        p_up2.active = false;
    }
    for(int x = 0; x<NUM_FIRES; x++){
    if(detect_balloon_fire(x)){
        cout << "yes" << endl;
        }
    }



    float left = screen_center_x - 4/screen_zoom;
    if(player.position.x - player.radius < left)
    {
        if(player.position.x - player.radius < -40.0)
            player.position.x = -40.0 + player.radius;

        screen_center_x = (player.position.x - player.radius) + 4/screen_zoom;
    }

    float right = screen_center_x + 4/screen_zoom;
    if(player.position.x + player.radius > right)
    {
        if(player.position.x + player.radius > 800.0)
            player.position.x = 800.0 - player.radius;

        screen_center_x = 2*(player.position.x + player.radius) - 4/screen_zoom;
    }

    reset_screen();
    sc[0].val = scu;
    sc[1].val = sct;
    sc[2].val = sch;

}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    player      = Ball(0, 0.7, 0.2, COLOR_GREY);
    ring        = Ring(40, 3);
    tr          = Triangle(COLOR_YELLOW);
    bmr         = Boomerang(COLOR_BLACK);
    ground      = Ground(floorHeight + 3*player.radius, -4.0);
    p_up        = Powerup(COLOR_RED);
    p_up2       = Poweruptwo(COLOR_LIGHTGREY);
    magnet      = Magnet(1);
    sc[0]       = Score(screen_center_x, -2, scu, COLOR_WHITE);
    sc[1]       = Score(screen_center_x - 1, -2, sct, COLOR_WHITE);
    sc[2]       = Score(screen_center_x - 2, -2, sch, COLOR_WHITE);
    balloon     = Balloon(0, 0);

    dr          = Dragon(48, 3, COLOR_GREEN);
    eye1         = Dragon(0,0.4, COLOR_BLACK);
    eye2         = Dragon(0,0.4, COLOR_BLACK);
    face        = Dragon_face(0, 0, COLOR_GREEN);
    ice         = Ice(48, 3.3);
    for(j=1; j<=NUM_FIRES; j++)
    {

        if(j%2==0) // it is a fire beam
        {
            float yfire_1      = 1.5;
            float xfire_1      = 4*j+1;
            float xfire_2      = xfire_1 + 3;
            float yfire_2      = yfire_1;
            fire[j-1]            = Fire(COLOR_FIRE, xfire_1, yfire_1, xfire_2, yfire_2);
            fire[j-1].beam = true;
        }
        else if(j%7==0) // it is a fire line
        {
            float yfire_1      = 2;
            float xfire_1      = 4*j + 1;
            float xfire_2      = xfire_1 + 3;
            float yfire_2      = yfire_1 - 0.4;
            fire[j-1]            = Fire(COLOR_FIRE, xfire_1, yfire_1, xfire_2, yfire_2);
        }
        else  // it is a fire line
        {
            float yfire_1      = 2;
            float xfire_1      = 4*j + 1;
            float xfire_2      = xfire_1 + 3;
            float yfire_2      = yfire_1 + 0.3;
            fire[j-1]            = Fire(COLOR_FIRE, xfire_1, yfire_1, xfire_2, yfire_2);
        }


    }

    //cout << player.position.y << endl;

    for(i=0; i<NUM_COINS; i++)
    {
        coins[i] = Coin(1.0+(i*1.5), floorHeight + 4*player.radius + i); // on right side of origin

    }

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv)
{
    srand(time(0));
    int width  = 800;
    int height = 800;

    window = initGLFW(width, height);

    initGL (window, width, height);
    int tick_count = 2*magnet.dashIn + magnet.stay;
    int gap = 1750; // Time between departure of old magnet and arrival of new
    glfwSetScrollCallback(window, scroll_callback);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {

            tick_count++;


            if(tick_count == gap + 1.5*magnet.dashIn + magnet.stay)
            {
               tick_count=0;
               magnet.start(rand()%2 + 1);
            }




            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);

            char titleString[64];
            sprintf(titleString, "Score: %d", score);
            glfwSetWindowTitle(window,titleString);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

float abso(float x)
{
    if(x<0) x=-x;
    return x;
}

bool detect_collision(int i, int type)
{
    // for coin collision, type= 0
    if(type == 0)
    {
        Coin coin = coins[i];
        //if(player.speedVertical > 0) return false;
        if(abso(player.position.x - coin.position.x) < (player.radius + coin.radius)
            && player.position.y > coin.position.y
            && player.position.y - coin.position.y <= (player.radius + coin.radius)
            ) return true;
        return false;
    }
    if(type == 1)
    {
        int xflag = 0;
        int yflag = 0;

        Fire f= fire[i];
        //if(player.speedVertical > 0) return false;
        if(player.position.x >= 4*(i+1)+3 && player.position.x <= 4*(i + 1)+4)
            xflag = 1;
        if(i%2==0)
        {
            if(player.position.y >= 1.4 && player.position.y <= 1.6)
            yflag = 1;
        }
        else if(i%7==0)
        {
            if(player.position.y >= 1.57 && player.position.y <= 2)
                yflag = 1;
        }
        else
        {
            if(player.position.y >= 1.95 && player.position.y <= 2.35)
                yflag = 1;
        }
        if(xflag==1 && yflag ==1)
            return true;
        return false;
    }

}


bool detect_collision_bonus(int p)
{

    //if(player.speedVertical > 0) return false;
    //cout << player.position.x << " " << p_up.position.x << endl;
    //cout << player.position.y << " " << p_up.position.y << endl;
    if(p==1)
    {
        if(abso(player.position.x - p_up.position.x) <= player.radius + p_up.size && abso(player.position.y - p_up.position.y) <= player.radius + p_up.size)
            return true;
        return false;
    }
    if(p==2)
    {
        if(abso(player.position.x - p_up2.position.x) <= player.radius + p_up2.size && abso(player.position.y - p_up2.position.y) <= player.radius + p_up2.size)
            return true;
        return false;
    }
}


void reset_screen()
{
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;

    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 2000.0f);
}

bool detect_balloon_fire(int i)
{
    int xflag = 0;
    int yflag = 0;

    Fire f= fire[i];
    //if(player.speedVertical > 0) return false;
    if(balloon.position.x >= 4*(i+1) && balloon.position.x <= 4*(i + 1)+4)
        xflag = 1;
    if(i%2==0)
    {
        if(balloon.position.y >= 1.41 && balloon.position.y <= 1.63)
        yflag = 1;
    }
    else if(i%7==0)
    {
        if(balloon.position.y >= 1.6 && balloon.position.y <= 2.05)
            yflag = 1;
    }
    else
    {
        if(balloon.position.y >= 1.95 && balloon.position.y <= 2.35)
            yflag = 1;
    }
    if(xflag==1 && yflag ==1){
        fire[i].touched = true;
        return true;
    }
    return false;
}
