#include "GraphicsOld.h"

#include <iostream>

#include "lib_3rd_party/glm/glm.hpp"
#include "lib_3rd_party/glm/gtc/matrix_transform.hpp"
#include "lib_3rd_party/shader.hpp"

GraphicsOld::GraphicsOld(Tetromino *tetromino, Board *board)
{
    mTetromino = tetromino;
    mBoard     = board;
}

GraphicsOld::~GraphicsOld(){}

bool GraphicsOld::InitGraphics(int scale, int row, int col)
{
    mRow            = row;
    mCol            = col;
    mScale          = scale;
    mScreenWidth    = col * scale;
    mScreenHeight   = row * scale;

    if(!InitSDL()) return false;
    if(!InitOpenGL()) return false;

    return true;
}

void GraphicsOld::Rendering()
{
    UpdateScreen();

    // Draw moving tetromino
    float transX = mTetromino->GetTopLeft()->col;
    float transY = mTetromino->GetTopLeft()->row;

    for(int row=0; row<mTetromino->GetHeight(); row++)
    {
        for(int col=0; col<mTetromino->GetWidth(); col++)
        {
            if(mTetromino->GetShape()[row][col] != 0)
            {
                DrawSquare2D(col + transX, row + transY, mTetromino->GetShape()[row][col]);
            }
        }
    }

    // Draw landed tetrominos
    for(int row=0; row<mRow; row++)
    {
        for(int col=0; col<mCol; col++)
        {
            DrawSquare2D(col, row, mBoard->GetLanded()[row][col]);
        }
    }

    SwapFrameBuffer();
}

void GraphicsOld::SetWindowTitle(int score)
{
    char title[64];
    sprintf(title, "Tetris - SCORE: %d - GAME OVER", score);
    SDL_WM_SetCaption(title, NULL);
}

void GraphicsOld::SetWindowTitle(int score, int gameSpeed)
{
    char title[64];
    sprintf(title, "Tetris - SCORE: %d - Game speed: %d", score, gameSpeed);
    SDL_WM_SetCaption(title, NULL);
}

void GraphicsOld::SetWindowTitle(const char *title)
{
    SDL_WM_SetCaption(title, NULL);
}

bool GraphicsOld::InitSDL()
{
    // Init video
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
		std::cout << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}

	// Set window position to center
	SDL_putenv((char*)"SDL_VIDEO_CENTERED=center");

    // Set video mode
    if ((mScreen = SDL_SetVideoMode(mScreenWidth, mScreenHeight, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL)) == NULL)
    {
		std::cout << "Couldn't set " << mScreenWidth << "x" << mScreenHeight <<  " video mode: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}

    std::cout << "SDL initialization OK\n";

    return true;
}

bool GraphicsOld::InitOpenGL()
{
    // Init GLEW
    if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return false;
	}

    // Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glClearDepth(1.0f);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, mScreenWidth, mScreenHeight, 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    std::cout << "OpenGL initialization OK\n";
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL   version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    return true;
}

void GraphicsOld::DrawSquare2D(float transX, float transY, int color)
{
    glPushMatrix();

    glScalef(mScale, mScale, 1.0f);
    glTranslatef(transX, transY, 0.0f);

    glBegin(GL_TRIANGLES);
    glColor3f(Colors[color][0], Colors[color][1], Colors[color][2]);
    glVertex3f(Vertices[0], Vertices[1], Vertices[2]);
    glVertex3f(Vertices[3], Vertices[4], Vertices[5]);
    glVertex3f(Vertices[6], Vertices[7], Vertices[8]);
    glVertex3f(Vertices[9], Vertices[10], Vertices[11]);
    glVertex3f(Vertices[12], Vertices[13], Vertices[14]);
    glVertex3f(Vertices[15], Vertices[16], Vertices[17]);
    glEnd();

    glPopMatrix();
}

void GraphicsOld::UpdateScreen()
{
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicsOld::SwapFrameBuffer()
{
    // Swap OpenGL framebuffer
    SDL_GL_SwapBuffers();
}
