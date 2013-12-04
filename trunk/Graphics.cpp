#include "Graphics.h"

#include <iostream>

#include "lib_3rd_party/glm/glm.hpp"
#include "lib_3rd_party/glm/gtc/matrix_transform.hpp"
#include "lib_3rd_party/shader.hpp"

// TODO move mTetromino and mBoard from private var to rendering args

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
    mScale          = scale;
    mRow            = row;
    mCol            = col;
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

    // Set window title
    SDL_WM_SetCaption("Tetris 3D", "");

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
    float transX = mTetromino->getPositionCol();
    float transY = mTetromino->getPositionRow();
    unsigned int **shape = mTetromino->getShape();

    for(int row=0; row<4; row++)
    {
        for(int col=0; col<4; col++)
        {
            if(shape[row][col] != 0)
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
    glUseProgram(mShaderProgramId);

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

/**
    TEST
*/

//void Graphics::InitTestData()
//{
//
//	mMatrixID = glGetUniformLocation(mShaderProgramId, "MVP");
//
//	glGenBuffers(1, &mVertexbuffer);
//	glBindBuffer(GL_ARRAY_BUFFER, mVertexbuffer);
////	glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertex), squareVertex, GL_STATIC_DRAW);
//
//	glGenBuffers(1, &mColorbuffer);
//	glBindBuffer(GL_ARRAY_BUFFER, mColorbuffer);
////	glBufferData(GL_ARRAY_BUFFER, sizeof(squareColor), squareColor, GL_STATIC_DRAW);
//}
//
//void Graphics::TestRendering()
//{
//    UpdateScreen();
//
//    glUseProgram(mShaderProgramId);
//
//    glm::mat4 Projection2d = glm::ortho(0.0f, 1024.0f, 768.0f, 0.0f);
//
//	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
////	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
//	// Camera matrix
////	glm::mat4 View       = glm::lookAt(
////								glm::vec3(0,3,3), // Camera is at (4,3,-3), in World Space
////								glm::vec3(0,0,0), // and looks at the origin
////								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
////						   );
//	// Model matrix : an identity matrix (model will be at the origin)
//	glm::mat4 Model      = glm::mat4(1.0f);
//	// Our ModelViewProjection : multiplication of our 3 matrices
////	glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around
//
//    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
//    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(500.0f, 0.0f, 0.0f));
//
//    glm::mat4 Transform = scale * translate;
//
//    glm::mat4 MVP        = Projection2d * Transform * Model;
//
//    // Send our transformation to the currently bound shader,
//    // in the "MVP" uniform
//	glUniformMatrix4fv(mMatrixID, 1, GL_FALSE, &MVP[0][0]);
//
//    // 1rst attribute buffer : vertices
//    glEnableVertexAttribArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, mVertexbuffer);
//    glVertexAttribPointer(
//        0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
//        2,                  // size
//        GL_FLOAT,           // type
//        GL_FALSE,           // normalized?
//        0,                  // stride
//        (void*)0            // array buffer offset
//    );
//
//    // 2nd attribute buffer : colors
//    glEnableVertexAttribArray(1);
//    glBindBuffer(GL_ARRAY_BUFFER, mColorbuffer);
//    glVertexAttribPointer(
//        1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
//        3,                                // size
//        GL_FLOAT,                         // type
//        GL_FALSE,                         // normalized?
//        0,                                // stride
//        (void*)0                          // array buffer offset
//    );
//
//    // Draw the triangle !
//    glDrawArrays(GL_TRIANGLES, 0, 12);
//
//    glDisableVertexAttribArray(0);
//    glDisableVertexAttribArray(1);
//
//    SwapFrameBuffer();
//}
