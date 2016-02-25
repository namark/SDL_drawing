#include "SDL_class.h"

using namespace SDL;

SDL_class::SDL_class(int win_width, int win_height,
                     int bits_per_pixel,
                     const char* caption,
                     const char* icon,
                     int frames_per_second,
                     Uint32 flags)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    screen_canvas = SDL_SetVideoMode(WIDTH=win_width, HEIGHT=win_height, BPP=bits_per_pixel, flags);
    SDL_WM_SetCaption(caption, icon);
    run = true;
    frame_delay = 1000/(FPS=frames_per_second);
}

void SDL_class::begin(int argc, char* argm[])
{
    while(run)
    {
        timer = SDL_GetTicks();
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    close();
                break;
                case SDL_MOUSEBUTTONDOWN:
                    mousePressed(event.button);
                break;
                case SDL_MOUSEBUTTONUP:
                    mouseReleased(event.button);
                break;
                case SDL_MOUSEMOTION:
                    mouseMoved(event.motion);
                break;
                case SDL_KEYDOWN:
                    keyPressed(event.key.keysym);
                break;
                case SDL_KEYUP:
                    keyReleased(event.key.keysym);
                break;
            }
        }

        mainLoop();

        SDL_Flip(screen_canvas);
        timer = (frame_delay - (SDL_GetTicks()-timer));
        if(timer > 0) SDL_Delay(timer);
    }
    SDL_Quit(); // maybe move this to the destructor
}

void SDL_class::close() { run=!closed();}
