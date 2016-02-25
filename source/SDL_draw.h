#ifndef SDL_DRAW_H_INCLUDED
#define SDL_DRAW_H_INCLUDED
#include <SDL/SDL.h>
#include "Painter32.h"


namespace SDL
{
    using namespace Drawing32;

class SDL_class;

class SDL_Canvas32 : public Canvas32
{
    SDL_Surface* sdl_sur;
    enum FlagName { FREE_THE_SDL_SURFACE = 1};
    enum ColorMask
    {
        AMASK = 0xFF000000,
        RMASK = 0x00FF0000,
        GMASK = 0x0000FF00,
        BMASK = 0x000000FF
    };

    void cleanup();

public:
    SDL_Canvas32() : sdl_sur(0) {}
    SDL_Canvas32(uint width, uint height, Uint32 sdl_flags = SDL_SWSURFACE | SDL_SRCALPHA);
    SDL_Canvas32(Uint32* pixels, uint width, uint height, bool copy = false, Uint32 sdl_flags = SDL_SWSURFACE | SDL_SRCALPHA);
    SDL_Canvas32(SDL_Surface* surface);
    SDL_Canvas32(const SDL_Canvas32& x);

    SDL_Canvas32& operator=(const SDL_Canvas32& x);
    SDL_Canvas32& operator=(SDL_Surface* s);// does not copy

    SDL_Canvas32& set(Uint32* pixels, uint width, uint height,
                      Uint32 alpha_mask = AMASK, Uint32 red_mask = RMASK, Uint32 green_mask = GMASK, Uint32 blue_mask = BMASK,
                      bool copy = false, Uint32 sdl_flags = SDL_SWSURFACE | SDL_SRCALPHA);
    SDL_Canvas32& set(uint width, uint height, Uint32 sdl_flags = SDL_SWSURFACE | SDL_SRCALPHA);

    operator SDL_Surface*() { return sdl_sur;}

    ~SDL_Canvas32();
    void lock();
    void unlock();

    void fill(const Color32& color=0, const Rect* rect=0);
    void vline(const Point& start, int offset, const Color32& color = 0xFF000000);
    void hline(const Point& start, int offset, const Color32& color = 0xFF000000);

    void blit(SDL_Canvas32& c, const Point& position = Point(0,0),const Rect& part = Rect(0,0,-1,-1));//
};

}
#endif // SDL_DRAW_H_INCLUDED
