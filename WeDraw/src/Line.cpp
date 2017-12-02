#include "Line.h"

void Line::draw()
{
    config();
    glBegin(GL_LINE_STRIP);
        glVertex2i(pArray[0].x, pArray[0].y);
        glVertex2i(pArray[1].x, pArray[1].y);
    glEnd();
}


void Line::rotate()
{
}


double Line::getDistance(int x, int y)
{
    return PLDistance(Point(x, y), pArray[0], pArray[1]);
}


