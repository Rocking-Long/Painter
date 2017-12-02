#ifndef LINE_H
#define LINE_H
#include "Graph.h"

/*****************
 *���ڱ�ʾ�߶�
 *������ɱ�ʾ
*****************/
class Line: public Graph
{

public:
    Line(int i): Graph(i)
    {
        s = LINE;
    }

    void draw();
    void rotate();
    double getDistance(int x, int y);
};



#endif // LINE_H
