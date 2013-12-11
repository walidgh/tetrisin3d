#include "EventManager.h"

EventManager::EventManager()
{
    for(int i=0; i<400; i++)
    {
        mKeysDown[i] = false;
        mKeysUp[i]   = false;
    }
}

EventManager::~EventManager()
{
    //dtor
}

void EventManager::PollEvents()
{
    mActualEvent = NO_EVENT;

    if(SDL_PollEvent(&mSDLevent) == 0)
    {
        return;
    }

    switch(mSDLevent.type)
    {
        case SDL_KEYDOWN:
            mActualEvent = ANY_KEY_DOWN;
            mKeysDown[mSDLevent.key.keysym.sym] = true;
            mKeysUp[mSDLevent.key.keysym.sym] = false;
            break;

        case SDL_KEYUP:
            mKeysDown[mSDLevent.key.keysym.sym] = false;
            mKeysUp[mSDLevent.key.keysym.sym] = true;
            break;

        case SDL_QUIT:
            mActualEvent = WINDOW_CLOSE;
            break;

        default:
            break;
    }
}

bool EventManager::isActualEvent(Events event)
{
    if(mActualEvent == event)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool EventManager::isKeyDown(SDLKey key)
{
    return mKeysDown[key];
}

bool EventManager::isKeyUp(SDLKey key)
{
    bool b = mKeysUp[key];
    mKeysUp[key] = false;
    return b;
}
