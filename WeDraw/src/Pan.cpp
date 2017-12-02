#include "Pan.h"

void Pan::draw()
{
    config();
    //ֻ�е�
    if (pArray.size() == 1) {
        glPointSize(conf.lineSize);
        glBegin(GL_POINTS);
            glVertex2i(pArray[0].x, pArray[0].y);
        glEnd();
    }
    //������
    glBegin(GL_LINE_STRIP);
        for (int i = 0; i < pArray.size(); i++)
            glVertex2i(pArray[i].x, pArray[i].y);
    glEnd();
}

void Pan::setPoint(int x, int y)
{
    if (ok) return;
    int last = pArray.size()-1;
    if (pArray.empty()) {
        pArray.push_back(Point(x, y));
        return;
    }
    //�ظ��㣬������
    if (x == pArray[last].x && y == pArray[last].y)
        return;
    pArray.push_back(Point(x, y));
}


void Pan::rotate()
{

}

double Pan::getDistance(int x, int y)
{
    double minVal = 99999999;
    Point p(x, y);
    int gap = pArray.size() / 100 + 1;  //��С������

    for (int i = 0; i < pArray.size(); i += gap) {
        double dis = PPDistance(p, pArray[i]);
        if (dis < minVal)
            minVal = dis;
    }

    return minVal;
}
