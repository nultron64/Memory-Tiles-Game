#include "grid.hpp"

Grid::Grid()
{
    nrows = 5;
    ncols = 8;
    cellSize = 64;
    cellGap = 16;

    gridImgIdxs = new int[nrows*ncols];
    gridIsCovered = new bool[nrows*ncols];
    reset();

    INITIAL_LOAD_TIME = 5;
    
    leftPad=88;
    topPad=80;
}

void Grid::update()
{
    if (atInitialPause) {
        if (GetTime()-InitialPauseTime >= INITIAL_LOAD_TIME) {
            atInitialPause = false;
            int ncells = nrows*ncols;
            for(int i=0; i<ncells; i++) {
                gridIsCovered[i] = true;
            }
            startTime = GetTime();
        }
    }
    if (isPaused) {
        if ((GetTime()-pausedTime) >= 1.5) {
            endTempPause();
        }
    }
}

void Grid::draw()
{
    for(int i=0; i<nrows; i++) {
        for(int j=0; j<ncols; j++) {
            // Rectangle
            // DrawRectangleRounded()
            DrawRectangle(leftPad+j*(cellSize+cellGap), topPad+i*(cellSize+cellGap), cellSize, cellSize, WHITE);
            DrawTexture(icons[gridImgIdxs[i*ncols + j]], leftPad+j*(cellSize+cellGap), topPad+i*(cellSize+cellGap), WHITE);
            
            if (gridIsCovered[i*ncols + j]) {
                DrawRectangle(leftPad+j*(cellSize+cellGap), topPad+i*(cellSize+cellGap), cellSize, cellSize, WHITE);
            }
        }
    }
}

void Grid::handleClick(int x, int y)
{
    if (atInitialPause) return;
    if (isPaused) endTempPause();

    x -= leftPad;
    y -= topPad;

    if (x<0 || y<0) return;

    int totalCellSize = cellSize+cellGap;

    int xq = x/(totalCellSize); // x quotient
    int yq = y/(totalCellSize);
    if (xq>=8 || yq>=5) return;

    int xr = x - xq*totalCellSize; // x remainder
    int yr = y - yq*totalCellSize;

    if (xr<=cellSize && yr<=cellSize) {
        int currCell = yq*ncols+xq;
        // if clicked on previous correctly opened cells
        if (gridIsCovered[currCell]==false) {
            // if clicked on already opened cell - close it and increment wrongPairsOpened
            if (alreadyOpenedCell==currCell) {
                wrongPairsOpened++;
                gridIsCovered[alreadyOpenedCell] = true;
                alreadyOpenedCell = -1;
            }
            return;
        }

        if (alreadyOpenedCell==-1) {
            gridIsCovered[currCell] = false;
            alreadyOpenedCell = currCell;
            return;
        }
        else {
            gridIsCovered[currCell] = false;
            
            // When two opeened cells match - success case
            if (gridImgIdxs[currCell]==gridImgIdxs[alreadyOpenedCell]){
                alreadyOpenedCell = -1;
                secondOpenedCell = -1;
                remained -= 2;
                if (remained == 0) {
                    std::cout << wrongPairsOpened << std::endl;
                    std::cout << "Game Over\n" << std::endl;
                    endTime = GetTime();
                }
            }
            else { // two opened cells don't match - failure case
                secondOpenedCell = currCell;
                wrongPairsOpened++;
                callTempPause();
            }
        }
    }
}

bool Grid::isAtInitialPause()
{
    return atInitialPause;
}

double Grid::getInitialLoad()
{
    if (atInitialPause) {
        return (GetTime()-InitialPauseTime)/INITIAL_LOAD_TIME;
    }
    return 1;
}

double Grid::getTimeElapsed()
{
    return GetTime()-startTime;
}

void Grid::callTempPause()
{
    isPaused = true;
    pausedTime = GetTime();
}

void Grid::endTempPause()
{
    if (isPaused) {
        if(alreadyOpenedCell!=-1) gridIsCovered[alreadyOpenedCell] = true;
        if(secondOpenedCell!=-1) gridIsCovered[secondOpenedCell] = true;
        alreadyOpenedCell = -1;
        secondOpenedCell = -1;

        isPaused = false;
    }
}

void Grid::randomize()
{
    RandomSeq iconSeq(32);
    RandomSeq placesSeq(40);
    for(int i=0; i<20; i++) {
        int icon = iconSeq.next()-1;
        // std::cout << icon << std::endl;
        int place = placesSeq.next()-1;
        gridImgIdxs[place] = icon;
        place = placesSeq.next()-1;
        gridImgIdxs[place] = icon;
    }
}

void Grid::reset()
{
    randomize();
    int ncells = nrows*ncols;
    for(int i=0; i<ncells; i++) {
        gridIsCovered[i] = false;
    }
    
    alreadyOpenedCell = -1;
    secondOpenedCell = -1;
    
    isPaused = false;

    remained = nrows*ncols;
    wrongPairsOpened = 0;
    
    InitialPauseTime = GetTime();
    atInitialPause = true;
}

int Grid::getWrongPairsOpened()
{
    return wrongPairsOpened;
}

int Grid::isGameOver()
{
    return remained<=0;
}

Grid::~Grid()
{
    delete[] gridImgIdxs;
    delete[] gridIsCovered;
}