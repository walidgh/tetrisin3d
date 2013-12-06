#ifndef BOARD_H
#define BOARD_H

#include "Tetromino.h"

class Board
{
    public:     // functions

        Board(int width, int height);
        ~Board();

        void InitBoard();
        int** GetLanded();
        void LandShape(Tetromino *tetromino);
        int GetHeight();
        int GetWidth();

    private:    // variables

        int mWidth;
        int mHeight;
        int **mLanded;
};

#endif // BOARD_H
