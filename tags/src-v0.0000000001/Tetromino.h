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
        unsigned int** getPotentialShape();

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

        unsigned int   **mShape;
        unsigned int   **mPotentialShape;
        sPosition        mTopLeft;
        sPosition        mPotentialTopLeft;

        int mWidth;
        int mHeight;
        int mPotentialWidth;
        int mPotentialHeight;
};

#endif // TETROMINO_H
