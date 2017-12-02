#ifndef HAPPYDOG_H_INCLUDED
#define HAPPYDOG_H_INCLUDED
#include "Manager.h"


/************************************************************
 *保存操作开关
 *执行绘画的函数
 *最重要的数据Painter
 *是Manager.h和Menu.h的中介 Basic -> Graph -> Manager -> HappyDog -> Menu -> main
 *如果需要绘制额外的东西，需要修改该类
************************************************************/

/*******************************************开关与数据**************************************************/

Manager Painter;  //全局管理者

//图形参数选择
GraphConfig config;
Shape shape = PAN;
Motion myMotion = NO;

//选择开关
bool choose = false; //是否被选择
int optionID = -1;   //被选择的图形ID

//鼠标开关，仅用于防止右键bug
bool mouseLeft  = false;
bool mouseRight = false;


//屏幕大小
int screenWidth  = 1000;
int screenHeight = 600;

//标尺开关
bool openRuler = false;
bool mouseRuler = false;


/*********************************************绘画函数********************************************/

void drawRuler()
{
    /********************
     *绘制标尺
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
 *绘制颜色条
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
     *唯一的控制绘画的函数
     *非常重要
    ***************************/
    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = 0; i < Painter.size(); i++)
        if (Painter[i] != NULL)
            Painter[i]->draw();

    //镜像绘制
    if (Painter.mirror && Painter.m != NULL)
        Painter.m->draw();
    //标尺
    if (openRuler)
        drawRuler();
    if (mouseRuler)
        drawMouseRuler();
    //选择框
    if (choose || myMotion != NO)
        Painter.rec->draw();
    drawColorDog();
    glFlush();
}

#endif // HAPPYDOG_H_INCLUDED
