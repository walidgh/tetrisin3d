#ifndef BOARD_H
#define BOARD_H

#include "Tetromino.h"

class Board
{
    public:     // functions

        Board(int col, int row);
        ~Board();

        void InitBoard();
        unsigned int** GetLanded();
        void LandShape(Tetromino *tetromino);

    private:    // variables

        int mRow;
        int mCol;
        unsigned int **mLanded;
};

#endif // BOARD_H
