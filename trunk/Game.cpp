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

bool Game::CheckCollisionWithLanded()
{
    for (int row=0; row<mTetromino->getHeight(); row++)
    {
        for (int col = 0; col<mTetromino->getWidth(); col++)
        {
            if(mTetromino->getShape()[row][col] != 0)
            {
                if(row + mTetromino->getPotentialTopLeft()->row >= mBoard->GetRow())
                {
                    //this block would be below the playing field
                    return true;
                }
                if (mBoard->GetLanded()[row + mTetromino->getPotentialTopLeft()->row][col + mTetromino->getTopLeft()->col] != 0)
                {
                    //the space is taken
                    return true;
                }
            }
         }
    }

    return false;
}

bool Game::CheckCollisionWithBorder()
{
    for (int row=0; row<mTetromino->getHeight(); row++)
    {
        for (int col = 0; col<mTetromino->getWidth(); col++)
        {
            if(mTetromino->getShape()[row][col] != 0)
            {
                if(col + mTetromino->getPotentialTopLeft()->col < 0)
                {
                    //this block would be to the left of the playing field
                    return true;
                }
                if(col + mTetromino->getPotentialTopLeft()->col >= mBoard->GetCol())
                {
                    //this block would be to the right of the playing field
                    return true;
                }
                if (mBoard->GetLanded()[row + mTetromino->getPotentialTopLeft()->row][col + mTetromino->getPotentialTopLeft()->col] != 0)
                {
                    //the space is taken
                    return true;
                }
            }
         }
    }

    return false;
}

bool Game::CheckCollisionWhenRotated()
{
    for(int row=0; row<mTetromino->getPotentialHeight(); row++)
    {
        for(int col=0; col<mTetromino->getPotentialWidth(); col++)
        {
            if(mTetromino->getPotentialShape()[row][col] != 0)
            {
                if(col + mTetromino->getTopLeft()->col < 0)
                {
                    //this block would be to the left of the playing field
                    return true;
                }
                if(col + mTetromino->getTopLeft()->col >= mBoard->GetCol())
                {
                    //this block would be to the right of the playing field
                    return true;
                }
                if(row + mTetromino->getTopLeft()->row >= mBoard->GetRow())
                {
                    //this block would be below the playing field
                    return true;
                }
                if(mBoard->GetLanded()[row + mTetromino->getTopLeft()->row][col + mTetromino->getTopLeft()->col] != 0)
                {
                    //the space is taken
                    return true;
                }
            }
        }
    }

    return false;
}

void Game::DeleteLines()
{
    for(int row=0; row<mBoard->GetRow(); row++)
    {
        bool isFilled = true;
        for(int col=0; col<mBoard->GetCol(); col++)
        {
            // Check if row is full
            if(mBoard->GetLanded()[row][col] == 0)
            {
                isFilled = false;
            }
        }

        // If row is full
        if(isFilled)
        {
            // Make all element 0
            for(int col=0; col<mBoard->GetCol(); col++)
            {
                mBoard->GetLanded()[row][col] = 0;
            }

            // Move 1 row down every line above the empted row
            for(int row2=row; row2>0; row2--)
            {
                for(int col2=0; col2<mBoard->GetCol(); col2++)
                {
                    mBoard->GetLanded()[row2][col2] = mBoard->GetLanded()[row2-1][col2];
                    mBoard->GetLanded()[row2-1][col2] = 0;
                }
            }

        }
    }
}
