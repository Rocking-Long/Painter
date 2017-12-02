#ifndef TOOL_H
#define TOOL_H

/*******************************************
 *工具类
 *实现常用函数
********************************************/


#include "Basic.h"
#include <cmath>
#include <vector>
#include <GL/glut.h>
using namespace std;

const double PI = 3.1415926536;

//两点距离
inline double PPDistance(const Point &p1, const Point &p2);

//点线距离
double PLDistance(const Point &p, const Point &begin, const Point &end);

//交换两点值
void swapPoint(Point &p1, Point &p2);

//高亮某点——暂时无用
void highLightPoint(const Point &p, int size);


#endif // TOOL_H
