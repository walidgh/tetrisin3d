#include "Board.h"

Board::Board()
{
    // Init board
    for(unsigned int row=0; row<16; row++)
    {
        for(unsigned int col=0; col<10; col++)
        {
            mLanded[row][col] = 0;
        }
    }


}

Board::~Board()
{
    //dtor
}
