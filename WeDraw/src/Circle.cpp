#include "Circle.h"
#include <cstdlib>
const int precision = 1000;   //圆的精度

void Circle::draw()
{
    config();
    GLfloat R = PPDistance(pArray[0], pArray[1])/2;  //半径
    GLfloat x = (pArray[0].x+pArray[1].x) / 2;  //圆心横坐标
    GLfloat y = (pArray[0].y+pArray[1].y) / 2;  //圆心纵坐标

    //绘制图形
    for (int i = 0; i < 2; i++) {
        glBegin(GL_POLYGON);
        for(int i=0; i < precision; ++i)
            glVertex2f(x+R*cos(2*PI/precision*i),
                       y+R*sin(2*PI/precision*i));
        glEnd();
        if (!conf.frame) break;
        glColor3f(0.0, 0.0, 0.0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    //参考点
    if (!ok) {
        glPointSize(conf.lineSize);
        if (conf.c.R >= 0.90)
            glColor3f(0.0, 0.0, 1.0);
        else
            glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_POINTS);
            glVertex2i(pArray[0].x, pArray[0].y);
        glEnd();
    }
}

void Circle::getRectangle(Point &p1, Point &p2)
{
    GLfloat R = PPDistance(pArray[0], pArray[1])/2;  //半径
    GLfloat x = (pArray[0].x+pArray[1].x) / 2;  //圆心横坐标
    GLfloat y = (pArray[0].y+pArray[1].y) / 2;  //圆心纵坐标
    p1.set(x-R, y+R);
    p2.set(x+R, y-R);
}

void Circle::rotate()
{

}

double Circle::getDistance(int x, int y)
{
    /*********************
     *点与圆心距离d
     *半径r
     * |d-r|
    *********************/
    Point p(x, y);
    double R = PPDistance(pArray[0], pArray[1])/2;
    int px = (pArray[0].x+pArray[1].x) / 2;  //圆心横坐标
    int py = (pArray[0].y+pArray[1].y) / 2;  //圆心纵坐标

    return abs(PPDistance(p, Point(px, py))-R);
}

void Ellipse::draw()
{
    /*****************************
     *椭圆：x^2/a^2 + y^2/b^2 = 1
     *计算出椭圆的a，b
     *表达出x，求出y，保存在vector p里
     *实际x' = p1.x + x
     *实际y* = p2.y + y
     *只需要求1/4椭圆
    ******************************/
    config();
    double a = abs(pArray[0].y-pArray[1].y);
    double b = abs(pArray[0].x-pArray[1].x);


    int x = pArray[0].x;
    int y = pArray[1].y;

    //绘制
    for (int i = 0; i < 2; i++)
    {
        glBegin(GL_POLYGON);
        for(int i=0; i < precision; ++i)
            glVertex2f(x+b*cos(2*PI/precision*i),
                       y+a*sin(2*PI/precision*i));
        glEnd();

        if (!conf.frame) break;
        glColor3f(0.0, 0.0, 0.0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }


    //绘制参考点
    if (!ok) {
        glPointSize(conf.lineSize);
        if (conf.c.R >= 0.90)
            glColor3f(0.0, 0.0, 1.0);
        else
            glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_POINTS);
            glVertex2i(pArray[0].x, pArray[0].y);
        glEnd();
    }
}

void Ellipse::getRectangle(Point &p1, Point &p2)
{
    int x = pArray[0].x;
    int y = pArray[1].y;  //中心坐标
    p1.x = x - abs(pArray[0].x-pArray[1].x);
    p1.y = y + abs(pArray[0].y-pArray[1].y);
    p2.x = x + abs(pArray[0].x-pArray[1].x);
    p2.y = y - abs(pArray[0].y-pArray[1].y);
}

double Ellipse::getDistance(int x, int y)
{
    int px = pArray[0].x;
    int py = pArray[1].y;
    int R = min(abs(pArray[0].y-pArray[1].y), abs(pArray[0].x-pArray[1].x));
    return abs(PPDistance(Point(px,py), Point(x,y))-R);
}



