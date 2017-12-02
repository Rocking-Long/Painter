#ifndef CIRCLE_H
#define CIRCLE_H
#include "Graph.h"

//‘≤
class Circle: public Graph
{
public:
    Circle(int i): Graph(i)
    {
        s = CIRCLE;
    }

    void draw();
    void rotate();
    double getDistance(int x, int y);
    void getRectangle(Point &p1, Point &p2);
};

//Õ÷‘≤
class Ellipse: public Graph
{
public:
    vector<Point> p;

    Ellipse(int i): Graph(i)
    {
        s = ELLIPSE;
        p = vector<Point>(250);
    }

    void draw();
    void getRectangle(Point &, Point &);
};

#endif // CIRCLE_H
