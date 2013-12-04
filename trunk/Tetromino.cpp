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
        /**
            Shapes [shape type][row][col]
            Types:
                square
                T
                I
                L
                S
        */
        unsigned int Shapes[5][4][4] = {
            { {1, 1, 0, 0},
              {1, 1, 0, 0},
              {0, 0, 0, 0},
              {0, 0, 0, 0} },
            { {0, 1, 0, 0},
              {1, 1, 1, 0},
              {0, 0, 0, 0},
              {0, 0, 0, 0} },
            { {1, 0, 0, 0},
              {1, 0, 0, 0},
              {1, 0, 0, 0},
              {1, 0, 0, 0} },
            { {1, 0, 0, 0},
              {1, 0, 0, 0},
              {1, 0, 0, 0},
              {1, 1, 0, 0} },
            { {0, 1, 1, 0},
              {1, 1, 0, 0},
              {0, 0, 0, 0},
              {0, 0, 0, 0} }
        };

    int rand = GetRand(0, 4);

    for(int row=0; row<4; row++)
    {
        for(int col=0; col<4; col++)
        {
            mShapeActual[row][col] = Shapes[rand][row][col];
        }
    }

    // Set shape start position
    mTopLeft.row = 0;
    mTopLeft.col = 4;

}

unsigned int** Tetromino::getShape()
{
    return mShapeActual;
}

int Tetromino::getPositionCol()
{
    return mTopLeft.col;
}

int Tetromino::getPositionRow()
{
    return mTopLeft.row;
}

int Tetromino::getPotentionalPositionRow()
{
    return mTopLeft.row + 1;
}

void Tetromino::MoveDown()
{
    mTopLeft.row += 1;
}

void Tetromino::MoveLeft()
{
    mTopLeft.col -= 1;
}

void Tetromino::MoveRight()
{
    mTopLeft.col += 1;
}

int Tetromino::GetRand(int a, int b)
{
	return rand () % (b - a + 1) + a;
}
