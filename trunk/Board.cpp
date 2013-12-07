#include "Board.h"

Board::Board(int width, int height)
{
    mWidth = width;
    mHeight = height;
}

Board::~Board()
{
    for(int i=0; i<mHeight; i++)
        delete [] mLanded[i];
    delete [] mLanded;
}


void Board::InitBoard()
{
    mLanded = new int*[mHeight];
    for(int i=0; i<mHeight; i++) mLanded[i] = new int[mWidth];

    for(int row=0; row<mHeight; row++)
    {
        for(int col=0; col<mWidth; col++)
        {
            mLanded[row][col] = 0;
        }
    }
}

int** Board::GetLanded()
{
    return mLanded;
}

int Board::GetHeight()
{
    return mHeight;
}

int Board::GetWidth()
{
    return mWidth;
}

void Board::LandShape(Tetromino *tetromino)
{
    for (int row=0; row<tetromino->GetHeight(); row++)
    {
        for (int col=0; col<tetromino->GetWidth(); col++)
        {
            if (tetromino->GetShape()[row][col] != 0)
            {
                mLanded[row + tetromino->GetTopLeft()->row][col + tetromino->GetTopLeft()->col] = tetromino->GetShape()[row][col];
            }
        }
    }
}
