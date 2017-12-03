#include "myRectangle.h"

void myRectangle::draw()
{
    config();
    for (int i = 0; i < 2; i++) {
        glBegin(GL_POLYGON);
            glVertex2i(pArray[0].x, pArray[0].y);
            glVertex2i(pArray[1].x, pArray[1].y);
            glVertex2i(pArray[2].x, pArray[2].y);
            glVertex2i(pArray[3].x, pArray[3].y);
        glEnd();
        if (!conf.frame) return;
        glColor3f(0.0, 0.0, 0.0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
}


void myRectangle::drag(const Point &originalPoint, int x, int y)
{
    double dis1 = PLDistance(originalPoint, pArray[0], pArray[1]);
    double dis2 = PLDistance(originalPoint, pArray[2], pArray[3]);
    int size = conf.lineSize + 2;
    //选择最近点进行拉扯
    if (dis1 < dis2) {
        pArray[0].x += x;
        pArray[0].y += y;
        pArray[1].x += x;
        pArray[1].y += y;
    }
    else {
        pArray[2].x += x;
        pArray[2].y += y;
        pArray[3].x += x;
        pArray[3].y += y;
    }
}

void myRectangle::rotate()
{

}

void myRectangle::setPoint(int x, int y)
{
    if (pArray.empty()) {
        pArray = vector<Point>(4, Point(x, y));
        pArray[1].x = pArray[2].x += 1;
        pArray[2].y = pArray[3].y -= 1;
    }
    else {
        ok = true;
    }
}

void myRectangle::changePoint(int x, int y)
{
    pArray[2].set(x, y);
    pArray[1].set(x, pArray[0].y);
    pArray[3].set(pArray[0].x, y);
}


double myRectangle::getDistance(int x, int y)
{
    /*****************
     *四条边最小距离
    *****************/
    Point p(x, y);
    Point p00(pArray[0]);
    Point p11(pArray[2]);
    Point p10(p00.x, p11.y);
    Point p01(p11.x, p00.y);

    double dis1 = PLDistance(p, p00, p01);
    double dis2 = PLDistance(p, p01, p11);
    double dis3 = PLDistance(p, p11, p10);
    double dis4 = PLDistance(p, p10, p00);

    return min(dis1, min(dis2, min(dis3,dis4)));
}

void Square::setPoint(int x, int y)
{
    if (pArray.empty()) {
        pArray = vector<Point>(4, Point(x, y));
    }
    else {
        int length = abs(pArray[0].x-x);
        if (y < pArray[0].y)
            pArray[2].set(x, pArray[0].y-length);
        else
            pArray[2].set(x, pArray[0].y+length);
        pArray[1].set(pArray[2].x, pArray[0].y);
        pArray[3].set(pArray[0].x, pArray[2].y);
        ok = true;
    }
}


void Square::changePoint(int x, int y)
{
    int length = abs(pArray[0].x-x);
    if (y < pArray[0].y)
        pArray[2].set(x, pArray[0].y-length);
    else
        pArray[2].set(x, pArray[0].y+length);
    pArray[1].set(pArray[2].x, pArray[0].y);
    pArray[3].set(pArray[0].x, pArray[2].y);
}


void CRectangle::draw()
{
    static const int subPrecision = 250;
    config();

    GLfloat R = PPDistance(pArray[0], pArray[2]) / 8;  //半径
    if (R > 15)
        R = 15;

    //取左上角和右下角的顶点
    Point p1, p2;
    p1.set(pArray[0]);
    p2.set(pArray[2]);
    if (p1.x > p2.x && p1.y > p2.y) {
        p1.set(pArray[1]);
        p2.set(pArray[3]);
    }
    else if (p1.x < p2.x && p1.y < p2.y) {
        p1.set(pArray[3]);
        p2.set(pArray[1]);
    }
    else if (p1.x > p2.x && p1.y < p2.y) {
        swapPoint(p1, p2);
    }

    //4个四分之一圆的圆心
    GLfloat x1 = p1.x+R;
    GLfloat y1 = p1.y-R;
    GLfloat x2 = p2.x-R;
    GLfloat y2 = p2.y+R;

    //绘制
    for (int i = 0; i < 2; i++) {
        glBegin(GL_POLYGON);
            glVertex2i(p2.x, y2);
            glVertex2i(p2.x, y1);
            for(int i=0; i < subPrecision; ++i)
            {
               glVertex2f(x2+R*cos(0.5*PI/subPrecision*i),
                           y1+R*sin(0.5*PI/subPrecision*i));
            }

            glVertex2i(x2, p1.y);
            glVertex2i(x1, p1.y);
            for(int i=subPrecision; i < 2*subPrecision; ++i)
            {
                 glVertex2f(x1+R*cos(0.5*PI/subPrecision*i),
                           y1+R*sin(0.5*PI/subPrecision*i));
            }

            glVertex2i(p1.x, y1);
            glVertex2i(p1.x, y2);
            for(int i=2*subPrecision; i < 3*subPrecision; ++i)
            {
                glVertex2f(x1+R*cos(0.5*PI/subPrecision*i),
                           y2+R*sin(0.5*PI/subPrecision*i));
            }

            glVertex2i(x1, p2.y);
            glVertex2i(x2, p2.y);
            for(int i=3*subPrecision; i < 4*subPrecision; ++i)
            {
                glVertex2f(x2+R*cos(0.5*PI/subPrecision*i),
                           y2+R*sin(0.5*PI/subPrecision*i));
            }
        glEnd();
        if (!conf.frame) return;
        glColor3f(0.0, 0.0, 0.0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

}
