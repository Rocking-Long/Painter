#ifndef TOOL_H
#define TOOL_H

/*******************************************
 *������
 *ʵ�ֳ��ú���
********************************************/


#include "Basic.h"
#include <cmath>
#include <vector>
#include <GL/glut.h>
using namespace std;

const double PI = 3.1415926536;

//�������
inline double PPDistance(const Point &p1, const Point &p2);

//���߾���
double PLDistance(const Point &p, const Point &begin, const Point &end);

//��������ֵ
void swapPoint(Point &p1, Point &p2);

//����ĳ�㡪����ʱ����
void highLightPoint(const Point &p, int size);


#endif // TOOL_H
