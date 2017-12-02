#include "Tool.h"
#include <iostream>
using namespace std;

/**********************************************
 *工具箱
 *求两点距离
 *求点与线段距离
 *交换两点
**********************************************/

inline double PPDistance(const Point &p1, const Point &p2)
{
    /***********************
     *计算线两点距离
    ***********************/
    return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
}


double PLDistance(const Point &p, const Point &begin, const Point &end)
{
    /**********************
     *计算点到线段的距离
    **********************/
    Point b;
    Point e;

    //获取b和e的位置
    //------------------------------------------
    //垂线段
    if (begin.x == end.x) {
        //b在e上方
        if (begin.y > end.y) {
            b.set(begin);
            e.set(end);
        }
        else {
            e.set(begin);
            b.set(end);
        }
    }
    //平行线段与斜线段
    else {
        //b在e左侧
        if (begin.x < end.x) {
            b.set(begin);
            e.set(end);
        }
        else {
            b.set(end);
            e.set(begin);
        }
    }


    //点与线段距离
    //-------------------------------------------
    //首先计算在线段垂线范围内-------------------
    //垂线段
    if (b.x == e.x) {
        if (p.y <= b.y && p.y >= e.y)
            return abs(p.x-b.x);
    }
    //平行线段
    else if (b.y == e.y) {
        if (p.x >= b.x && p.x <= e.x)
            return abs(p.y-b.y);
    }
    //斜线段
    else {
        double k = 1.0*(b.y-e.y) / (b.x-e.x);  //线段斜率
        double vk = -1.0 / k;                  //垂线段斜率
        double c  = b.y - k  * b.x;      //线段    y = k*x + c
        double c1 = b.y - vk * b.x;      //垂线段1 y = vk*x + c1
        double c2 = e.y - vk * e.x;      //垂线段2 y = vk*x + c2

/*cout << "y = " << k << "*x + " <<  c << '\n';
cout << "y = " << vk << "*x + " <<  c1 << '\n';
cout << "y = " << vk << "*x + " <<  c2 << '\n';*/

        //当线段斜率大于0
        if (k > 0) {
            if (p.y >= vk*p.x+c1 && p.y <= vk*p.x+c2) {
                //计算p与直线相连的直线的方程 y = vk + c3
                double c3 = p.y - vk * p.x;
                //计算该直线与原线段交点 kx + c == vkx + c3
                int x = (c3-c) / (k-vk);
                int y = k*x + c;
                return PPDistance(p, Point(x, y));
            }
        }
        //线段斜率小于0
        else {
            if (p.y <= vk*p.x+c1 && p.y >= vk*p.x+c2) {
                //计算p与直线相连的直线的方程 y = vk + c3
                double c3 = p.y - vk * p.x;
                //计算该直线与原线段交点 kx + c == vkx + c3
                int x = (c3-c) / (k-vk);
                int y = k*x + c;
                return PPDistance(p, Point(x, y));
            }

        }

    }

    //不在线段垂线范围内
    return min(PPDistance(p, b), PPDistance(p, e));
}

void swapPoint(Point &p1, Point &p2)
{
    int temp = p1.x;
    p1.x = p2.x;
    p2.x = temp;
    temp = p1.y;
    p1.y = p2.y;
    p2.y = temp;
}

void highLightPoint(const Point &p, int size)
{
    glPointSize(size);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
        glVertex2i(p.x, p.y);
    glEnd();
}


