#include <windows.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#include "Menu.h"
using namespace std;

/******************************************全局数据*********************************************/
//注释数据在HappyDog.h里
//GraphConfig config;   图形基本参数
//Shape shape = LINE;   图形类别
//bool choose = false;  是否选择

//鼠标操作，防止bug，没有更多作用
//bool mouseLeft  = false;  //在Menu中
//bool mouseRight = false;

//图形操作
//int optionID = -1;  //被选择的图形  Menu.h
Point origalMoving;   //位移原点

//窗口大小，在Manager.h
//int screenWidth  = 1000;
//int screenHeight = 600;


/******************************************控制函数********************************************/


void init(void)
{
    /******************
     *初始化
    ******************/
    glClearColor(1.0,1.0,1.0,1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);
}


void mouse(int button, int state, int x, int y)
{
    /*********************************
     *监视鼠标事件
     *检测鼠标左键
     *摁下时，被绘画图形增加一个顶点
     *或者进行动作
     *松开时，完成动作或绘画
    *********************************/

    int sy = screenHeight-y;
    //鼠标标尺
    if (mouseRuler)
        setMouseXY(x, sy);
    //左键
    if(button == GLUT_LEFT_BUTTON)
    {
        mouseLeft  = true;
        mouseRight = false;

        /******************************
         *左键摁下操作
         *图形选择，操作
         *图形绘制
        *******************************/
        if(state == GLUT_DOWN)
        {
            //图形选择
            //---------------------------------
            if (choose)
            {
                //无动作
                if (myMotion == NO) {
                    optionID = Painter.getNearestGraph(x, sy);
                    if (optionID == -1) return;
                }
                //平移
                else if (myMotion == MOVING || myMotion == DRAG) {
                    origalMoving.set(x, sy);
                }
                //大小形变
                else if (myMotion == SCHANGE || myMotion == RCHANGE) {
                    origalMoving.set(x, sy);
                    Painter.setOriginalRec(optionID);
                }
                else if (myMotion == SETCOLOR) {
                    origalMoving.set(x, sy);
                }

                display();
                return;  //结束
            }

            //图形绘制
            //-----------------------------------
            Painter.createGraph(shape, config);  //如果需要创建新图形，则创建
            Painter.setPoint(x, sy); //加入新绘制的顶点
            //镜像
                if (Painter.mirror)
                {
                    int mx, my;
                    switch (Painter.mirror) {
                        case 1: mx = screenWidth-x; my = sy; break;
                        case 2: mx = x; my = screenHeight - sy; break;
                        case 3: mx = screenWidth-x; my = screenHeight-sy; break;
                    }
                    Painter.m->setPoint(mx, my);
                    if (Painter.getLast()->finish()) {
                        //结束绘制镜像
                        Painter.panel.push_back(Painter.m);
                        Painter.m = NULL;
                    }

                }

            display();
        }

        /*****************************
         *左键松开操作
         *画笔完成
         *图形操作
        *****************************/
        else if (state == GLUT_UP)
        {
            if (Painter.empty())
                return;
            //图形操作，完成
            if (choose && optionID != -1)
            {
                //pass
            }
            //画笔操作，完成绘制
            else if (shape == PAN)
            {
                mouseRight = true;  //防止右键绘画
                Painter.setPoint(x, sy);
                Painter.getLast()->ok = true;
                    //镜像
                    if (Painter.mirror)
                    {
                        int mx, my;
                        switch (Painter.mirror) {
                            case 1: mx = screenWidth-x; my = sy; break;
                            case 2: mx = x; my = screenHeight - sy; break;
                            case 3: mx = screenWidth-x; my = screenHeight-sy; break;
                        }
                        //结束绘制镜像
                        Painter.m->setPoint(mx, my);
                        Painter.m->ok = true;
                        Painter.panel.push_back(Painter.m);
                        Painter.m = NULL;
                    }
            }
            display();
            mouseRight = true;
        }
    }

    /***********************
     *右键操作
     *可能非法
     *做好防范
    ***********************/
    else {
        mouseLeft  = false;
        mouseRight = true;
    }

}


void passiveMotion(int x, int y)
{
    /*************************************
     *监视松开鼠标后的动作
     *改变正在绘画的图形的被画点的坐标
    *************************************/
    int sy = screenHeight - y;
    //鼠标标尺
    if (mouseRuler)
        setMouseXY(x, sy);


    //没有图形正在绘画，不需要调用此
    if (!Painter.enable() || shape == PAN) {
        if (mouseRuler)
            display();
        return;
    }

    //有图形正在绘画中，修改被绘画点的坐标
    Painter.changePoint(x, sy);
        //镜像
        if (Painter.mirror)
        {
            int mx, my;
            switch (Painter.mirror) {
                case 1: mx = screenWidth-x; my = sy; break;
                case 2: mx = x; my = screenHeight - sy; break;
                case 3: mx = screenWidth-x; my = screenHeight-sy; break;
            }
            Painter.m->changePoint(mx, my);
        }
    display();
}


void motion(int x, int y)
{
    /**********************************
     *鼠标按住事件
     *用于画笔绘图和图像操作
    **********************************/
    if ((shape!=PAN && !choose) || mouseRight || Painter.empty())
        return;

    //鼠标标尺
    if (mouseRuler)
        setMouseXY(x, screenHeight-y);

    //图形被选择
    if (choose && optionID != -1)
    {
        int moveX = x - origalMoving.x;
        int moveY = screenHeight - y - origalMoving.y;
        //进行平移操作
        if (myMotion == MOVING) {
            Painter.move(optionID, moveX, moveY);
        }
        //进行拉扯操作
        else if (myMotion == DRAG) {
            if (shape == PAN) return;
            Painter.drag(optionID, origalMoving, moveX, moveY);
        }
        //改变大小操作
        else if (myMotion == SCHANGE) {
            Painter.changeSize(optionID, moveX, moveY);
        }
        //改变形状
        else if (myMotion == RCHANGE) {
            Painter.changeShape(optionID, moveX, moveY);
        }
        else if (myMotion == SETCOLOR) {
            Painter.colorDog(optionID, moveY);
        }

        origalMoving.set(x, screenHeight-y);
    }
    //画笔
    else
    {
        int sy = screenHeight - y;
        Painter.setPoint(x, sy);
            //镜像
            if (Painter.mirror) {
                int mx, my;
                switch (Painter.mirror) {
                    case 1: mx = screenWidth-x; my = sy; break;
                    case 2: mx = x; my = screenHeight - sy; break;
                    case 3: mx = screenWidth-x; my = screenHeight-sy; break;
                }
                Painter.m->setPoint(mx, my);
            }
    }

    display();
}



int main(int argc, char *argv[])
{
    //界面初始化
    //------------------------------------
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Draw system");
    init();

    Painter.screenHeight = screenHeight;
    Painter.screenWidth  = screenWidth;

    //菜单
    Menu();

    //开始绘画
    //--------------------------------------
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutPassiveMotionFunc(passiveMotion);
    glutDisplayFunc(display);
    glutMainLoop();
}



