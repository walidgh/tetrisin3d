#include "Game.h"

Game::Game(Tetromino *tetromino, Board *board)
{
    mTetromino  = tetromino;
    mBoard      = board;
}

Game::~Game()
{
    //dtor
}

bool Game::CheckCollision()
{
    for (int row=0; row<4; row++)
    {
        for (int col = 0; col<4; col++) {
            if(mTetromino->getShape()[row][col] != 0)
            {
                if (mBoard->GetLanded()[row + mTetromino->getPotentionalPositionRow()][col + mTetromino->getPositionCol()] != 0)
                {
                    return true;
                }
            }
         }
    }

    return false;
}
