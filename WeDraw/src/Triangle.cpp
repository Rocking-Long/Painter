#include "Triangle.h"

void Triangle::draw()
{
    config();
    //完整三角形
    if (pArray.size()==3)
    {
        for (int i = 0; i < 2; i++) {
            glBegin(GL_POLYGON);
                glVertex2i(pArray[0].x, pArray[0].y);
                glVertex2i(pArray[1].x, pArray[1].y);
                glVertex2i(pArray[2].x, pArray[2].y);
            glEnd();
            if (!conf.frame) return;
            glColor3f(0.0, 0.0, 0.0);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
    }
    //只有线段(画到一半)
    else if(pArray.size()==2) {
        glBegin(GL_LINE_STRIP);
            glVertex2i(pArray[0].x, pArray[0].y);
            glVertex2i(pArray[1].x, pArray[1].y);
        glEnd();
    }
}

void Triangle::setPoint(int x, int y)
{
    if (pArray.empty())
        pArray = vector<Point>(2, Point(x, y));
    else if (pArray.size() == 2) {
        pArray[1].x = x;
        pArray[1].y = y;
        pArray.push_back(Point(x, y));
    }
    else
        ok = true;
}

void Triangle::changPoint(int x, int y)
{
    if (pArray.size() == 2) {
        pArray[1].x = x;
        pArray[1].y = y;
    }
    else {
        pArray[2].x = x;
        pArray[2].y = y;
    }
}



void Triangle::drag(const Point &originalPoint, int x, int y)
{
    double dis1 = PPDistance(originalPoint, pArray[0]);
    double dis2 = PPDistance(originalPoint, pArray[1]);
    double dis3 = PPDistance(originalPoint, pArray[2]);
    int size = conf.lineSize + 2;
    //选择最近点进行拉扯
    if (dis1 < dis2 && dis1 < dis3) {
        pArray[0].x += x;
        pArray[0].y += y;
    }
    else if (dis2 < dis1 && dis2 < dis3){
        pArray[1].x += x;
        pArray[1].y += y;
    }
    else {
        pArray[2].x += x;
        pArray[2].y += y;
    }
}

void Triangle::rotate()
{

}

double Triangle::getDistance(int x, int y)
{
    /**********************
     *离三条边最小距离
    **********************/
    Point p(x, y);
    double dis1 = PLDistance(p, pArray[0], pArray[1]);
    double dis2 = PLDistance(p, pArray[1], pArray[2]);
    double dis3 = PLDistance(p, pArray[0], pArray[2]);

    return min(dis1, min(dis1, dis3));
}

