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

        sPosition* getTopLeft();
        sPosition* getPotentionalTopLeft();
        int getWidth();
        int getHeight();

        void MoveDown();
        void MoveLeft();
        void MoveRight();

    private:    // functions

        int GetRand(int a, int b);

    private:    // variables

        unsigned int   **mShapeActual;
        unsigned int    *mShapeNext;
        sPosition        mTopLeft;
        sPosition        mPotentionalTopLeft;

        int mWidth;
        int mHeight;
};

#endif // TETROMINO_H
