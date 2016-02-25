#ifndef PAINTER32_H_INCLUDED
#define PAINTER32_H_INCLUDED
#include <cstring> // for memcpy, and memset... do i really need this
#include "Geometry2D.h"

namespace Drawing32
{
using namespace Generic;
using namespace Geometry2D;

class Color32
{
    uint8 color[4];
public:
    enum COLOR_COMPONENT_POSITION
    #ifndef BIG_ENDIAN_MEMORY
    {
        ALPHA_POSITION = 3,
        RED_POSITION = 2,
        GREEN_POSITION = 1,
        BLUE_POSITION = 0
    };
    #else
    {
        ALPHA_POSITION = 0,
        RED_POSITION = 1,
        GREEN_POSITION = 2,
        BLUE_POSITION = 3
    };
    #endif

    Color32(const uint32& hex_color) {*((uint32*)color)=hex_color;}

    uint8 alpha() const {return color[ALPHA_POSITION];}
    uint8 red() const {return color[RED_POSITION];}
    uint8 green() const {return color[GREEN_POSITION];}
    uint8 blue() const {return color[BLUE_POSITION];}

    void alpha(uint8 alpha) {color[ALPHA_POSITION] = alpha;}
    void red(uint8 red) {color[RED_POSITION] = red;}
    void green(uint8 green) {color[GREEN_POSITION] = green;}
    void blue(uint8 blue) {color[BLUE_POSITION] = blue;}

    uint32 hex() const{return *((uint32*)color);}

    Color32& operator=(const uint32& x)
    {
        *((uint32*)color) = x;
        return *this;
    }
    operator uint32() const { return *((uint32*)color);}

    Color32& blend(const Color32& color);
};



class Canvas32
{
protected:
    uint w, h;
    uint32* sur;
    // flags are initialized by 0
    FLAGS flags; // 0 - the sur needs to be freed; the rest are unused (so you can use them!)
    enum FlagName { FREE_THE_SURFACE = 0 };

    void cleanup();

public:
    Canvas32() : w(0), h(0), sur(0){}
    Canvas32(uint width, uint height);
    Canvas32(uint* pixels, uint width, uint height, bool copy = false);
    // too many constructors... well... i try to keep it simple... one constructor gets too hairy...

    virtual ~Canvas32();
    virtual void lock() {};
    virtual void unlock() {};

    uint32 width() const {return w;}
    uint32 height() const {return h;}
    uint32* surface() const {return sur;}

    Canvas32& operator=(const Canvas32& canv);
    Canvas32& set(uint width, uint height);
    Canvas32& set(uint32* pixels, uint width, uint height, bool copy = false);

    virtual void fill(const Color32& color=0, const Rect* rect=0);
    virtual void vline(const Point& start, int offset, const Color32& color = 0xFF000000);
    virtual void hline(const Point& start, int offset, const Color32& color = 0xFF000000);
    virtual void blit(Canvas32& c, const Point& position = Point(0,0),const Rect& part = Rect(0,0,-1,-1)); // on me
    virtual void blitAlpha(Canvas32& c, const Point& position = Point(0,0),const Rect& part = Rect(0,0,-1,-1)); // on me
};


class Painter32
{
    Color32 pen_color, brush_color;
    short pen_width;
    Canvas32* canvas;

    public:
        Painter32(Canvas32& canvas, Color32 pen_color = 0xFF000000, short pen_width = 1, Color32 brush_color = 0) :
            canvas(&canvas), pen_color(pen_color), pen_width(pen_width), brush_color(brush_color)
        {}

        void setPenColor(Color32 pencol){pen_color = pencol;}
        void setBrushColor(Color32 brshcol){brush_color = brshcol;}

        void setPixel(int x, int y) const;
        void setPixel(const Point& p) const;

        // basic Bresenham line
        void drawLine(int x1, int y1, int x2, int y2) const;
        void drawLine(const Point& p1, const Point& p2) const;

        // basic Bresenham circle
        void drawCircle(int center_x, int center_y, int radius) const;
        void drawCircle(const Point& center, int radius) const;

        void drawRect(const Rect& rect) const;


};

}
#endif // PAINTER32_H_INCLUDED
