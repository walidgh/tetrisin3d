#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL/SDL.h>
#include <GL/glew.h>

#include "Tetromino.h"
#include "Board.h"

class Graphics
{
    public:     // functions
        Graphics(Tetromino *tetromino, Board *board);
        ~Graphics();

        bool InitGraphics(int scale, int row, int col);

        void Rendering();

    private:    // variables

        Tetromino *mTetromino;
        Board     *mBoard;

        // Display settings
        int mScreenWidth;
        int mScreenHeight;
        int mScale;
        int mRow;
        int mCol;

        // SDL stuff
        SDL_Surface *mScreen;

        // OpenGL stuff
        GLuint mShaderProgramId;

        GLuint  mVertexBufferId;
        GLuint  mColorBufferId;
        GLuint  mMVPuniformLocation;

    private:    // functions

        bool InitSDL();
        bool InitOpenGL();

        void DrawSquare(float transX, float transY);

        void UpdateScreen();
        void SwapFrameBuffer();
};

    static const GLfloat Vertices[] =
    {
          0.0f, 0.0f, 0.0f,
          0.0f, 1.0f, 0.0f,
          1.0f, 1.0f, 0.0f,
          0.0f, 0.0f, 0.0f,
          1.0f, 1.0f, 0.0f,
          1.0f, 0.0f, 0.0f
    };

    static const GLfloat Colors[] =
    {
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f
    };

#endif // GRAPHICS_H
