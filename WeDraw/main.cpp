#include <windows.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#include "Menu.h"
using namespace std;

/******************************************ȫ������*********************************************/
//ע��������HappyDog.h��
//GraphConfig config;   ͼ�λ�������
//Shape shape = LINE;   ͼ�����
//bool choose = false;  �Ƿ�ѡ��

//����������ֹbug��û�и�������
//bool mouseLeft  = false;  //��Menu��
//bool mouseRight = false;

//ͼ�β���
//int optionID = -1;  //��ѡ���ͼ��  Menu.h
Point origalMoving;   //λ��ԭ��

//���ڴ�С����Manager.h
//int screenWidth  = 1000;
//int screenHeight = 600;


/******************************************���ƺ���********************************************/


void init(void)
{
    /******************
     *��ʼ��
    ******************/
    glClearColor(1.0,1.0,1.0,1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);
}


void mouse(int button, int state, int x, int y)
{
    /*********************************
     *��������¼�
     *���������
     *����ʱ�����滭ͼ������һ������
     *���߽��ж���
     *�ɿ�ʱ����ɶ�����滭
    *********************************/

    int sy = screenHeight-y;
    //�����
    if (mouseRuler)
        setMouseXY(x, sy);
    //���
    if(button == GLUT_LEFT_BUTTON)
    {
        mouseLeft  = true;
        mouseRight = false;

        /******************************
         *������²���
         *ͼ��ѡ�񣬲���
         *ͼ�λ���
        *******************************/
        if(state == GLUT_DOWN)
        {
            //ͼ��ѡ��
            //---------------------------------
            if (choose)
            {
                //�޶���
                if (myMotion == NO) {
                    optionID = Painter.getNearestGraph(x, sy);
                    if (optionID == -1) return;
                }
                //ƽ��
                else if (myMotion == MOVING || myMotion == DRAG) {
                    origalMoving.set(x, sy);
                }
                //��С�α�
                else if (myMotion == SCHANGE || myMotion == RCHANGE) {
                    origalMoving.set(x, sy);
                    Painter.setOriginalRec(optionID);
                }
                else if (myMotion == SETCOLOR) {
                    origalMoving.set(x, sy);
                }

                display();
                return;  //����
            }

            //ͼ�λ���
            //-----------------------------------
            Painter.createGraph(shape, config);  //�����Ҫ������ͼ�Σ��򴴽�
            Painter.setPoint(x, sy); //�����»��ƵĶ���
            //����
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
                        //�������ƾ���
                        Painter.panel.push_back(Painter.m);
                        Painter.m = NULL;
                    }

                }

            display();
        }

        /*****************************
         *����ɿ�����
         *�������
         *ͼ�β���
        *****************************/
        else if (state == GLUT_UP)
        {
            if (Painter.empty())
                return;
            //ͼ�β��������
            if (choose && optionID != -1)
            {
                //pass
            }
            //���ʲ�������ɻ���
            else if (shape == PAN)
            {
                mouseRight = true;  //��ֹ�Ҽ��滭
                Painter.setPoint(x, sy);
                Painter.getLast()->ok = true;
                    //����
                    if (Painter.mirror)
                    {
                        int mx, my;
                        switch (Painter.mirror) {
                            case 1: mx = screenWidth-x; my = sy; break;
                            case 2: mx = x; my = screenHeight - sy; break;
                            case 3: mx = screenWidth-x; my = screenHeight-sy; break;
                        }
                        //�������ƾ���
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
     *�Ҽ�����
     *���ܷǷ�
     *���÷���
    ***********************/
    else {
        mouseLeft  = false;
        mouseRight = true;
    }

}


void passiveMotion(int x, int y)
{
    /*************************************
     *�����ɿ�����Ķ���
     *�ı����ڻ滭��ͼ�εı����������
    *************************************/
    int sy = screenHeight - y;
    //�����
    if (mouseRuler)
        setMouseXY(x, sy);


    //û��ͼ�����ڻ滭������Ҫ���ô�
    if (!Painter.enable() || shape == PAN) {
        if (mouseRuler)
            display();
        return;
    }

    //��ͼ�����ڻ滭�У��޸ı��滭�������
    Painter.changePoint(x, sy);
        //����
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
     *��갴ס�¼�
     *���ڻ��ʻ�ͼ��ͼ�����
    **********************************/
    if ((shape!=PAN && !choose) || mouseRight || Painter.empty())
        return;

    //�����
    if (mouseRuler)
        setMouseXY(x, screenHeight-y);

    //ͼ�α�ѡ��
    if (choose && optionID != -1)
    {
        int moveX = x - origalMoving.x;
        int moveY = screenHeight - y - origalMoving.y;
        //����ƽ�Ʋ���
        if (myMotion == MOVING) {
            Painter.move(optionID, moveX, moveY);
        }
        //������������
        else if (myMotion == DRAG) {
            if (shape == PAN) return;
            Painter.drag(optionID, origalMoving, moveX, moveY);
        }
        //�ı��С����
        else if (myMotion == SCHANGE) {
            Painter.changeSize(optionID, moveX, moveY);
        }
        //�ı���״
        else if (myMotion == RCHANGE) {
            Painter.changeShape(optionID, moveX, moveY);
        }
        else if (myMotion == SETCOLOR) {
            Painter.colorDog(optionID, moveY);
        }

        origalMoving.set(x, screenHeight-y);
    }
    //����
    else
    {
        int sy = screenHeight - y;
        Painter.setPoint(x, sy);
            //����
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
    //�����ʼ��
    //------------------------------------
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Draw system");
    init();

    Painter.screenHeight = screenHeight;
    Painter.screenWidth  = screenWidth;

    //�˵�
    Menu();

    //��ʼ�滭
    //--------------------------------------
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutPassiveMotionFunc(passiveMotion);
    glutDisplayFunc(display);
    glutMainLoop();
}



