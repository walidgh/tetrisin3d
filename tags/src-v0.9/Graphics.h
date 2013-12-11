#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL/SDL.h>
#include <GL/glew.h>

#include "Tetromino.h"
#include "Board.h"

class Graphics
{
    public:     // Functions

        Graphics(Tetromino *tetromino, Board *board);   // Constructor
        ~Graphics();                                    // Destructor

        bool InitGraphics(int scale, int row, int col); // Initializes core graphic and display settings

        void Rendering();                               // Renders the scene

        void SetWindowTitle(int score);                 // Sets window title for game over
        void SetWindowTitle(int score, int gameSpeed);  // Sets window title with score and game speed
        void SetWindowTitle(const char *title);         // Sets window title with given string

    private:    // Variables

        Tetromino *mTetromino;      // Pointer to Tetromino object
        Board     *mBoard;          // Pointer to Board object

        // Display settings
        int mScreenWidth;       // Screen width
        int mScreenHeight;      // Screen height
        int mRow;               // Number of rows
        int mCol;               // Number of columns
        int mScale;             // Tetromino base block size

        // SDL stuff
        SDL_Surface *mScreen;   // SDL screen

        // OpenGL stuff
        GLuint mShaderProgramId;        // OpenGL shader program id

        GLuint  mVertexBufferId;        // Vertex buffer id
        GLuint  mColorBufferId;         // Color buffer id
        GLuint  mMVPuniformLocation;    // MVP matrix uniform location id

    private:    // Functions

        bool InitSDL();         // Initializes SDL
        bool InitOpenGL();      // Initializes OpenGL and GLEW

        void DrawSquare2D(float transX, float transY, int color);     // Draw 2d scquare on the given coordinates

        void UpdateScreen();        // Clears the color and depth buffers
        void SwapFrameBuffer();     // Swap the frame buffer
};

    // Tetromino base block vertices
    static const GLfloat Vertices[] =
    {
          0.05f, 0.05f, 0.0f,
          0.05f, 0.95f, 0.0f,
          0.95f, 0.95f, 0.0f,
          0.05f, 0.05f, 0.0f,
          0.95f, 0.95f, 0.0f,
          0.95f, 0.05f, 0.0f
    };

    // Colors for tetrominos
    static const GLfloat Colors[8][18] =
    {
        {
            0.0f, 0.0f, 0.3f,
            0.0f, 0.0f, 0.3f,
            0.0f, 0.0f, 0.3f,
            0.0f, 0.0f, 0.3f,
            0.0f, 0.0f, 0.3f,
            0.0f, 0.0f, 0.3f
        },

        {
            0.525f, 0.0f, 0.62f,
            0.525f, 0.0f, 0.62f,
            0.525f, 0.0f, 0.62f,
            0.525f, 0.0f, 0.62f,
            0.525f, 0.0f, 0.62f,
            0.525f, 0.0f, 0.62f
        },

        {
            0.62f, 0.0f, 0.0f,
            0.62f, 0.0f, 0.0f,
            0.62f, 0.0f, 0.0f,
            0.62f, 0.0f, 0.0f,
            0.62f, 0.0f, 0.0f,
            0.62f, 0.0f, 0.0f
        },

        {
            0.0f, 0.216f, 0.62f,
            0.0f, 0.216f, 0.62f,
            0.0f, 0.216f, 0.62f,
            0.0f, 0.216f, 0.62f,
            0.0f, 0.216f, 0.62f,
            0.0f, 0.216f, 0.62f
        },

        {
            0.788, 0.498, 0.024,
            0.788, 0.498, 0.024,
            0.788, 0.498, 0.024,
            0.788, 0.498, 0.024,
            0.788, 0.498, 0.024,
            0.788, 0.498, 0.024
        },

        {
            0.027, 0.522, 0.671,
            0.027, 0.522, 0.671,
            0.027, 0.522, 0.671,
            0.027, 0.522, 0.671,
            0.027, 0.522, 0.671,
            0.027, 0.522, 0.671
        },

        {
            0.024, 0.569, 0.133,
            0.024, 0.569, 0.133,
            0.024, 0.569, 0.133,
            0.024, 0.569, 0.133,
            0.024, 0.569, 0.133,
            0.024, 0.569, 0.133
        },

        {
            0.839, 0.839, 0.035,
            0.839, 0.839, 0.035,
            0.839, 0.839, 0.035,
            0.839, 0.839, 0.035,
            0.839, 0.839, 0.035,
            0.839, 0.839, 0.035
        }
    };

#endif // GRAPHICS_H
