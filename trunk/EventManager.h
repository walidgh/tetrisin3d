#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <SDL/SDL.h>

enum Events         // Basic events definition
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
    public:     // Functions

        EventManager();         // Constructor
        ~EventManager();        // Destructor

        void PollEvents();      // Poll SDL events

        bool isActualEvent(Events event);   // Checks the actual event

        bool isKeyDown(SDLKey key);         // Checks is key down
        bool isKeyUp(SDLKey key);           // Checks is key up
        bool isKeyPressed(SDLKey key);      // Checks is key pressed

    private:    // Variables

        SDL_Event mSDLevent;    // SDL event

        Events mActualEvent;    // Actual event sign

        bool mKeysDown[400];    // Pressed keys
        bool mKeysUp[400];      // Released keys
        bool mIsKeyPressed;        // Holds "key is down" status
};

#endif // EVENTMANAGER_H
