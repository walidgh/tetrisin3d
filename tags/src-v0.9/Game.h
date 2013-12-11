#ifndef GAME_H
#define GAME_H

#include "Tetromino.h"
#include "Board.h"

class Game
{
    public:     // Functions

        Game(Tetromino *tetromino, Board *board);   // Constructor
        ~Game();                                    // Destructor

        bool CheckCollisionWithLanded();    // Checks collision with landed tetrominos
        bool CheckCollisionWithBorder();    // Checks collision with the borders
        bool CheckCollisionWhenRotated();   // Checks collision before tetromino is rotated
        bool CheckGameOver();               // Checks tetromino reached the top

        void DeleteLines(int *score);       // Remove full line on gameboard

    private:    // Variables

        Tetromino *mTetromino;      // Pointer to Tetromino object
        Board     *mBoard;          // Pointer to Board object
};

#endif // GAME_H
