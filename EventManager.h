#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <SDL/SDL.h>

//TODO init subsystem

enum Events
{
    NO_EVENT = 0,
    ANY_KEY_DOWN,
    WINDOW_CLOSE,
    MOUSE_BUTTON_LEFT_UP,
    MOUSE_BUTTON_RIGHT_UP,
    MOUSE_BUTTON_LEFT_DOWN,
    MOUSE_BUTTON_RIGHT_DOWN
};

class EventManager
{
    public:     // functions

        EventManager();
        ~EventManager();

        void PollEvents();

        bool isActualEvent(Events event);

        bool isKeyDown(SDLKey key);
        bool isKeyUp(SDLKey key);

    private:    // variables

        SDL_Event mSDLevent;

        Events mActualEvent;

        bool mKeysDown[400];
        bool mKeysUp[400];
};

#endif // EVENTMANAGER_H
