#ifndef GAME_H
#define GAME_H

#include "Tetromino.h"
#include "Board.h"

class Game
{
    public:     // functions

        Game(Tetromino *tetromino, Board *board);
        ~Game();

        bool CheckCollision();

    private:    // variables

        Tetromino *mTetromino;
        Board     *mBoard;
};

#endif // GAME_H
