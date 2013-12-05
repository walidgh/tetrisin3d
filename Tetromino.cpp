#include "Tetromino.h"

#include <stdlib.h>
#include <time.h>

Tetromino::Tetromino()
{
    // Init random numbers
    srand ((unsigned int) time(NULL));

    // Allocate memory
    mShapeActual = new unsigned int*[4];
        for(int i=0; i<4; i++) mShapeActual[i] = new unsigned int[4];

    // Create new shape
    NewShape();
}

Tetromino::~Tetromino()
{
    for(int i=0; i<4; i++)
        delete [] mShapeActual[i];
    delete [] mShapeActual;
}

/**
    Set random shape
*/
void Tetromino::NewShape()
{
    int rand = GetRand(0, 2);

    if(rand == 0)       // O
    {
        mShapeActual = 0;
        mWidth = 2;
        mHeight = 2;

        unsigned int temp[2][2] = {{1, 1}, {1, 1}};

        mShapeActual = new unsigned int*[mHeight];
        for(int i=0; i<mHeight; i++) mShapeActual[i] = new unsigned int[mWidth];

        for(int row=0; row<mHeight; row++)
        {
            for(int col=0; col<mWidth; col++)
            {
                mShapeActual[row][col] = temp[row][col];
            }
        }
    }
    else if(rand == 1)       // I
    {
        mShapeActual = 0;
        mWidth = 1;
        mHeight = 4;

        mShapeActual = new unsigned int*[mHeight];
        for(int i=0; i<mHeight; i++) mShapeActual[i] = new unsigned int[mWidth];

        unsigned int temp[4][1] = {{1}, {1}, {1}, {1}};

        for(int row=0; row<mHeight; row++)
        {
            for(int col=0; col<mWidth; col++)
            {
                mShapeActual[row][col] = temp[row][col];
            }
        }
    }
    else if(rand == 2)       // L
    {
        mShapeActual = 0;
        mWidth = 2;
        mHeight = 3;

        mShapeActual = new unsigned int*[mHeight];
        for(int i=0; i<mHeight; i++) mShapeActual[i] = new unsigned int[mWidth];

        unsigned int temp[3][2] = {{1, 0}, {1, 0}, {1, 1}};

        for(int row=0; row<mHeight; row++)
        {
            for(int col=0; col<mWidth; col++)
            {
                mShapeActual[row][col] = temp[row][col];
            }
        }
    }

    // Set shape start position
    mTopLeft.row = 0;
    mTopLeft.col = 4;

    mPotentialTopLeft.row = 0;
    mPotentialTopLeft.col = 4;

}

unsigned int** Tetromino::getShape()
{
    return mShapeActual;
}

unsigned int** Tetromino::getPotentialShape()
{
    return mPotentialShape;
}

sPosition* Tetromino::getTopLeft()
{
    return &mTopLeft;
}

sPosition* Tetromino::getPotentialTopLeft()
{
    return &mPotentialTopLeft;
}

int Tetromino::GetRand(int a, int b)
{
	return rand () % (b - a + 1) + a;
}

int Tetromino::getWidth()
{
    return mWidth;
}

int Tetromino::getHeight()
{
    return mHeight;
}

int Tetromino::getPotentialWidth()
{
    return mPotentialWidth;
}

int Tetromino::getPotentialHeight()
{
    return mPotentialHeight;
}

void Tetromino::RotatePotential()
{
    mPotentialWidth  = mHeight;
    mPotentialHeight = mWidth;

    mPotentialShape = 0;
    mPotentialShape = new unsigned int*[mPotentialHeight];
    for(int i=0; i<mPotentialHeight; i++) mPotentialShape[i] = new unsigned int[mPotentialWidth];

    int r = 0;
    for(int row=mHeight-1; row>=0; row--)
    {
        for(int col=0; col<mWidth; col++)
        {
            mPotentialShape[col][r] = mShapeActual[row][col];
        }
        r++;
    }

}

void Tetromino::Rotate()
{
    mHeight = mPotentialHeight;
    mWidth  = mPotentialWidth;
    mShapeActual = mPotentialShape;
}

void Tetromino::Move()
{
    mTopLeft = mPotentialTopLeft;
}
