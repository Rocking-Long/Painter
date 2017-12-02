#ifndef HAPPYDOG_H_INCLUDED
#define HAPPYDOG_H_INCLUDED
#include "Manager.h"


/************************************************************
 *�����������
 *ִ�л滭�ĺ���
 *����Ҫ������Painter
 *��Manager.h��Menu.h���н� Basic -> Graph -> Manager -> HappyDog -> Menu -> main
 *�����Ҫ���ƶ���Ķ�������Ҫ�޸ĸ���
************************************************************/

/*******************************************����������**************************************************/

Manager Painter;  //ȫ�ֹ�����

//ͼ�β���ѡ��
GraphConfig config;
Shape shape = PAN;
Motion myMotion = NO;

//ѡ�񿪹�
bool choose = false; //�Ƿ�ѡ��
int optionID = -1;   //��ѡ���ͼ��ID

//��꿪�أ������ڷ�ֹ�Ҽ�bug
bool mouseLeft  = false;
bool mouseRight = false;


//��Ļ��С
int screenWidth  = 1000;
int screenHeight = 600;

//��߿���
bool openRuler = false;
bool mouseRuler = false;


/*********************************************�滭����********************************************/

void drawRuler()
{
    /********************
     *���Ʊ��
    ********************/
    glLineWidth(1);
    glColor3f(0.0, 0.0, 0.0);
    glDisable(GL_LINE_STIPPLE);
    glBegin(GL_LINE_STRIP);
        glVertex2i(0, screenHeight/2);
        glVertex2i(screenWidth, screenHeight/2);
    glEnd();
    glBegin(GL_LINE_STRIP);
        glVertex2i(screenWidth/2, 0);
        glVertex2i(screenWidth/2, screenHeight);
    glEnd();
}

int mouseX, mouseY;
void drawMouseRuler()
{
    glLineWidth(1);
    glColor3f(0.0, 0.0, 0.0);
    glDisable(GL_LINE_STIPPLE);
    glBegin(GL_LINE_STRIP);
        glVertex2i(mouseX, 0);
        glVertex2i(mouseX, screenHeight);
    glEnd();
    glBegin(GL_LINE_STRIP);
        glVertex2i(0, mouseY);
        glVertex2i(screenWidth, mouseY);
    glEnd();
}

void setMouseXY(int x, int y)
{
    mouseX = x;
    mouseY = y;
}

/******************
 *������ɫ��
******************/

void drawColorDog()
{
    if (myMotion != SETCOLOR)
        return;
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(l1);
    glDisable(GL_LINE_STIPPLE);
    int highMin = screenHeight / 4;
    int highMax = screenHeight * 3 / 4;
    int w = screenWidth / 8;
    glBegin(GL_LINE_STRIP);
        glVertex2i(w, highMin);
        glVertex2i(w, highMax);
    glEnd();
    Painter.cir->draw();
}

void display()
{
    /***************************
     *Ψһ�Ŀ��ƻ滭�ĺ���
     *�ǳ���Ҫ
    ***************************/
    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = 0; i < Painter.size(); i++)
        if (Painter[i] != NULL)
            Painter[i]->draw();

    //�������
    if (Painter.mirror && Painter.m != NULL)
        Painter.m->draw();
    //���
    if (openRuler)
        drawRuler();
    if (mouseRuler)
        drawMouseRuler();
    //ѡ���
    if (choose || myMotion != NO)
        Painter.rec->draw();
    drawColorDog();
    glFlush();
}

#endif // HAPPYDOG_H_INCLUDED
