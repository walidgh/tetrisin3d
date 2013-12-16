#ifndef IGRAPHICS_H
#define IGRAPHICS_H


class IGraphics
{
    public:

        virtual ~IGraphics(){}

        // Initializes core graphic and display settings
        virtual bool InitGraphics(int scale, int row, int col) = 0;
        // Renders the scene
        virtual void Rendering() = 0;

        // Sets window title for game over
        virtual void SetWindowTitle(int score) = 0;
        // Sets window title with score and game speed
        virtual void SetWindowTitle(int score, int gameSpeed) = 0;
        // Sets window title with given string
        virtual void SetWindowTitle(const char *title) = 0;

    private:
        // Initializes SDL
        virtual bool InitSDL() = 0;
        // Initializes OpenGL and GLEW
        virtual bool InitOpenGL() = 0;
        // Draw 2d scquare on the given coordinates
        virtual void DrawSquare2D(float transX, float transY, int color) = 0;
        // Clears the color and depth buffers
        virtual void UpdateScreen() = 0;
        // Swap the frame buffer
        virtual void SwapFrameBuffer() = 0;
};

#endif // IGRAPHICS_H
