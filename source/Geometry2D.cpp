#include "Geometry2D.h"

using namespace Geometry2D;
//hmmm... lots of same stuff over and over again... i don't like this

//int round(double x) {return (x>0) ? x+0.5 : x-0.5;} // alright! alright!... cmath... do whatever you want...

// int to float conversions

Point::Point(const PointF& p) : x(round(p.x)), y(round(p.y)) {}

Point & Point::operator = (const PointF& p) { x=round(p.x); y=round(p.y); return *this; }

PointF::PointF(const Point& p)  : x(p.x), y(p.y) {}

PointF & PointF::operator = (const Point& p) { x=p.x; y=p.y; return *this; }

Rect::Rect(const RectF& r) : Point(r), s(r.s) {}

Rect& Rect::operator=(const RectF& r) { *this = r; s = r.s; return *this; }

RectF::RectF(const Rect& r) : PointF(r), s(r.s) {}

RectF& RectF::operator=(const Rect& r) { *this = r; s = r.s; return *this; }


// other operators
// plusing
Point Point::operator+(const Point& p) const { return Point(x+p.x, y+p.y); }
Point Point::operator+(const PointF& p) const { return PointF(x+round(p.x), y+round(p.y)); }

Point operator+(const Point& p, const int& i) { return Point(p.x+i, p.y+i); }
Point operator+(const int& i, const Point& p) { return Point(p.x+i, p.y+i); }

PointF PointF::operator+(const PointF& p) const { return PointF(x+p.x, y+p.y); }
PointF PointF::operator+(const Point& p) const { return PointF(x+p.x, y+p.y); }

PointF operator+(const PointF& p, const double& i) { return PointF(p.x+i, p.y+i); }
PointF operator+(const double& i, const PointF& p) { return PointF(p.x+i, p.y+i); }

PointF & PointF::operator+=(const PointF& p) { x+=p.x; y+=p.y; return *this; }
PointF & PointF::operator+=(const Point& p) { x+=p.x; y+=p.y; return *this; }

Point & Point::operator+=(const PointF& p) { x+=round(p.x); y+=round(p.y); return *this; }
Point & Point::operator+=(const Point& p) { x+=p.x; y+=p.y; return *this; }


//minusing
Point Point::operator-(const Point& p) const { return Point(x-p.x, y-p.y); }
Point Point::operator-(const PointF& p) const { return PointF(x-round(p.x), y-round(p.y)); }

Point operator-(const Point& p, const int& i) { return Point(p.x-i, p.y-i); }
//Point operator-(const int& i, const Point& p) { return Point(p.x-i, p.y-i); }

PointF PointF::operator-(const PointF& p) const { return PointF(x-p.x, y-p.y); }
PointF PointF::operator-(const Point& p) const { return PointF(x-p.x, y-p.y); }

PointF operator-(const PointF& p, const double& i) { return PointF(p.x-i, p.y-i); }
//PointF operator-(const double& i, const Point& p) { return PointF(p.x-i, p.y-i); }

PointF & PointF::operator-=(const PointF& p) { x-=p.x; y-=p.y; return *this; }
PointF & PointF::operator-=(const Point& p) { x-=p.x; y-=p.y; return *this; }

Point & Point::operator-=(const PointF& p) { x-=p.x; y-=p.y; return *this; }
Point & Point::operator-=(const Point& p) { x-=p.x; y-=p.y; return *this; }


// in/equality
bool PointF::operator==(const PointF& p) const {return (x == p.x) && (y == p.y);}
bool PointF::operator!=(const PointF& p) const {return (x != p.x) || (y != p.y);}
bool PointF::operator==(const Point& p) const {return (x == p.x) && (y == p.y);}
bool PointF::operator!=(const Point& p) const {return (x != p.x) || (y != p.y);}
bool Point::operator==(const PointF& p) const {return (x == round(p.x)) && (y == round(p.y));}
bool Point::operator!=(const PointF& p) const {return (x != round(p.x)) || (y != round(p.y));}
bool Point::operator==(const Point& p) const {return (x == p.x) && (y == p.y);}
bool Point::operator!=(const Point& p) const {return (x == p.x) || (y == p.y);}

//point is in
bool Point::is_in(const Rect& rect) const { return x>=rect.x && y>=rect.y &&
                                            x < rect.bottomRight().x && y < rect.bottomRight().y;}
