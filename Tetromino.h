#ifndef TETROMINO_H
#define TETROMINO_H

struct sPosition
{
    unsigned int row;
    unsigned int col;
};

class Tetromino
{
    public:     // functions

        Tetromino();
        ~Tetromino();

        void NewShape();

        unsigned int** getShape();
        sPosition*    getPosition();

    public:     // variables



    private:    // variables

        unsigned int   **mShapeActual;
        unsigned int    *mShapeNext;
        sPosition        mTopLeft;
};

#endif // TETROMINO_H
