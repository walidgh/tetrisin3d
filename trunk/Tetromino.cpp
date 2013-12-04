#include "Tetromino.h"

Tetromino::Tetromino()
{
    NewShape();
}

Tetromino::~Tetromino()
{
    delete mShapeActual;
}

void Tetromino::NewShape()
{
    unsigned int temp[4][4] =
        { {1, 1, 0, 0},
          {1, 1, 0, 0},
          {0, 0, 0, 0},
          {0, 0, 0, 0} };

    mShapeActual = new unsigned int*[4];
    for(int i=0; i<4; i++) mShapeActual[i] = new unsigned int[4];

    for(int row=0; row<4; row++)
    {
        for(int col=0; col<4; col++)
        {
            mShapeActual[row][col] = temp[row][col];
        }
    }

    mTopLeft.row = 0;
    mTopLeft.col = 4;

}

unsigned int** Tetromino::getShape()
{
    return mShapeActual;
}

sPosition* Tetromino::getPosition()
{
    return &mTopLeft;
}
