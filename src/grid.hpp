#pragma once

#include <raylib.h>
#include "icons.hpp"
#include "random.hpp"
#include <iostream>

class Grid
{
    int nrows;
    int ncols;
    int cellSize;
    int cellGap;

    int* gridImgIdxs; // image indices - [nrows][ncols]

    bool* gridIsCovered; // matrix [nrows][ncols] whether that cell is covered or not

    int alreadyOpenedCell; // if one cell is already open, stores it's index, otherwise stores -1
    int secondOpenedCell; // the second cell that is opened

    // for initial pause
    bool atInitialPause;
    double InitialPauseTime;
    double INITIAL_LOAD_TIME;

    // once the game starts
    double startTime;

    // once the game ends
    double endTime;

    // for pausing
    bool isPaused;
    double pausedTime;

    int remained; // no. of cells remained to open
    int wrongPairsOpened; // no. of wrong pairs opened

    int leftPad, topPad;

public:
    Grid();
    void draw();
    void update(); // clears temp pause
    void handleClick(int x, int y);

    bool isAtInitialPause();
    double getInitialLoad(); // returns the fraction of time completed for initial load time, used to display loading bar at top

    double getTimeElapsed(); // time elapsed from startTime

    void callTempPause();
    void endTempPause();

    void randomize();
    void reset();

    int getWrongPairsOpened();
    int isGameOver();

    ~Grid();

    friend int main(); // temporary
};