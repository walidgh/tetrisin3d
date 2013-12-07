#ifndef BOARD_H
#define BOARD_H

#include "Tetromino.h"

class Board
{
    public:     // Functions

        Board(int width, int height);       // Constructor
        ~Board();                           // Destructor

        void  InitBoard();      // Initializes the gameboard
        int** GetLanded();      // Get the gameboard matrix
        int   GetHeight();      // Get gameboard height
        int   GetWidth();       // Get gameboard width

        void  LandShape(Tetromino *tetromino);      // Place tetromino on the gameboard

    private:    // Variables

        int   mWidth;       // Gameboard width
        int   mHeight;      // Gameboard height
        int **mLanded;      // Gameboard matrix
};

#endif // BOARD_H
