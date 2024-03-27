/***********************************
 * CSC 122 Sample Raylib application.
 * A game object chases the points at the front of a queue.
 * 
 * name: Paul W. Bible
 */ 
#include "raylib.h"
#include "raymath.h"
#include "MovingObject.hpp"
#include "PointQueue.hpp"
#include <cmath>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    // These varaibles are for the screen size
    const int screenWidth = 800;
    const int screenHeight = 450;

    // Create some Custom colors
    Color depauwBlack = Color{35, 31, 32, 255};
    Color depauwGold = Color{253, 221, 6, 255};

    // create some game objects
    float x = screenWidth/2;
    float y = screenHeight/2;
    MovingObject seeker = MovingObject(x, y, depauwBlack);

    PointQueue chaseQueue;
       
    // Initialize window and set the screen title
    InitWindow(screenWidth, screenHeight, "CSC122 - Window Title Here");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // current time
    // GetTime gives the number of seconds since start of application.
    double time = GetTime();

    // Main game loop, Draw loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // ***** Processing and updates *****
        // Get the change in time since last frame.
        double lastTime = time;
        time = GetTime();
        double deltaTime = time - lastTime;
        //cout << deltaTime << endl;

        // ***** Process user input *****
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            Vector2 mouseXY = GetMousePosition();
            chaseQueue.enqueue(mouseXY);
        }

        // as long as a point is in the queue, have the seeker move toward it.
        if(!chaseQueue.isEmpty()){
            // get the front element of the queue.
            Vector2 target = chaseQueue.frontNodeData();
            // have the seeker look to the target.
            seeker.lookTo(target);
            // has seeker take a step.
            seeker.update(deltaTime);
            // when the seeker gets close, dequeue the element.
            if(Vector2Distance(seeker.getPostion(),target) < 10) {
                chaseQueue.dequeue();
            }
        }

        // ***** Draw *****
        //----------------------------------------------------------------------------------
        // ***** Draw Regular Game Scene *****
        // Call this at the end of your drawing.
        BeginDrawing();
        ClearBackground(RAYWHITE);

            // draw objects
            chaseQueue.draw();
            seeker.draw();
    
        // Call this at the end of your drawing.
        EndDrawing();
    }

    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return 0;
}