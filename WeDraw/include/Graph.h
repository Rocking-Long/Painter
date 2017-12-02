#ifndef GRAPH_H
#define GRAPH_H

/************************************************
 *Graph��
 *����ͼ�μ̳еĸ���
 *ʵ�����л�������
 *
 *�����Ϊͼ������¹��ܣ���Ҫ�ڸ�������ӣ�����
 *����ͼ������д
************************************************/

#include "Basic.h"
#include "Tool.h"
#include <vector>
#include <iostream>
#include <GL/glut.h>
using namespace std;


class Graph
{
    /**********************
     *��Ψһ��ʶһ��ͼ�ε�id
     *ͼ�ε���״s��ʹ��ö������
     *��ͼ���Ƿ����ú�
     *��ͼ�εĵ㼯
     *ͼ�εĲ���
    ***********************/
public:
    int id;    //ͼ��id
    Shape s;   //��״
    bool ok;   //ͼ���Ƿ�������
    GraphConfig conf;  //��������
    vector<Point> pArray;  //�㼯

public:
    Graph(int i): id(i), s(LINE), ok(false) {}
    ~Graph() {}


    //������������
    bool finish();                          //���ƽ���
    void setColor(const Color &col);        //������ɫ
    void setLineSize(LineSize lineSize);    //���ô�ϸ
    void setDash(bool isDashes);            //��������
    void setpolymode(bool isfilled);        //�������
    void setConfig(const GraphConfig &config);  //��������

    //������
    virtual void setPoint(int x, int y);     //���붥�㣬���ڻ���
    virtual void changePoint(int x, int y);  //�޸Ķ��㣬���ڻ����붯��
    virtual double getDistance(int x, int y){} //�������ͼ��ľ��룬�������ѡ��

    virtual void copy(Graph*);   //�����Լ������ھ���


    //ͼ�ζ���
    virtual void draw() = 0;   //���Ƹ�ͼ��
    void move(int, int);   //λ��
    virtual void rotate() {};   //��ת
    virtual void drag(const Point &originalPoint, int x, int y);  //����
    virtual void getRectangle(Point &, Point &);

protected:
    //����
    void config();
};



#endif // GRAPH_H
