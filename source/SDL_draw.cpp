#include "SDL_draw.h"

using namespace SDL;

SDL_Canvas32::SDL_Canvas32(uint width, uint height, Uint32 sdl_flags)
{
    sdl_sur = SDL_CreateRGBSurface(sdl_flags, width, height, 32, RMASK, GMASK, BMASK, AMASK);
    flags.set(FREE_THE_SDL_SURFACE);
    w = width; h = height;
}

SDL_Canvas32::SDL_Canvas32(Uint32* pixels, uint width, uint height, bool copy, Uint32 sdl_flags)
{
    if(copy)
    {
        sdl_sur = SDL_CreateRGBSurface(sdl_flags, width, height, 32, RMASK, GMASK, BMASK, AMASK);
        flags.set(FREE_THE_SDL_SURFACE);
        w = width; h = height;
        lock();
        memcpy(sur,pixels,(w*h)<<2);
        unlock();
    }
    else
    {
        sdl_sur = SDL_CreateRGBSurface(sdl_flags, 0, 0, 32, RMASK, GMASK, BMASK, AMASK);
        if (sdl_sur)
        {
            sdl_sur->flags |= SDL_PREALLOC;
            sdl_sur->pixels = pixels;
            sdl_sur->w = width;
            sdl_sur->h = height;
            sdl_sur->pitch = width<<2;
            SDL_SetClipRect(sdl_sur, NULL);
        }
        //flags.set(FREE_THE_SURFACE);
        w = width; h = height;
        sur = pixels;
    }
}

SDL_Canvas32::SDL_Canvas32(SDL_Surface* surface)
{
    sdl_sur = surface;
    w = sdl_sur->w;
    h = sdl_sur->h;
}

SDL_Canvas32::SDL_Canvas32(const SDL_Canvas32& x)
{
    w = x.w; h = x.h;
    sdl_sur = SDL_CreateRGBSurface(x.sdl_sur->flags, w, h, 32, RMASK, GMASK, BMASK, AMASK);
    flags.set(FREE_THE_SDL_SURFACE);
    lock();
    memcpy(sur,x.sdl_sur->pixels,(w*h)<<2);
    unlock();
}

SDL_Canvas32& SDL_Canvas32::operator=(const SDL_Canvas32& x)
{
    if(this != &x)
    {
        cleanup();
        w = x.w; h = x.h;
        sdl_sur = SDL_CreateRGBSurface(x.sdl_sur->flags, w, h, 32, RMASK, GMASK, BMASK, AMASK);
        flags.set(FREE_THE_SDL_SURFACE);
        lock();
        memcpy(sur,x.sdl_sur->pixels,(w*h)<<2);
        unlock();
    }
    return *this;
}

SDL_Canvas32& SDL_Canvas32::operator=(SDL_Surface* s)
{
    if(sdl_sur != s)
    {
        cleanup();
        sdl_sur = s;
        w = s->w; h = s->h;
    }
    return *this;
}

void SDL_Canvas32::cleanup()
{
    if(flags[FREE_THE_SDL_SURFACE])
    {
        SDL_FreeSurface(sdl_sur);
        flags.clear(FREE_THE_SDL_SURFACE);
    }
}

SDL_Canvas32::~SDL_Canvas32()
{
    cleanup();
    sur = 0;
    sdl_sur = 0;
    w = h =0;
}

SDL_Canvas32& SDL_Canvas32::set(Uint32* pixels, uint width, uint height,
                                Uint32 alpha_mask , Uint32 red_mask, Uint32 green_mask, Uint32 blue_mask,
                                bool copy, Uint32 sdl_flags)
{
    cleanup();
    if(copy)
    {
        sdl_sur = SDL_CreateRGBSurface(sdl_flags, width, height, 32, red_mask, green_mask, blue_mask, alpha_mask);
        flags.set(FREE_THE_SDL_SURFACE);
        w = width; h = height;
        lock();
        memcpy(sur,pixels,(w*h)<<2);
        unlock();
    }
    else
    {
        sdl_sur = SDL_CreateRGBSurface(sdl_flags, 0, 0, 32, red_mask, green_mask, blue_mask, alpha_mask);
        if (sdl_sur)
        {
            sdl_sur->flags |= SDL_PREALLOC;
            sdl_sur->pixels = pixels;
            sdl_sur->w = width;
            sdl_sur->h = height;
            sdl_sur->pitch = width<<2;
            SDL_SetClipRect(sdl_sur, NULL);
        }
        //flags.set(FREE_THE_SURFACE);
        w = width; h = height;
        sur = pixels;
    }
    return *this;
}

SDL_Canvas32& SDL_Canvas32::set(uint width, uint height, Uint32 sdl_flags)
{
    cleanup();
    sdl_sur = SDL_CreateRGBSurface(sdl_flags, width, height, 32, RMASK, GMASK, BMASK, AMASK);
    flags.set(FREE_THE_SDL_SURFACE);
    w = width; h = height;
    return *this;
}

void SDL_Canvas32::lock()
{
    if(SDL_MUSTLOCK(sdl_sur)) SDL_LockSurface(sdl_sur);
    sur = reinterpret_cast<Uint32*> (sdl_sur->pixels);
}

void SDL_Canvas32::unlock()
{
    sur=0;// ?
    if(SDL_MUSTLOCK(sdl_sur)) SDL_UnlockSurface(sdl_sur);
}

void SDL_Canvas32::fill(const Color32& color, const Rect* rect)
{
    if(rect)
    {
        SDL_Rect r;
        r.x = rect->x;
        r.y = rect->y;
        r.h = rect->h();
        r.w = rect->w();
        SDL_FillRect(sdl_sur,&r,color);
    }
    else SDL_FillRect(sdl_sur,0,color);
}

void SDL_Canvas32::vline(const Point& start, int offset, const Color32& color)
{
    if(offset == 0) return;
    SDL_Rect r;
    r.y = start.y;

    if(offset > 0)
    {
        ++offset;
        r.x = start.x;
        r.w = offset;
    }
    else
    {
        //--offset;
        r.x = start.x + offset;
        r.w = -offset+1;
    }
    r.h = 1;
    SDL_FillRect(sdl_sur,&r,color);
}


void SDL_Canvas32::hline(const Point& start, int offset, const Color32& color)
{
    if(offset == 0) return;
    SDL_Rect r;
    r.x = start.x;

    if(offset > 0)
    {
        ++offset;
        r.y = start.y;
        r.h = offset;
    }
    else
    {
        //--offset;
        r.y = start.y + offset;
        r.h = -offset+1;
    }
    r.w = 1;
    SDL_FillRect(sdl_sur,&r,color);
}

void SDL_Canvas32::blit(SDL_Canvas32& c, const Point& position,const Rect& part)
{
    SDL_Rect srs_rect, dest_rect;
    srs_rect.x = part.x;
    srs_rect.y = part.y;
    srs_rect.w = part.w();
    srs_rect.h = part.h();
    dest_rect.x = position.x;
    dest_rect.y = position.y;
    SDL_BlitSurface(c,&srs_rect,*this,&dest_rect);
}
