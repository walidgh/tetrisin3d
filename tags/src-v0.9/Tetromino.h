#ifndef TETROMINO_H
#define TETROMINO_H

struct sPosition
{
    int row;
    int col;
};

class Tetromino
{
    public:     // Functions

        Tetromino();    // Constructor
        ~Tetromino();   // Destructor

        void NewShape();                    // Creates random new shape

        int** GetShape();                   // Gets shape matrix
        int** GetPotentialShape();          // Gets rotated shape

        sPosition* GetTopLeft();            // Gets shape position
        sPosition* GetPotentialTopLeft();   // Gets shape next position

        int GetWidth();             // Gets shape width
        int GetHeight();            // Gets shape height
        int GetPotentialWidth();    // Gets rotated shape width
        int GetPotentialHeight();   // Gets rotated shape height

        void RotatePotential();     // Creates rotated shape

        void Rotate();  // Rotate the actual shape
        void Move();    // Move the actual shape


    private:    // Functions

        int GetRand(int a, int b);      // Gets random number between two number

    private:    // Variables

        int            **mShape;                // Shape matrix
        int            **mPotentialShape;       // Rotated shape matrix
        sPosition        mTopLeft;              // Shape position
        sPosition        mPotentialTopLeft;     // Shape next position

        int mWidth;                 // Shape width
        int mHeight;                // Shape height
        int mPotentialWidth;        // Rotated shape width
        int mPotentialHeight;       // Rotated shape height

        int mColor;     // Tetromino color serial number
};

#endif // TETROMINO_H
