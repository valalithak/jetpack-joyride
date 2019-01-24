#include "main.h"
#include "timer.h"
#include "ball.h"
#include "ground.h"
#include "triangle.h"
#include "boomerang.h"
#include "powerup.h"
#include "powerup.h"
#include "fire.h"
#include "magnet.h"
#include "score.h"
#include "coin.h"
#include<bits/stdc++.h>
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

#define NUM_COINS 250
#define NUM_FIRES 16 // 4 fire beams and 4 fire lines
Ball player;
Fire fire[NUM_FIRES];
Triangle tr;
Boomerang bmr;
Powerup p_up;
Ground ground;
Magnet magnet;
Coin coins[NUM_COINS];
Score sc[3];

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
    player.draw(VP);
    tr.draw(VP);
    magnet.draw(VP);
    sc[0].draw(VP);
    sc[1].draw(VP);
    sc[2].draw(VP);


    for(j=0; j<NUM_FIRES;j++){
        if(fire[j].touched == false)
        fire[j].draw(VP);
    }


    if(bmr.collided == false && bmr.finish == false && player.position.x > 8)
        bmr.draw(VP);
    if(p_up.active)
        p_up.draw(VP);

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
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    if (A) {
        player.position.x -= 0.3*player.speed;
        tr.position.x -= 0.3*player.speed;

    }
    if (D) {
        player.position.x += 0.3*player.speed;
        tr.position.x += 0.3*player.speed;
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
    magnet.tick();
    if(magnet.field == true)
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
    player.tick();
    {
        tr.position.x = player.position.x;
        tr.position.y = player.position.y - 0.7;
    }
    p_up.tick();//tr.tick();
    for(i=0; i<NUM_FIRES; i++)
        fire[i].tick();
    if(player.position.x > bmr.radius_of_path - 5 && bmr.finish == false)
    {
        cout << "x : " << abs(player.position.x - bmr.position.x) << endl;
        cout << "y : " << player.position.y - bmr.position.y << endl;
        cout << bmr.collided << endl << endl;

        bmr.tick();

        if(abs(player.position.x - bmr.position.x) < 1.5*player.radius && (abs(player.position.y - bmr.position.y) < 1.5*player.radius))
                bmr.collided = true;

        if (abs(player.position.x - bmr.position.x) < 1.5*player.radius && (player.position.y == 0.7 && bmr.position.y < 0))
                bmr.collided = true;
        if(bmr.collided == true && bmr.finish == false)
        {
            score -= 100;
            if(score>999)
                score = 999;
            scu = score%10;
            sct = (score/10)%100;
            sch = score%100;
            bmr.finish = true;
        }
        // cout << player.position.x << " " << p_up.position.x << endl;
        // cout << player.position.y << " " << p_up.position.y << endl;
    }
    if((player.position.y > 0.7))
    {
        for(i=0; i<NUM_COINS; i++)
        {
            if(coins[i].alive && detect_collision(i, 0))
            {
                    score+= coins[i].score;
                    if(score>999)
                        score = 999;
                    scu = score%10;
                    sct = (score/10)%100;
                    sch = score%100;
                    coins[i].alive = false;
            }

        }

    }
    for(i=0; i<NUM_FIRES; i++)
    {
        if(detect_collision(i,1) && fire[i].touched == false )
        {
            fire[i].touched = true;
            score -= 1000;
            if(score>999)
                score = 999;
            scu = score%10;
            sct = (score/10)%100;
            sch = score%100;
        }
    }


    if(p_up.active && detect_collision_bonus())
    {
        score += 100;
        if(score>999)
            score = 999;
        scu = score%10;
        sct = (score/10)%100;
        sch = score%100;
        //cout << "collided" << endl;
        p_up.active = false;
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
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    player      = Ball(0, 0.7,0.2, COLOR_GREY);
    tr          = Triangle(COLOR_YELLOW);
    bmr         = Boomerang(COLOR_BLACK);
    ground      = Ground(floorHeight + 3*player.radius, -4.0);
    p_up        = Powerup(COLOR_DARKBLUE);
    magnet      = Magnet(1);
    sc[0]       = Score(screen_center_x, -2, scu, COLOR_WHITE);
    sc[1]       = Score(screen_center_x - 1, -2, sct, COLOR_WHITE);
    sc[2]       = Score(screen_center_x - 2, -2, sch, COLOR_WHITE);
    // generate 4 random fire lines
    for(j=0; j<NUM_FIRES; j++)
    {

        if(j%2==0 || j%7 == 0) // it is a fire beam
        {
            float yfire_1      = 1.5;
            float xfire_1      = 4*j + rand()%5 + 5;
            float xfire_2      = xfire_1 + 2.5;
            float yfire_2      = yfire_1;
            fire[j]            = Fire(COLOR_FIRE, xfire_1, yfire_1, xfire_2, yfire_2);
            fire[j].beam = true;
        }
        else // it is a fire line
        {
            float yfire_1      = 1.7 + rand()%2 + 0.1;
            float xfire_1      = 4*j + rand()%5 + 5;
            float xfire_2      = xfire_1 + 2.5;
            float yfire_2      = yfire_1 + rand()%3 - 0.4;
            fire[j]            = Fire(COLOR_FIRE, xfire_1, yfire_1, xfire_2, yfire_2);
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
    int gap = 1250; // Time between departure of old magnet and arrival of new
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
        Fire f= fire[i];
        //if(player.speedVertical > 0) return false;
        if(player.position.x >= f.x1 && player.position.x <= f.x2 && player.position.y >= f.y1 && player.position.y <= f.y2+0.15)
            return true;
        return false;
    }

}


bool detect_collision_bonus()
{

    //if(player.speedVertical > 0) return false;
    //cout << player.position.x << " " << p_up.position.x << endl;
    //cout << player.position.y << " " << p_up.position.y << endl;

    if(abso(player.position.x - p_up.position.x) <= player.radius + p_up.size && abso(player.position.y - p_up.position.y) <= player.radius + p_up.size)
        return true;
    return false;
}


void reset_screen()
{
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;

    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 2000.0f);
}
