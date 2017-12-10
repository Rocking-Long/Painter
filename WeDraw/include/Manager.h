#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include <GL/glut.h>
#include "childGraph.h"
#include "Data.h"
#include <iostream>

using namespace std;


/**
 *  @brief  图形管理类
 *
 *  管理所有的图形，与图形相关的所有操作通过这个类来间接
 *  地调用。该类包含了一个存储所有图形的vector<Graph*>，
 *  还有其他的相关操作需要的数据，如镜像等
 *
 *  如果需要添加一个图形，需要修改该类的
 *    graphName[]
 *    void createGraph()
 *  添加一个动作，需要添加一个函数
 *    void 动作()
 *  该函数要直接操作panel中图形
 */

class Manager
{
public:
    //保存图形的数组
    vector<Graph*> panel;

    //镜像参数
    int mirror = 0;        //镜像绘制
    Graph *m = NULL;       //镜像

    //绘制条
    Graph *cir;
    double a1, b1, c1;    //RGB值的二次函数
    double a2, b2, c2;
    double a3, b3, c3;

    //图形选择参数
    Graph *rec;

    //改变图形大小，记录比例
    Graph *tempRec;           //临时矩形
    Graph *tempPerRec;        //比例数组
    vector<Point> tempArray;  //临时数组

    //清理垃圾参数
    int clearDay;  //清理空指针的周期，用于clearBoy()

    //图形名字
    string graphName[11] = {"画笔", "线段", "三角形", "矩形", "圆形", "多边形", "折线", "正方形", "圆角矩阵", "椭圆", "曲线"};

    //屏幕大小
    int screenWidth;
    int screenHeight;

public:
    Manager();

    /**********Debug**********/
    void check(const string &name, int id, bool ifNull);  //检查非法访问panel，置于图形操作中，非法则输出报告
    void print();  //打印panel情况


    /********获取信息*********/
    unsigned int size();

    Graph* getLast();  //获取panel尾元素

    bool enable();     //是否在绘画中

    bool empty();      //panel是否空

    Graph* operator [](int i);  //重载[]，用于访问panel



    /*********操作图形********/
    void deleteGraph(int id);   //删除图形

    void createGraph(Shape s, const GraphConfig &config);  //创建新图形，包括镜像

    void changePoint(int x, int y);  //动态改变图形顶点

    void setPoint(int x, int y);     //给绘制的图形加入顶点

    void move(int id, int x, int y); //移动图形

    void drag(int id, const Point &p, int x, int y); //拉扯图形

    void setOriginalRec(int id);            //开始形变
    void changeSize(int id, int x, int y);  //改变图形大小
    void changeShape(int id, int x, int y); //改变图形形状

    void setColorFunc(int id);       //计算RGB二次函数
    void colorDog(int id, int y);    //调色条
    int whatColorDog;     //调节什么

    /***********选择图形*************/
    void setRectangle(const Point &p1, const Point &p2);  //绘制包围图形的矩形

    int getNearestGraph(int x, int y);   //求出最近图形的id，并高亮它，恢复前一个被高亮的图形

    void cancelChoose(); //取消选择，复原状态

    /***********读取与保存***********/
    void save();
    void read();


private:
    /************清洁工*************/
    //清理空指针
    void clearBoy();  //上述操作会造成panel含有大量空指针，定期清理

};



#endif // MANAGER_H
