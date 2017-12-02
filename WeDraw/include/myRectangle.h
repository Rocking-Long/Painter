#ifndef MYRECTANGLE_H
#define MYRECTANGLE_H
#include "Graph.h"

/************************
 *���ڱ�ʾ����
*************************/
class myRectangle: public Graph
{
public:
    myRectangle(int i): Graph(i)
    {
        s = RECTANGLE;
    }

    void setPoint(int x, int y);
    void changePoint(int x, int y);
    void draw();
    void drag(const Point &originalPoint, int x, int y);
    void rotate();
    double getDistance(int x, int y);
};

/**********************
 *������
**********************/
class Square: public myRectangle
{
public:
    Square(int i): myRectangle(i)
    {
        s = SQUARE;
    }

    void setPoint(int x, int y);
    void changePoint(int x, int y);
};

/**********************
 *Բ�Ǿ���
**********************/
class CRectangle: public myRectangle
{
public:
    CRectangle(int id): myRectangle(id)
    {
        s = CRECTANGLE;
    }

    void draw();
};

#endif // MYRECTANGLE_H
