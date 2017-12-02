#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Graph.h"

/***********************
 *������
***********************/
class Triangle: public Graph
{
public:
    Triangle(int id): Graph(id)
    {
        s = TRIANGLE;
    }

    void changPoint(int x, int y);
    void setPoint(int x, int y);
    void draw();
    void drag(const Point &originalPoint, int x, int y);
    void rotate();
    double getDistance(int x, int y);
};

/************************
 *����������
************************/
class ETriangle: public Triangle
{

};

#endif // TRIANGLE_H
