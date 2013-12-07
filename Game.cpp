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
    for (int row=0; row<mTetromino->GetHeight(); row++)
    {
        for (int col = 0; col<mTetromino->GetWidth(); col++)
        {
            if(mTetromino->GetShape()[row][col] != 0)
            {
                if(row + mTetromino->GetPotentialTopLeft()->row >= mBoard->GetHeight())
                {
                    //this block would be below the playing field
                    return true;
                }
                if (mBoard->GetLanded()[row + mTetromino->GetPotentialTopLeft()->row][col + mTetromino->GetTopLeft()->col] != 0)
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
    for (int row=0; row<mTetromino->GetHeight(); row++)
    {
        for (int col = 0; col<mTetromino->GetWidth(); col++)
        {
            if(mTetromino->GetShape()[row][col] != 0)
            {
                if(col + mTetromino->GetPotentialTopLeft()->col < 0)
                {
                    //this block would be to the left of the playing field
                    return true;
                }
                if(col + mTetromino->GetPotentialTopLeft()->col >= mBoard->GetWidth())
                {
                    //this block would be to the right of the playing field
                    return true;
                }
                if (mBoard->GetLanded()[row + mTetromino->GetPotentialTopLeft()->row][col + mTetromino->GetPotentialTopLeft()->col] != 0)
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
    for(int row=0; row<mTetromino->GetPotentialHeight(); row++)
    {
        for(int col=0; col<mTetromino->GetPotentialWidth(); col++)
        {
            if(mTetromino->GetPotentialShape()[row][col] != 0)
            {
                if(col + mTetromino->GetTopLeft()->col < 0)
                {
                    //this block would be to the left of the playing field
                    return true;
                }
                if(col + mTetromino->GetTopLeft()->col >= mBoard->GetWidth())
                {
                    //this block would be to the right of the playing field
                    return true;
                }
                if(row + mTetromino->GetTopLeft()->row >= mBoard->GetHeight())
                {
                    //this block would be below the playing field
                    return true;
                }
                if(mBoard->GetLanded()[row + mTetromino->GetTopLeft()->row][col + mTetromino->GetTopLeft()->col] != 0)
                {
                    //the space is taken
                    return true;
                }
            }
        }
    }

    return false;
}

//TODO make another game over check
//     which checks is there any collsision between landed and new shape
bool Game::CheckGameOver()
{
    for(int col=0; col<mBoard->GetWidth(); col++)
    {
        if(mBoard->GetLanded()[2][col] != 0)
        {
            return true;
        }
    }

    return false;
}

void Game::DeleteLines(int *score)
{
    for(int row=0; row<mBoard->GetHeight(); row++)
    {
        bool isFilled = true;
        for(int col=0; col<mBoard->GetWidth(); col++)
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
            // Increment game score with 1
            *score += 1;

            // Make all element 0
            for(int col=0; col<mBoard->GetWidth(); col++)
            {
                mBoard->GetLanded()[row][col] = 0;
            }

            // Move 1 row down every line above the empted row
            for(int row2=row; row2>0; row2--)
            {
                for(int col2=0; col2<mBoard->GetWidth(); col2++)
                {
                    mBoard->GetLanded()[row2][col2] = mBoard->GetLanded()[row2-1][col2];
                    mBoard->GetLanded()[row2-1][col2] = 0;
                }
            }

        }
    }
}
