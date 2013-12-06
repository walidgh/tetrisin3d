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

        int** getShape();
        int** getPotentialShape();

        sPosition* getTopLeft();
        sPosition* getPotentialTopLeft();

        int getWidth();
        int getHeight();
        int getPotentialWidth();
        int getPotentialHeight();

        void RotatePotential();

        void Rotate();
        void Move();


    private:    // functions

        int GetRand(int a, int b);

    private:    // variables

        int            **mShape;
        int            **mPotentialShape;
        sPosition        mTopLeft;
        sPosition        mPotentialTopLeft;

        int mWidth;
        int mHeight;
        int mPotentialWidth;
        int mPotentialHeight;

        int mColor;
};

#endif // TETROMINO_H
