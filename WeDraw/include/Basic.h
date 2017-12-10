#ifndef BASIC_H_INCLUDED
#define BASIC_H_INCLUDED

#include <GL/glut.h>
#include <string>
/*******************************************
 *Point  点类
 *Color  颜色类
 *Shape  形状枚举
 *Motion 图形操作动作
 *LineSize  粗细枚举
 *Config  图形参数结构体
*******************************************/


class Point
{
    /******************
     *点的数据结构
     *用x和y坐标表示
     *最基本的数据
    ******************/
public:
    int x;
    int y;

public:
    //点初始化为-1
    //便于判断一个点是否已经被赋值
    Point():x(-1), y(-1) {}

    Point(int a, int b):
        x(a), y(b) {}

    void set(int a, int b) {
        x = a;
        y = b;
    }

    void set(const Point &p) {
        x = p.x;
        y = p.y;
    }

};


class Color
{
    /**********************
     *颜色类
     *使用RGB值来表示颜色
     *所有图形具有该数据
    **********************/
public:
    GLfloat R;
    GLfloat G;
    GLfloat B;

public:
    Color():R(0.0), B(0.0), G(0.0)
        {}

    Color(GLfloat r, GLfloat g, GLfloat b)
    {
        R = r;
        G = g;
        B = b;
    }

    Color(const Color &c)
    {
        set(c);
    }

    void set(const Color &c)
    {
        R = c.R;
        G = c.G;
        B = c.B;
    }
};



enum Shape
{
    /*********************
     *表示图形的枚举类型
     *用于表示是什么图形
     *否则所有图形继承Graph
     *无法辨认
    *********************/
    PAN,       //画笔
    LINE,      //线段
    TRIANGLE,  //三角形
    RECTANGLE, //矩形
    CIRCLE,    //圆
    POLYGON,   //多边形
    FOLDLINE,  //折线
    SQUARE,    //正方形
    CRECTANGLE, //圆角矩形
    ELLIPSE,    //椭圆
    BEZIER      //三次Bezier曲线
};


enum Motion
{
    /*******************
     *图形操作动作
    *******************/
    NO,     //没有操作
    MOVING, //平移
    DRAG,   //拖拉
    ROTATE, //旋转
    SCHANGE,  //大小形变
    RCHANGE,  //矩形形变
    SETCOLOR  //色条
};


enum LineSize
{
    /****************
     *线粗细
    ****************/
    l1 = 1,
    l2 = 2,
    l3 = 3,
    l4 = 5,
    l5 = 8
};


struct GraphConfig
{
    /******************
     *图形基本参数
    ******************/
    Color c;
    LineSize lineSize = l3;  //线粗细
    bool isDashes = false;   //是否虚线
    bool isFilled = false;
    bool frame = false;
};

#endif // BASIC_H_INCLUDED
