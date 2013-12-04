#include <iostream>

#include <SDL/SDL.h>

#include "Graphics.h"
#include "EventManager.h"
#include "Tetromino.h"
#include "Board.h"
#include "Game.h"

//TODO clean up memory

#define WAIT_TIME 500       // milliseconds between the movements

using namespace std;

int main(int argc, char *argv[])
{
    atexit(SDL_Quit);

    Tetromino    tetromino;
    Board        board(10, 16);

    Graphics     graphics(&tetromino, &board);
    if(!graphics.InitGraphics(30, 16, 10)) return 0;

    board.InitBoard();

    Game game(&tetromino, &board);

    EventManager events;

    unsigned long timeStart = SDL_GetTicks();

	while (true)
	{
	    // Event Handling
	    events.PollEvents();

        if(events.isKeyDown(SDLK_ESCAPE)) break;

        if(events.isActualEvent(WINDOW_CLOSE)) break;

        // Rendering
        graphics.Rendering();

        // Timed vertical movement
        unsigned long timeEnd = SDL_GetTicks();

        if((timeEnd - timeStart) > WAIT_TIME)
        {
            if(game.CheckCollision())
            {
                board.LandShape(&tetromino);

                tetromino.NewShape();
            }
            else
            {
                tetromino.MoveDown();
            }

            timeStart = SDL_GetTicks();
        }

	}

	return 0;
}
