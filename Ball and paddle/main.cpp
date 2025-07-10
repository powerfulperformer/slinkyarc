#define RAYGUI_IMPLEMENTATION
#include <raylib.h>
#include "raygui.h"
#include <fstream>
int main() {
    InitWindow(800, 600, "PADDLE AND BALL");
    // Save highscore
    float rect_x = 400;
    float rect_y = 400;
    float ball_x = 450;
    float ball_y = 200;
    float ball_speed_x = 3;
    float ball_speed_y = 3;
   float paddle_speed = 6;
   int score = 0;
   int highscore;
   std::ifstream loadFile("C:/Users/Slinky_Arc/Desktop/Raylib-CPP-Starter-Template-for-VSCODE-main/highscore.txt");
if (loadFile.is_open()) {
    loadFile >> highscore;
    loadFile.close();
}
    SetTargetFPS(120);
    bool running = true;
    bool modification = false;
    while (!WindowShouldClose()) {
        if (GuiButton((Rectangle){690, 550, 100, 40}, "PAUSE")) {
            running = !running;
        }
        if (GuiButton((Rectangle){690,500,100,40},"MODIFY")){
            modification = !modification;
        }
        if (modification){
            running = false;
            GuiSlider((Rectangle){640,100,100,20},"speedX","ball",&ball_speed_x,-20.0f,20.0f);
            GuiSlider((Rectangle){640,130,100,20},"SpeedY","ball",&ball_speed_y,-20.0f,20.0f);
            GuiSlider((Rectangle){640,160,100,20},"PADDLE","paddle",&paddle_speed,0.0f,100.0f);
        }

        BeginDrawing();
        ClearBackground(WHITE);

        Rectangle ball = { ball_x, ball_y, 10, 10 };
        Rectangle paddle = { rect_x, rect_y, 100, 20 };
        
        // Game logic updates only if NOT paused
        if (running) {
            ball_x += ball_speed_x;
            ball_y += ball_speed_y;

            if (ball_x >= 800 || ball_x <= 0) ball_speed_x *= -1;
            if (ball_y >= 600 || ball_y <= 0) {ball_speed_y *= -1;}
            if (ball_y >= 600){
                score = 0;
            }

            if (IsKeyDown(KEY_D)) rect_x += paddle_speed;
            if (IsKeyDown(KEY_A)) rect_x -= paddle_speed;

            bool collision = CheckCollisionRecs(paddle, ball);
            if (collision && ball_speed_y > 0) {
                ball_speed_y *= -1;
                score++;
                if (score >  highscore) {highscore = score;}
            }
        }
        DrawText(TextFormat("SCORE: %d", score), 10, 10, 20, DARKGRAY);
        DrawText(TextFormat("HIGH SCORE: %d", highscore), 10, 35, 20, DARKBLUE);

        // Draw elements
        DrawRectangleRec(ball, BLACK);
        DrawRectangleRec(paddle, BLACK);

        if (!running) {
            DrawText("PAUSED", 350, 250, 40, RED);
        }

        EndDrawing();
    }
        std::ofstream saveFile("C:/Users/Slinky_Arc/Desktop/Raylib-CPP-Starter-Template-for-VSCODE-main/highscore.txt");
if (saveFile.is_open()) {
    saveFile << highscore;
    saveFile.close();
}
    CloseWindow();
}