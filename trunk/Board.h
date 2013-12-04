#ifndef BOARD_H
#define BOARD_H


class Board
{
    public:     // functions

        Board();
        ~Board();

    private:    // variables

        unsigned int mLanded[16][10];
};

#endif // BOARD_H
