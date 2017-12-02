#include "Tool.h"
#include <iostream>
using namespace std;

/**********************************************
 *������
 *���������
 *������߶ξ���
 *��������
**********************************************/

inline double PPDistance(const Point &p1, const Point &p2)
{
    /***********************
     *�������������
    ***********************/
    return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
}


double PLDistance(const Point &p, const Point &begin, const Point &end)
{
    /**********************
     *����㵽�߶εľ���
    **********************/
    Point b;
    Point e;

    //��ȡb��e��λ��
    //------------------------------------------
    //���߶�
    if (begin.x == end.x) {
        //b��e�Ϸ�
        if (begin.y > end.y) {
            b.set(begin);
            e.set(end);
        }
        else {
            e.set(begin);
            b.set(end);
        }
    }
    //ƽ���߶���б�߶�
    else {
        //b��e���
        if (begin.x < end.x) {
            b.set(begin);
            e.set(end);
        }
        else {
            b.set(end);
            e.set(begin);
        }
    }


    //�����߶ξ���
    //-------------------------------------------
    //���ȼ������߶δ��߷�Χ��-------------------
    //���߶�
    if (b.x == e.x) {
        if (p.y <= b.y && p.y >= e.y)
            return abs(p.x-b.x);
    }
    //ƽ���߶�
    else if (b.y == e.y) {
        if (p.x >= b.x && p.x <= e.x)
            return abs(p.y-b.y);
    }
    //б�߶�
    else {
        double k = 1.0*(b.y-e.y) / (b.x-e.x);  //�߶�б��
        double vk = -1.0 / k;                  //���߶�б��
        double c  = b.y - k  * b.x;      //�߶�    y = k*x + c
        double c1 = b.y - vk * b.x;      //���߶�1 y = vk*x + c1
        double c2 = e.y - vk * e.x;      //���߶�2 y = vk*x + c2

/*cout << "y = " << k << "*x + " <<  c << '\n';
cout << "y = " << vk << "*x + " <<  c1 << '\n';
cout << "y = " << vk << "*x + " <<  c2 << '\n';*/

        //���߶�б�ʴ���0
        if (k > 0) {
            if (p.y >= vk*p.x+c1 && p.y <= vk*p.x+c2) {
                //����p��ֱ��������ֱ�ߵķ��� y = vk + c3
                double c3 = p.y - vk * p.x;
                //�����ֱ����ԭ�߶ν��� kx + c == vkx + c3
                int x = (c3-c) / (k-vk);
                int y = k*x + c;
                return PPDistance(p, Point(x, y));
            }
        }
        //�߶�б��С��0
        else {
            if (p.y <= vk*p.x+c1 && p.y >= vk*p.x+c2) {
                //����p��ֱ��������ֱ�ߵķ��� y = vk + c3
                double c3 = p.y - vk * p.x;
                //�����ֱ����ԭ�߶ν��� kx + c == vkx + c3
                int x = (c3-c) / (k-vk);
                int y = k*x + c;
                return PPDistance(p, Point(x, y));
            }

        }

    }

    //�����߶δ��߷�Χ��
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


