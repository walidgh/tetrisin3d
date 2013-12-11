#include "Tetromino.h"

#include <stdlib.h>
#include <time.h>

Tetromino::Tetromino()
{
    // Init random numbers
    srand ((unsigned int) time(NULL));

    // Allocate memory
    mShape = new int*[4];
        for(int i=0; i<4; i++) mShape[i] = new int[4];

    // Create new shape
    NewShape();
}

Tetromino::~Tetromino()
{
    for(int i=0; i<4; i++)
        delete [] mShape[i];
    delete [] mShape;
}

/**
    Set random shape
*/
void Tetromino::NewShape()
{
    int rand = GetRand(0, 6);

    mColor = GetRand(1, 7);

    if(rand == 0)       // O
    {
        mShape = 0;
        mWidth = 2;
        mHeight = 2;

        int temp[2][2] = {{mColor, mColor}, {mColor, mColor}};

        mShape = new int*[mHeight];
        for(int i=0; i<mHeight; i++) mShape[i] = new int[mWidth];

        for(int row=0; row<mHeight; row++)
        {
            for(int col=0; col<mWidth; col++)
            {
                mShape[row][col] = temp[row][col];
            }
        }
    }
    else if(rand == 1)       // I
    {
        mShape = 0;
        mWidth = 1;
        mHeight = 4;

        mShape = new int*[mHeight];
        for(int i=0; i<mHeight; i++) mShape[i] = new int[mWidth];

        int temp[4][1] = {{mColor}, {mColor}, {mColor}, {mColor}};

        for(int row=0; row<mHeight; row++)
        {
            for(int col=0; col<mWidth; col++)
            {
                mShape[row][col] = temp[row][col];
            }
        }
    }
    else if(rand == 2)       // L
    {
        mShape = 0;
        mWidth = 2;
        mHeight = 3;

        mShape = new int*[mHeight];
        for(int i=0; i<mHeight; i++) mShape[i] = new int[mWidth];

        int temp[3][2] = {{mColor, 0}, {mColor, 0}, {mColor, mColor}};

        for(int row=0; row<mHeight; row++)
        {
            for(int col=0; col<mWidth; col++)
            {
                mShape[row][col] = temp[row][col];
            }
        }
    }
    else if(rand == 3)       // J
    {
        mShape = 0;
        mWidth = 2;
        mHeight = 3;

        mShape = new int*[mHeight];
        for(int i=0; i<mHeight; i++) mShape[i] = new int[mWidth];

        int temp[3][2] = {{0, mColor}, {0, mColor}, {mColor, mColor}};

        for(int row=0; row<mHeight; row++)
        {
            for(int col=0; col<mWidth; col++)
            {
                mShape[row][col] = temp[row][col];
            }
        }
    }
    else if(rand == 4)       // S
    {
        mShape = 0;
        mWidth = 3;
        mHeight = 2;

        mShape = new int*[mHeight];
        for(int i=0; i<mHeight; i++) mShape[i] = new int[mWidth];

        int temp[2][3] = {{0, mColor, mColor}, {mColor, mColor, 0}};

        for(int row=0; row<mHeight; row++)
        {
            for(int col=0; col<mWidth; col++)
            {
                mShape[row][col] = temp[row][col];
            }
        }
    }
    else if(rand == 5)       // T
    {
        mShape = 0;
        mWidth = 3;
        mHeight = 2;

        mShape = new int*[mHeight];
        for(int i=0; i<mHeight; i++) mShape[i] = new int[mWidth];

        int temp[2][3] = {{0, mColor, 0}, {mColor, mColor, mColor}};

        for(int row=0; row<mHeight; row++)
        {
            for(int col=0; col<mWidth; col++)
            {
                mShape[row][col] = temp[row][col];
            }
        }
    }
    else if(rand == 6)       // Z
    {
        mShape = 0;
        mWidth = 3;
        mHeight = 2;

        mShape = new int*[mHeight];
        for(int i=0; i<mHeight; i++) mShape[i] = new int[mWidth];

        int temp[2][3] = {{mColor, mColor, 0}, {0, mColor, mColor}};

        for(int row=0; row<mHeight; row++)
        {
            for(int col=0; col<mWidth; col++)
            {
                mShape[row][col] = temp[row][col];
            }
        }
    }
    // Set shape start position
    mTopLeft.row = 0;
    mTopLeft.col = 4;

    mPotentialTopLeft.row = 0;
    mPotentialTopLeft.col = 4;

}

int** Tetromino::GetShape()
{
    return mShape;
}

int** Tetromino::GetPotentialShape()
{
    return mPotentialShape;
}

sPosition* Tetromino::GetTopLeft()
{
    return &mTopLeft;
}

sPosition* Tetromino::GetPotentialTopLeft()
{
    return &mPotentialTopLeft;
}

int Tetromino::GetWidth()
{
    return mWidth;
}

int Tetromino::GetHeight()
{
    return mHeight;
}

int Tetromino::GetPotentialWidth()
{
    return mPotentialWidth;
}

int Tetromino::GetPotentialHeight()
{
    return mPotentialHeight;
}

void Tetromino::RotatePotential()
{
    mPotentialWidth  = mHeight;
    mPotentialHeight = mWidth;

    mPotentialShape = 0;
    mPotentialShape = new int*[mPotentialHeight];
    for(int i=0; i<mPotentialHeight; i++) mPotentialShape[i] = new int[mPotentialWidth];

    int r = 0;
    for(int row=mHeight-1; row>=0; row--)
    {
        for(int col=0; col<mWidth; col++)
        {
            mPotentialShape[col][r] = mShape[row][col];
        }
        r++;
    }

}

void Tetromino::Rotate()
{
    mHeight = mPotentialHeight;
    mWidth  = mPotentialWidth;
    mShape = mPotentialShape;
}

void Tetromino::Move()
{
    mTopLeft = mPotentialTopLeft;
}

int Tetromino::GetRand(int a, int b)
{
	return rand () % (b - a + 1) + a;
}
