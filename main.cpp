#include <SDL/SDL.h>

#include "Graphics.h"
#include "EventManager.h"
#include "Tetromino.h"

//TODO clean up memory

int main(int argc, char *argv[])
{
    atexit(SDL_Quit);

    Tetromino    tetromino;
    Graphics     graphics(&tetromino);
    EventManager events;

    if(!graphics.InitGraphics(30, 16, 10))
    {
        return 0;
    }

	while (true)
	{
	    // Event Handling
	    events.PollEvents();

        if(events.isKeyDown(SDLK_ESCAPE)) break;

        if(events.isActualEvent(WINDOW_CLOSE)) break;

        // Rendering
        graphics.Rendering();
	}

	return 0;
}
