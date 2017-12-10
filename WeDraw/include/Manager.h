#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include <GL/glut.h>
#include "childGraph.h"
#include "Data.h"
#include <iostream>

using namespace std;


/**
 *  @brief  ͼ�ι�����
 *
 *  �������е�ͼ�Σ���ͼ����ص����в���ͨ������������
 *  �ص��á����������һ���洢����ͼ�ε�vector<Graph*>��
 *  ������������ز�����Ҫ�����ݣ��羵���
 *
 *  �����Ҫ���һ��ͼ�Σ���Ҫ�޸ĸ����
 *    graphName[]
 *    void createGraph()
 *  ���һ����������Ҫ���һ������
 *    void ����()
 *  �ú���Ҫֱ�Ӳ���panel��ͼ��
 */

class Manager
{
public:
    //����ͼ�ε�����
    vector<Graph*> panel;

    //�������
    int mirror = 0;        //�������
    Graph *m = NULL;       //����

    //������
    Graph *cir;
    double a1, b1, c1;    //RGBֵ�Ķ��κ���
    double a2, b2, c2;
    double a3, b3, c3;

    //ͼ��ѡ�����
    Graph *rec;

    //�ı�ͼ�δ�С����¼����
    Graph *tempRec;           //��ʱ����
    Graph *tempPerRec;        //��������
    vector<Point> tempArray;  //��ʱ����

    //������������
    int clearDay;  //�����ָ������ڣ�����clearBoy()

    //ͼ������
    string graphName[11] = {"����", "�߶�", "������", "����", "Բ��", "�����", "����", "������", "Բ�Ǿ���", "��Բ", "����"};

    //��Ļ��С
    int screenWidth;
    int screenHeight;

public:
    Manager();

    /**********Debug**********/
    void check(const string &name, int id, bool ifNull);  //���Ƿ�����panel������ͼ�β����У��Ƿ����������
    void print();  //��ӡpanel���


    /********��ȡ��Ϣ*********/
    unsigned int size();

    Graph* getLast();  //��ȡpanelβԪ��

    bool enable();     //�Ƿ��ڻ滭��

    bool empty();      //panel�Ƿ��

    Graph* operator [](int i);  //����[]�����ڷ���panel



    /*********����ͼ��********/
    void deleteGraph(int id);   //ɾ��ͼ��

    void createGraph(Shape s, const GraphConfig &config);  //������ͼ�Σ���������

    void changePoint(int x, int y);  //��̬�ı�ͼ�ζ���

    void setPoint(int x, int y);     //�����Ƶ�ͼ�μ��붥��

    void move(int id, int x, int y); //�ƶ�ͼ��

    void drag(int id, const Point &p, int x, int y); //����ͼ��

    void setOriginalRec(int id);            //��ʼ�α�
    void changeSize(int id, int x, int y);  //�ı�ͼ�δ�С
    void changeShape(int id, int x, int y); //�ı�ͼ����״

    void setColorFunc(int id);       //����RGB���κ���
    void colorDog(int id, int y);    //��ɫ��
    int whatColorDog;     //����ʲô

    /***********ѡ��ͼ��*************/
    void setRectangle(const Point &p1, const Point &p2);  //���ư�Χͼ�εľ���

    int getNearestGraph(int x, int y);   //������ͼ�ε�id�������������ָ�ǰһ����������ͼ��

    void cancelChoose(); //ȡ��ѡ�񣬸�ԭ״̬

    /***********��ȡ�뱣��***********/
    void save();
    void read();


private:
    /************��๤*************/
    //�����ָ��
    void clearBoy();  //�������������panel���д�����ָ�룬��������

};



#endif // MANAGER_H
