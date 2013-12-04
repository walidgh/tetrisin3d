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
    for (int row=0; row<mTetromino->getHeight(); row++)
    {
        for (int col = 0; col<mTetromino->getWidth(); col++)
        {
            if(mTetromino->getShape()[row][col] != 0)
            {
                if(row + mTetromino->getPotentionalTopLeft()->row >= mBoard->GetRow())
                {
                    return true;
                }
                if (mBoard->GetLanded()[row + mTetromino->getPotentionalTopLeft()->row][col + mTetromino->getTopLeft()->col] != 0)
                {
                    return true;
                }
            }
         }
    }

    return false;
}
