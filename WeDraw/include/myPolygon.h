#ifndef MYPOLYGON_H
#define MYPOLYGON_H
#include "Graph.h"

class myPolygon: public Graph
{
public:
    myPolygon(int id): Graph(id)
    {
        s = POLYGON;
    }

    void setPoint(int x, int y);
    void changePoint(int x, int y);
    void draw();
    void drag(const Point &originalPoint, int x, int y);
    void rotate();
    double getDistance(int x, int y);

};

/***************’€œﬂ********************/
class foldLine: public myPolygon
{
public:
    foldLine(int id): myPolygon(id)
    {
        s = FOLDLINE;
    }

    void draw();
    double getDistance(int x, int y);
    void rotate();
};

/* «˙œﬂ */
class Bezier: public foldLine
{
public:
    Bezier(int id): foldLine(id)
    {
        s = BEZIER;
    }

    void draw();
    void rotate();
    void setPoint(int x, int y);
};



#endif // MYPOLYGON_H






