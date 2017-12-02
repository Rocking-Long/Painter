#ifndef LINE_H
#define LINE_H
#include "Graph.h"

/*****************
 *用于表示线段
 *两个点可表示
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
