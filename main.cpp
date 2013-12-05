#include <iostream>

#include <SDL/SDL.h>

#include "Graphics.h"
#include "EventManager.h"
#include "Tetromino.h"
#include "Board.h"
#include "Game.h"

//TODO clean up memory
//TODO move left bugfix
//TODO renaming some variables
//TODO comments

#define WAIT_TIME 400       // milliseconds between the movements

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

//    EventManager events;

    unsigned long timeStart = SDL_GetTicks();

    SDL_Event event;
    bool run = true;
	while (run)
	{
	    // Event handling for continuous actions
//	    events.PollEvents();
//
//        if(events.isKeyDown(SDLK_ESCAPE)) break;
//
//        if(events.isActualEvent(WINDOW_CLOSE)) break;

        // Event handling for fractional actions

        while(SDL_PollEvent(&event))
        {
            switch(event.type)
                {
                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym)
                        {
                            case SDLK_LEFT:
                                {
                                    tetromino.getPotentialTopLeft()->col -= 1;
                                    if(game.CheckCollisionWithBorder())
                                    {
                                        tetromino.getPotentialTopLeft()->col += 1;
                                    }
                                    else
                                    {
                                        tetromino.Move();
                                    }
                                }
                                break;

                            case SDLK_RIGHT:
                                {
                                    tetromino.getPotentialTopLeft()->col += 1;
                                    if(game.CheckCollisionWithBorder())
                                    {
                                        tetromino.getPotentialTopLeft()->col -= 1;
                                    }
                                    else
                                    {
                                        tetromino.Move();
                                    }
                                }
                                break;

                            case SDLK_r:
                                {
                                    tetromino.RotatePotential();
                                    if(!game.CheckCollisionWhenRotated())
                                    {
                                        tetromino.Rotate();
                                    }
                                }
                                break;

                            case SDLK_ESCAPE:
                                run = false;
                                break;

                            default:
                                break;
                        }
                        break;

                    case SDL_QUIT:
                        run = false;

                    default:
                        break;
                }
        }

        // Rendering
        graphics.Rendering();

        // Timed vertical movement
        unsigned long timeEnd = SDL_GetTicks();

        if((timeEnd - timeStart) > WAIT_TIME)
        {
            game.CheckCollisionWithBorder();

            tetromino.getPotentialTopLeft()->row += 1;
            if(game.CheckCollisionWithLanded())
            {
                tetromino.getPotentialTopLeft()->row -= 1;
                board.LandShape(&tetromino);
                tetromino.NewShape();
            }
            else
            {
                tetromino.Move();
            }

            timeStart = SDL_GetTicks();
        }

	}

	return 0;
}
