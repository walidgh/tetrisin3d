#include "Graphics.h"

#include <iostream>

#include "lib_3rd_party/glm/glm.hpp"
#include "lib_3rd_party/glm/gtc/matrix_transform.hpp"
#include "lib_3rd_party/shader.hpp"

Graphics::Graphics(Tetromino *tetromino, Board *board)
{
    mTetromino = tetromino;
    mBoard     = board;
}

Graphics::~Graphics()
{

}

bool Graphics::InitGraphics(int scale, int row, int col)
{
    mRow            = row;
    mCol            = col;
    mScale          = scale;
    mScreenWidth    = col * scale;
    mScreenHeight   = row * scale;

    if(!InitSDL()) return false;
    if(!InitOpenGL()) return false;

    mShaderProgramId = LoadShaders("data/main.vs", "data/main.fs");

    mMVPuniformLocation = glGetUniformLocation(mShaderProgramId, "MVP");

	glGenBuffers(1, &mVertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &mColorBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, mColorBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);

    // The shader program used only in DrawSquare(float transX, float transY)
    // It is okay to install it here
    // In case of using more shaders, it may cause some trouble
    glUseProgram(mShaderProgramId);

    return true;
}

bool Graphics::InitSDL()
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

bool Graphics::InitOpenGL()
{
    // Init GLEW
    if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return false;
	}

    // Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

    std::cout << "OpenGL initialization OK\n";
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL   version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    return true;
}

void Graphics::Rendering()
{
    UpdateScreen();

    // Draw moving tetromino
    float transX = mTetromino->getTopLeft()->col;
    float transY = mTetromino->getTopLeft()->row;
//    unsigned int **shape = mTetromino->getShape();

    for(int row=0; row<mTetromino->getHeight(); row++)
    {
        for(int col=0; col<mTetromino->getWidth(); col++)
        {
            if(mTetromino->getShape()[row][col] != 0)
            {
                DrawSquare(col + transX, row + transY);
            }
        }
    }

    // Draw landed tetrominos
    for(int row=0; row<mRow; row++)
    {
        for(int col=0; col<mCol; col++)
        {
            if(mBoard->GetLanded()[row][col] != 0)
            {
                DrawSquare(col, row);
            }
        }
    }

    SwapFrameBuffer();
}

void Graphics::DrawSquare(float transX, float transY)
{
    glm::mat4 Projection2d = glm::ortho(0.0f, float(mScreenWidth), float(mScreenHeight), 0.0f);
	glm::mat4 Model        = glm::mat4(1.0f);

    glm::mat4 scale      = glm::scale(glm::mat4(1.0f), glm::vec3(float(mScale)));
    glm::mat4 translate  = glm::translate(glm::mat4(1.0f), glm::vec3(transX, transY, 0.0f));
    glm::mat4 Transform  = scale * translate;

    glm::mat4 MVP        = Projection2d * Transform * Model;

	glUniformMatrix4fv(mMVPuniformLocation, 1, GL_FALSE, &MVP[0][0]);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);
    glVertexAttribPointer(
        0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    // 2nd attribute buffer : colors
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, mColorBufferId);
    glVertexAttribPointer(
        1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
        3,                                // size
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 18);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void Graphics::UpdateScreen()
{
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::SwapFrameBuffer()
{
    // Swap OpenGL framebuffer
    SDL_GL_SwapBuffers();
}

void Graphics::SetWindowTitle(unsigned int score)
{
    char title[64];
    sprintf(title, "Tetris 3D - SCORE: %d - GAME OVER", score);
    SDL_WM_SetCaption(title, NULL);
}

void Graphics::SetWindowTitle(unsigned int score, unsigned int gameSpeed)
{
    char title[64];
    sprintf(title, "Tetris 3D - SCORE: %d - Game speed: %d", score, gameSpeed);
    SDL_WM_SetCaption(title, NULL);
}

void Graphics::SetWindowTitle(const char *title)
{
    SDL_WM_SetCaption(title, NULL);
}
