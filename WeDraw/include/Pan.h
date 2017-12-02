#ifndef PAN_H
#define PAN_H
#include "Graph.h"

class Pan: public Graph
{
public:
    Pan(int id): Graph(id)
    {
        s = PAN;
    }


    void setPoint(int x, int y);
    void draw();
    void rotate();
    double getDistance(int x, int y);
};
#endif // PAN_H
