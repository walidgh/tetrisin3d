#ifndef TETROMINO_H
#define TETROMINO_H

struct sPosition
{
    int row;
    int col;
};

class Tetromino
{
    public:     // functions

        Tetromino();
        ~Tetromino();

        void NewShape();

        unsigned int** getShape();

        int getPositionCol();
        int getPositionRow();
        int getPotentionalPositionRow();

        void MoveDown();
        void MoveLeft();
        void MoveRight();

    private:    // functions

        int GetRand(int a, int b);

    private:    // variables

        unsigned int   **mShapeActual;
        unsigned int    *mShapeNext;
        sPosition        mTopLeft;
};

#endif // TETROMINO_H
