#include <raylib.h>
#include "grid.hpp"

#include <iostream>

int main()
{
    Color darkGreen = Color{20, 160, 133, 255};
    Color LoadingColor = Color{200, 200, 200, 230};

    // String buffers
    char strBuff1[100];
    char strBuff2[100];
    // -----------------

    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Memory Game");
    SetTargetFPS(60);
    std::cout << "hello" << std::endl;
    if (InitializeIcons()==-1){
        std::cout << "Can't load images\n";
        CloseWindow();
    };

    Font zektonFont = LoadFont("fonts/zekton_rg.ttf");
    Font bloodyCreepyFont = LoadFontEx("fonts/CreepyBloodyRegular-pgRw1.ttf", 128, 0, 128);
    Font robotoFont = LoadFontEx("fonts/Roboto-Regular.ttf", 60, 0, 256);
    // Loadfon
    
    Grid grid;
    // grid.remained = 0;
    while (!WindowShouldClose())
    {

        grid.update();
        if (grid.isGameOver()) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || GetKeyPressed()) {
                grid.reset();
            }
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            int x=GetMouseX(), y=GetMouseY();
            if (640<=x && x<=760 && 500<=y && y<=540) {
                grid.reset();
            }
            grid.handleClick(x, y);
        }

        if (IsKeyPressed(KEY_NINE)) {
            int ncells = grid.ncols*grid.nrows;
            for(int i=0; i<ncells; i++) {
                grid.gridIsCovered[i] = !grid.gridIsCovered[i];
            }
        }

        if (IsKeyPressed(KEY_R)) {
            grid.reset();
        }

        BeginDrawing(); // Begin drawing ----------

        ClearBackground(darkGreen);

        if (grid.isAtInitialPause()) {
            DrawRectangle(0, 0, (int)screenWidth*grid.getInitialLoad(), 20, LoadingColor);
        }
        if(grid.isGameOver() == false) {
            grid.draw();
            
            // drawing time elapsed
            if (!grid.isAtInitialPause()) {
                sprintf(strBuff1, "%.1lf", grid.getTimeElapsed());
                DrawText(strBuff1, 20, 550, 40, WHITE);
            }

            // drawing no. of wrong pairs
            sprintf(strBuff2, "Wrong Pairs: %02d", grid.getWrongPairsOpened());
            // DrawText(strBuff2, 450, 520, 40, WHITE);
            DrawTextEx(zektonFont, strBuff2, Vector2{550, 560}, 30, 1, WHITE);

            // drawing reset button - 640, 500, 120, 40
            Rectangle rect{640, 500, 120, 40};
            Color color{255, 255, 255, 240};
            DrawRectangleRounded(rect, 0.2, 0, color);
            sprintf(strBuff1, "Reset");
            Color grey{150,150,200,255};
            DrawText(strBuff1, 658, 506, 30, grey);
        }
        else {
            // Drawing WELL DONE
            sprintf(strBuff1, "WELL DONE");
            DrawTextEx(bloodyCreepyFont, strBuff1, Vector2{120, 100}, 128, 1.3, WHITE);

            // Drawing Time Elapsed
            sprintf(strBuff1, "Time: %.1lfs", grid.endTime - grid.startTime);
            Vector2 size = MeasureTextEx(robotoFont, strBuff1, 60, 1);
            
            DrawTextEx(robotoFont, strBuff1, Vector2{screenWidth/2-size.x/2, 340}, 60, 1, WHITE);

            // Drawing Wrong Pairs
            sprintf(strBuff1, "Wrong Pairs: %d", grid.getWrongPairsOpened());
            size = MeasureTextEx(robotoFont, strBuff1, 60, 1);
            DrawTextEx(robotoFont, strBuff1 ,Vector2{screenWidth/2-size.x/2, 420}, 60, 1, WHITE);

            // Drawing "click anywhere to restart"
            sprintf(strBuff1, "Click anywhere to restart");
            size = MeasureTextEx(robotoFont, strBuff1, 30, 1);
            DrawTextEx(robotoFont, strBuff1, Vector2{screenWidth/2-size.x/2, 550}, 30, 1, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}