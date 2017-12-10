#include "Circle.h"
#include <cstdlib>
const int precision = 1000;   //Բ�ľ���

void Circle::draw()
{
    config();
    GLfloat R = PPDistance(pArray[0], pArray[1])/2;  //�뾶
    GLfloat x = (pArray[0].x+pArray[1].x) / 2;  //Բ�ĺ�����
    GLfloat y = (pArray[0].y+pArray[1].y) / 2;  //Բ��������

    //����ͼ��
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

    //�ο���
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
    GLfloat R = PPDistance(pArray[0], pArray[1])/2;  //�뾶
    GLfloat x = (pArray[0].x+pArray[1].x) / 2;  //Բ�ĺ�����
    GLfloat y = (pArray[0].y+pArray[1].y) / 2;  //Բ��������
    p1.set(x-R, y+R);
    p2.set(x+R, y-R);
}

void Circle::rotate()
{

}

double Circle::getDistance(int x, int y)
{
    /*********************
     *����Բ�ľ���d
     *�뾶r
     * |d-r|
    *********************/
    Point p(x, y);
    double R = PPDistance(pArray[0], pArray[1])/2;
    int px = (pArray[0].x+pArray[1].x) / 2;  //Բ�ĺ�����
    int py = (pArray[0].y+pArray[1].y) / 2;  //Բ��������

    return abs(PPDistance(p, Point(px, py))-R);
}

void Ellipse::draw()
{
    /*****************************
     *��Բ��x^2/a^2 + y^2/b^2 = 1
     *�������Բ��a��b
     *����x�����y��������vector p��
     *ʵ��x' = p1.x + x
     *ʵ��y* = p2.y + y
     *ֻ��Ҫ��1/4��Բ
    ******************************/
    config();
    double a = abs(pArray[0].y-pArray[1].y);
    double b = abs(pArray[0].x-pArray[1].x);


    int x = pArray[0].x;
    int y = pArray[1].y;

    //����
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


    //���Ʋο���
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
    int y = pArray[1].y;  //��������
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



