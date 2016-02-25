#ifndef SDL_CLASS_H_INCLUDED
#define SDL_CLASS_H_INCLUDED
#include "SDL_draw.h"

namespace SDL
{

class SDL_class
{
    int WIDTH; // why not uint???
    int HEIGHT;
    int BPP;
    int FPS;
    int frame_delay;
    SDL_Canvas32 screen_canvas;
    //SDL_Surface* screen;
    SDL_Event event;
    int timer;
    bool run;

protected:
    virtual void mainLoop(){}
    virtual void keyPressed(SDL_keysym& key){}
    virtual void keyReleased(SDL_keysym& key){}
    virtual void mousePressed(SDL_MouseButtonEvent& mouse){}
    virtual void mouseReleased(SDL_MouseButtonEvent& mouse){}
    virtual void mouseMoved(SDL_MouseMotionEvent& mouse){}
    virtual bool closed(){return true;}
public:
    SDL_class(  int win_width, int win_height,
                int bits_per_pixel = 32,
                const char* caption = "SDL window",
                const char* icon = 0,
                int frames_per_second = 30,
                Uint32 flags = SDL_SWSURFACE /*| SDL_SRCALPHA*/);
    void begin(int argc = 0, char** argm = 0); // sets up the main loop and handles events
    void close(); // triggers closed();
    virtual ~SDL_class(){}

    SDL_Canvas32& screenCanvas() {return screen_canvas;}

};

}
#endif // SDL_CLASS_H_INCLUDED
