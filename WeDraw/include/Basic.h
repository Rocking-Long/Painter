#ifndef BASIC_H_INCLUDED
#define BASIC_H_INCLUDED

#include <GL/glut.h>
#include <string>
/*******************************************
 *Point  ����
 *Color  ��ɫ��
 *Shape  ��״ö��
 *Motion ͼ�β�������
 *LineSize  ��ϸö��
 *Config  ͼ�β����ṹ��
*******************************************/


class Point
{
    /******************
     *������ݽṹ
     *��x��y�����ʾ
     *�����������
    ******************/
public:
    int x;
    int y;

public:
    //���ʼ��Ϊ-1
    //�����ж�һ�����Ƿ��Ѿ�����ֵ
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
     *��ɫ��
     *ʹ��RGBֵ����ʾ��ɫ
     *����ͼ�ξ��и�����
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
     *��ʾͼ�ε�ö������
     *���ڱ�ʾ��ʲôͼ��
     *��������ͼ�μ̳�Graph
     *�޷�����
    *********************/
    PAN,       //����
    LINE,      //�߶�
    TRIANGLE,  //������
    RECTANGLE, //����
    CIRCLE,    //Բ
    POLYGON,   //�����
    FOLDLINE,  //����
    SQUARE,    //������
    CRECTANGLE, //Բ�Ǿ���
    ELLIPSE,    //��Բ
    BEZIER      //����Bezier����
};


enum Motion
{
    /*******************
     *ͼ�β�������
    *******************/
    NO,     //û�в���
    MOVING, //ƽ��
    DRAG,   //����
    ROTATE, //��ת
    SCHANGE,  //��С�α�
    RCHANGE,  //�����α�
    SETCOLOR  //ɫ��
};


enum LineSize
{
    /****************
     *�ߴ�ϸ
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
     *ͼ�λ�������
    ******************/
    Color c;
    LineSize lineSize = l3;  //�ߴ�ϸ
    bool isDashes = false;   //�Ƿ�����
    bool isFilled = false;
    bool frame = false;
};

#endif // BASIC_H_INCLUDED
