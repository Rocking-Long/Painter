#include "myPolygon.h"
#include <cmath>
using std::pow;

void myPolygon::draw()
{
    config();
    //只有两个顶点，只能画一条直线
    if (pArray.size() == 2) {
        glBegin(GL_LINE_STRIP);
            glVertex2i(pArray[0].x, pArray[0].y);
            glVertex2i(pArray[1].x, pArray[1].y);
        glEnd();
        return;
    }

    //多个顶点
    for (int i = 0; i < 2; i++) {
        glBegin(GL_POLYGON);
        for (int i = 0; i < pArray.size(); i++)
            glVertex2i(pArray[i].x, pArray[i].y);
        glEnd();
        if (!conf.frame) return;
        glColor3f(0.0, 0.0, 0.0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
}

void myPolygon::setPoint(int x, int y)
{
    if (ok) return;
    //防止另一个点未定义
    if (pArray.empty())
        pArray.push_back(Point(x, y));
    pArray.push_back(Point(x, y));
}


void myPolygon::changePoint(int x, int y)
{
    if (pArray.empty())
        return;
    int last = pArray.size()-1;
    pArray[last].x = x;
    pArray[last].y = y;
}


void myPolygon::drag(const Point &originalPoint, int x, int y)
{
    Point *temp = &pArray[0];
    int minVal = PPDistance(originalPoint, pArray[0]);
    int size = conf.lineSize + 2;

    for (int i = 1; i < pArray.size(); i++)
    {
        double dis = PPDistance(originalPoint, pArray[i]);
        if (dis < minVal) {
            minVal = dis;
            temp = &pArray[i];
        }
    }

    temp->x += x;
    temp->y += y;
}

void myPolygon::rotate()
{

}

double myPolygon::getDistance(int x, int y)
{
    double minVal = 99999999;
    Point p(x, y);
    //p0, p1, ... pn-1
    for (int i = 0; i < pArray.size()-1; i++) {
        double dis = PLDistance(p, pArray[i], pArray[i+1]);
        if (dis < minVal)
            minVal = dis;
    }

    //pn-1, p0
    double dis = PLDistance(p, pArray[0], pArray[pArray.size()-1]);
    if (dis < minVal)
        minVal = dis;

    return minVal;
}


/*********************************************折线**********************************************/
void foldLine::draw()
{
    config();
    for (int i = 0; i < pArray.size()-1; i++) {
        glBegin(GL_LINE_STRIP);
            glVertex2i(pArray[i].x, pArray[i].y);
            glVertex2i(pArray[i+1].x, pArray[i+1].y);
        glEnd();
    }

}


double foldLine::getDistance(int x, int y)
{
    double minVal = 99999999;
    Point p(x, y);
    for (int i = 0; i < pArray.size()-1; i++) {
        double dis = PLDistance(p, pArray[i], pArray[i+1]);
        if (dis < minVal)
            minVal = dis;
    }

    return minVal;
}


void foldLine::rotate()
{

}


////////////////////////////////////////////////////////////////////////////Bezier曲线
void Bezier::setPoint(int x, int y)
{
    if (pArray.size() == 4) {
        ok = true;
        extend = 0;
        return;
    }
    if (ok)
        return;
    //防止另一个点未定义
    if (pArray.empty()) {
        extend = 1;
        pArray.push_back(Point(x, y));
    }

    pArray.push_back(Point(x, y));
}

void Bezier::draw()
{
    config();
    //正在绘制中，或被选择，画出折线
    if (extend == 1)
        for (int i = 0; i < pArray.size()-1; i++) {
            glBegin(GL_LINE_STRIP);
                glVertex2i(pArray[i].x, pArray[i].y);
                glVertex2i(pArray[i+1].x, pArray[i+1].y);
            glEnd();
        }
    //绘制完，可以画出曲线
    if (pArray.size() == 4) {
        Point prePoint;
        prePoint.set(pArray[0]);
        for (double t = 0.0; t<=1.0;t+=0.05)
        {
            Point P;
            double a1 = pow((1-t),3);
            double a2 = pow((1-t),2)*3*t;
            double a3 = 3*t*t*(1-t);
            double a4 = t*t*t;
            P.x = a1*pArray[0].x + a2*pArray[1].x + a3*pArray[2].x + a4*pArray[3].x;
            P.y = a1*pArray[0].y + a2*pArray[1].y + a3*pArray[2].y + a4*pArray[3].y;
            glBegin(GL_LINE_STRIP);
                glVertex2i(prePoint.x, prePoint.y);
                glVertex2i(P.x, P.y);
            glEnd();
            prePoint.set(P);
        }
    }
}

void Bezier::rotate()
{

}












