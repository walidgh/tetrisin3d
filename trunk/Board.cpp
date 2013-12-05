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
    mLanded = new unsigned int*[mHeight];
    for(int i=0; i<mHeight; i++) mLanded[i] = new unsigned int[mWidth];

    for(int row=0; row<mHeight; row++)
    {
        for(int col=0; col<mWidth; col++)
        {
            mLanded[row][col] = 0;
        }
    }

//    for(int col=0; col<mCol; col++)
//    {
//        mLanded[9][col] = 1;
//    }
}

unsigned int** Board::GetLanded()
{
    return mLanded;
}

void Board::LandShape(Tetromino *tetromino)
{
    for (int row=0; row<tetromino->getHeight(); row++)
    {
        for (int col=0; col<tetromino->getWidth(); col++)
        {
            if (tetromino->getShape()[row][col] != 0)
            {
                mLanded[row + tetromino->getTopLeft()->row][col + tetromino->getTopLeft()->col] = tetromino->getShape()[row][col];
            }
        }
    }
}

int Board::GetHeight()
{
    return mHeight;
}

int Board::GetWidth()
{
    return mWidth;
}
