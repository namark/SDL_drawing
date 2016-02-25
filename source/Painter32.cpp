#include "Painter32.h"
//#include "../float/consoleIO.h"

using namespace Drawing32;

//Color32
Color32& Color32::blend(const Color32& color)
{
    uint32 sourceAlpha = color.alpha(), sourceChannel = color.red();

    red( (uint32)red() + ((sourceAlpha*(sourceChannel-red()))>>8) );

    sourceChannel = color.green();

    green( (uint32)green() + ((sourceAlpha*(sourceChannel-green()))>>8) );

    sourceChannel = color.blue();

    blue( (uint32)blue() + ((sourceAlpha*(sourceChannel-blue()))>>8) );
}


//Canvas32

Canvas32::Canvas32(uint32 width, uint32 height) : w(width), h(height)
{
    sur = new uint32[w*h];
    flags.set(FREE_THE_SURFACE);
}

Canvas32::Canvas32(uint32* pixels, uint width, uint height, bool copy) :  w(width), h(height)
{
    if(copy)
    {
        flags.set(FREE_THE_SURFACE);
        uint size = w*h;
        sur = new uint32[size];
        memcpy(sur, pixels, size<<2);
    }
    else sur = pixels;
}


void Canvas32::cleanup()
{
    if(flags.flag(FREE_THE_SURFACE))
    {
        delete [] sur;
        flags.clear(FREE_THE_SURFACE);
    }

    sur = 0;
    w=h=0;
}

Canvas32::~Canvas32()
{
    cleanup();
}

Canvas32& Canvas32::operator=(const Canvas32& canv)
{
    cleanup();
    w = canv.w;
    h = canv.h;
    flags.set(FREE_THE_SURFACE);
    uint size = w*h;
    sur = new uint32[size];
    memcpy(sur, canv.sur, size<<2);
    return *this;
}

Canvas32& Canvas32::set(uint width, uint height)
{
    cleanup();
    w = width;
    h = height;
    uint size = w*h;
    flags.set(FREE_THE_SURFACE);
    sur = new uint32[size];
    return *this;
}

Canvas32& Canvas32::set(uint32* pixels, uint width, uint height, bool copy)
{
    cleanup();
    w = width;
    h = height;
    if(copy)
    {
        flags.set(FREE_THE_SURFACE);
        uint size = w*h;
        sur = new uint32[size];
        memcpy(sur, pixels, size<<2);
    }
    else sur = pixels;
    return *this;
}

void Canvas32::fill(const Color32& color,  const Rect* rect) // aaaaaaaaaaaaaaaa! pass the rect by a referance... use min to determine which is which
{
    lock();
    int xupto = rect->bottomRight().x,
        yupto = rect->bottomRight().y;
    for(int y = rect->y, ry = y*w, xfrom = rect->x; y < yupto; ++y, ry+=w)
        for(int x = xfrom; x < xupto; ++x)
            sur[x+ry] = color;
    unlock();
}

void Canvas32::vline(const Point& start, int offset, const Color32& color)
{
    lock();
    int ry= start.y*w, x = start.x;
    while(offset--)
    {
        sur[x+ry] = color;
        ry+=w;
    }
    unlock();
}

void Canvas32::hline(const Point& start, int offset, const Color32& color)
{
    lock();
    int ry = start.y*w, x = start.x;
    while(offset--) // use memcpy
    {
        sur[x+ry] = color;
        ++x;
    }
    unlock();
}

void Canvas32::blit(Canvas32& c, const Point& position, const Rect& part)
{
    lock();
    c.lock();

    Point   srs_point(part.x<0 ? 0 : part.x, part.y< 0 ? 0 : part.y),
            dest_point( (position.x < 0)? srs_point.x-=position.x,0:position.x,
                        (position.y < 0)? srs_point.y-=position.y,0:position.y );
    if(srs_point.x>c.w || srs_point.y>c.h || dest_point.x>w || dest_point.y>h) return;
    uint32 dest_pos = dest_point.y * w + dest_point.x;
    uint32 srs_pos = srs_point.y * c.width() + srs_point.x;

    int width, height;

    if(part.w() < 0)
    {
        width = c.w - srs_point.x;
        if(dest_point.x + width > w) width = w - dest_point.x;
    }
    else
    {
        width = part.w();
        if(dest_point.x + width > w) width = w - dest_point.x;
        if(srs_point.x + width > c.w) width = c.w - srs_point.x;
    }

    if(part.h() < 0)
    {
        height = c.h - srs_point.y;
        if(dest_point.y + height > h) height = h - dest_point.y;
    }
    else
    {
        height = part.h();
        if(dest_point.y + height > h) height = h - dest_point.y;
        if(srs_point.y + height > c.h) height = c.h - srs_point.y;
    }


    uint y = 0;
    uint32* to = sur+dest_pos, *from = c.sur+srs_pos;
    while( y < height )
    {
        memcpy(to, from, width << 2);
        to+=w, from+=c.w;
        ++y;
    }

    c.unlock();
    unlock();
}

void Canvas32::blitAlpha(Canvas32& c, const Point& position, const Rect& part)
{

}


//Painter32

void Painter32::setPixel(int x, int y) const
{
    canvas->lock();
    canvas->surface()[x+y*canvas->width()] = pen_color;
    canvas->unlock();
}

void Painter32::setPixel(const Point& p) const
{
    canvas->lock();
    canvas->surface()[p.x+p.y*canvas->width()] = pen_color;
    canvas->unlock();
}

void Painter32::drawRect(const Rect& rect) const
{
    canvas->lock();
    if(brush_color & 0xFF000000) canvas->fill(brush_color, &rect);
    if(pen_color & 0xFF000000)
    {
        Point tl = rect.topLeft() + Point(-1,-1), br = rect.bottomRight();
        canvas->vline(tl, rect.w()+1, pen_color);
        canvas->hline(tl, rect.h(), pen_color); // perhaps tl.x-1 here?
        canvas->vline(br, -(rect.w()+1), pen_color);
        canvas->hline(br, -rect.h(), pen_color);
    }
    canvas->unlock();
}

