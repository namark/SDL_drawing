#ifndef GEOMETRY2D_H_INCLUDED
#define GEOMETRY2D_H_INCLUDED
#include <cmath>
#include <algorithm>
#include "General.h" // I don't actually use this here :/

// hmmm... maybe a virtual class that does everything with 0s, and these could inherit it... hmmm... how would conversion work theeen...

namespace Geometry2D
{

//int round(double x);
template <typename T>
bool is_between(const T& x, const T& a, const T& b)
{
    const T& mn = std::min(a,b);
    const T& mx = std::max(a,b);
    return x>=mn && x<=mx;
}

struct Rect;
struct Point;

struct PointF
{
    double x, y;
    PointF(): x(0.0), y(0.0) {}
    PointF(double x, double y): x(x), y(y) {}
    PointF(const Point& p);

    //Point round();

    PointF & operator = (const Point& p);
    PointF operator+(const PointF& p) const;
    PointF operator-(const PointF& p) const;
    PointF operator+(const Point& p) const;
    PointF operator-(const Point& p) const;

    PointF & operator+=(const PointF& p);
    PointF & operator+=(const Point& p);
    PointF & operator-=(const PointF& p);
    PointF & operator-=(const Point& p);

    bool operator==(const PointF& p) const;
    bool operator!=(const PointF& p) const;
    bool operator==(const Point& p) const;
    bool operator!=(const Point& p) const;
};

PointF operator+(const PointF& p, const double& a);
PointF operator+(const double& a, const PointF& p);
PointF operator-(const PointF& p, const double& a);
//PointF operator-(const double& a, const PointF& p);


struct Point
{
    int x, y;
    Point(): x(0), y(0) {}
    Point(int x, int y): x(x), y(y) {}
    Point(const PointF& p);

    Point & operator = (const PointF& p);
    Point operator+(const Point& p) const;
    Point operator-(const Point& p) const;
    Point operator+(const PointF& p) const;
    Point operator-(const PointF& p) const;

    Point & operator+=(const Point& p);
    Point & operator+=(const PointF& p);
    Point & operator-=(const Point& p);
    Point & operator-=(const PointF& p);

    bool operator==(const Point& p) const;
    bool operator!=(const Point& p) const;
    bool operator==(const PointF& p) const;
    bool operator!=(const PointF& p) const;

    bool is_in(const Rect& rect) const;
};

Point operator+(const Point& p, const int& a);
Point operator+(const int& a, const Point& p);
Point operator-(const Point& p, const int& a);
//Point operator-(const int& a, const Point& p);

struct RectF;

struct Rect : public Point
{
    Point s;// size, width and height

    Rect(Point top_left, Point size) : Point(top_left), s(size) {}
    Rect(int x, int y, int width, int height) : Point(x,y), s(width,height) {}
    Rect(const RectF & r);

    Rect& operator=(const RectF& r);

    int w() const {return s.x;}
    int h() const {return s.y;}

    bool valid(){return s.x>=0 && s.y>=0;}
    //void move(Point dv) {tl += dv;}
    //void moveX(int dx) {tl.x += dx;}
    //void moveY(int dx) {tl.y += dy;}

    //void scale(Point dv);
    //void scaleW(int dw);
    //void scaleH(int dh);


    Point topLeft() const {return *this;}
    Point bottomRight() const {return *this+s;}
};

struct RectF : public PointF
{
    PointF s;// size, width and height

    RectF(PointF top_left, PointF size) : PointF(top_left), s(size) {}
    RectF(double x, double y, double width, double height) : PointF(x,y), s(width,height) {}
    RectF(const Rect & r);

    RectF& operator=(const Rect& r);

    double w() const {return s.x;}
    double h() const {return s.y;}

    bool valid(){return s.x>=0 && s.y>=0;}

    PointF topLeft() const {return *this;}
    PointF bottomRight() const {return *this+s;}
};

}
#endif // GEOMETRY2D_H_INCLUDED
