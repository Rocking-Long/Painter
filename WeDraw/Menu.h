#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <GL/glut.h>
#include "HappyDog.h"



// ͼ�β˵�����
// �ṩ���в�����ѡ��
// ���Ҫ�����¶���������޸ĸ��ļ�







//////////////////////////////////////////////////////////////////////////ѡ��ʱ�ı��������ԭ�Ķ���
void cancelMotion()
{
    /****************************
     *ĳЩѡ����Զ�ȡ��ѡ��״̬
    ****************************/
    myMotion = NO;
    choose = false;
    optionID = -1;
    Painter.cancelChoose();
}

void changeGraph(int option)
{
    /****************************
     *�޸�ͼ�β���
    ****************************/
    if (choose && optionID != -1) {
        switch (option) {
            case 1: Painter[optionID]->conf.c        = config.c; break;
            case 2: Painter[optionID]->conf.lineSize = config.lineSize; break;
            case 3: Painter[optionID]->conf.isDashes = config.isDashes; break;
            case 4: Painter[optionID]->conf.isFilled = config.isFilled; break;
            case 5: Painter[optionID]->conf.frame    = config.frame;    break;
        }
    }
    display();
}



//////////////////////////////////////////////////////////////////////////ͼ��ѡ���Ӳ˵�

void shapeSubMenu(GLint shapeOption)
{
    /********************
     *ͼ���Ӳ˵�
     *ѡ��Ҫ�滭��ͼ��
    ********************/
    switch (shapeOption) {
        case 0: shape = PAN;       break;
        case 1: shape = LINE;      break;
        case 2: shape = TRIANGLE;  break;
        case 3: shape = RECTANGLE; break;
        case 5: shape = POLYGON;   break;
    }
    cancelMotion();
}


void lineWhatMenu(GLint line)
{
    /**********************
     *���ߣ��߶�ѡ��
    **********************/
    if (line == 1)
        shape = LINE;
    else if (line == 2)
        shape = FOLDLINE;
    else if (line == 3) {}
        shape = BEZIER;
    cancelMotion();
}

void recWhatMenu(GLint rec)
{
    /************************
     *����ѡ��
    ************************/
    if (rec == 1)
        shape = RECTANGLE;
    else if (rec == 2)
        shape = SQUARE;
    else
        shape = CRECTANGLE;
    cancelMotion();
}

/* Բ��ѡ�� */
void cirWhatMenu(GLint cir)
{
    if (cir == 1)
        shape = CIRCLE;
    else
        shape = ELLIPSE;
    cancelMotion();
}


//////////////////////////////////////////////////////////////////////////ͼ�β����Ӳ˵�

void lineSizeSubMenu(GLint lineSizeOption)
{
    /**********************
     *�ߴ�ϸѡ��
    **********************/
    switch (lineSizeOption) {
        case 1: config.lineSize = l1; break;
        case 2: config.lineSize = l2; break;
        case 3: config.lineSize = l3; break;
        case 4: config.lineSize = l4; break;
        case 5: config.lineSize = l5; break;
    }
    changeGraph(2);
}

void lineSubMenu(GLint isDashes)
{
    /**********************
     *����ѡ��
    **********************/
    if (isDashes == 1)
        config.isDashes = true;
    else
        config.isDashes = false;
    changeGraph(3);
}


void chooseSubMenu(GLint c)
{
    /******************
     *ѡ��ͼ��
    ******************/
    if (c == 1) {
        choose = true;
    }
    else {
        cancelMotion();
        display();
    }
}

void SetPaintMode(GLint opt)
{
    /****************
     *���ģʽ
    ***************/
    if (opt == 1) {
        config.isFilled = true;
        config.frame = false;
    }
    else if (opt == 2) {
        config.isFilled = true;
        config.frame = true;

    }
    else {
        config.isFilled = false;
        config.frame = false;
    }
    changeGraph(4);
    changeGraph(5);
}

void changeSizeMenu(GLint opt)
{
    if (opt == 1) {
        myMotion = SCHANGE;
    }
    else {
        myMotion = RCHANGE;
    }
    mouseRight = true;  //��ֹbug
    display();
}

void setColorDog(GLint c)
{
    if (optionID == -1)
        return;
    Painter.whatColorDog = c;
    Painter.setColorFunc(optionID);
    myMotion = SETCOLOR;
    mouseRight = true;  //��ֹbug
    display();
}

void motionMenu(GLint m)
{
    /********************
     *ͼ�ζ���
    ********************/

    //û��ͼ�ο��Բ���
    if (optionID == -1) {
        myMotion = NO;
        return;
    }
    //ɾ��
    if (m == 3) {
        Painter.deleteGraph(optionID);
        optionID = -1;
        myMotion = NO;
        display();
    }
    else if (m == 4) {
        //����
        Painter.mirror = 0;  //������Ҫ�رգ��������
        Painter.createGraph(Painter[optionID]->s, Painter[optionID]->conf);
        Painter[optionID]->copy(Painter.getLast());
        //���¸��Ƶ�ͼ�ε�conf�趨Ϊǰһ��ͼ�ε�conf
        Painter.getLast()->conf.c = Painter[optionID]->conf.c;
        Painter.getLast()->conf.lineSize = Painter[optionID]->conf.lineSize;
        Painter.getLast()->conf.isDashes = Painter[optionID]->conf.isDashes;
        myMotion = MOVING;
        display();
        Painter.mirror = 1;  //�����ؿ�
    }

    switch (m) {
        case 0: myMotion = NO;      break;
        case 1: myMotion = MOVING;  break;
        case 2: myMotion = DRAG;    break;
    }
    mouseRight = true;  //��ֹbug
    display();
}



//////////////////////////////////////////////////////////////////////////ѡ���Ӳ˵�
void setRuler(GLint opt)
{
    /*******************
     *���ѡ��
    *******************/
    if (opt == 1) {
        openRuler = true;
    }
    else {
        openRuler = false;
    }
    display();
}

void backColorMenu(GLint c)
{
    /*********************
     *����ɫѡ��
    *********************/
    Color temp;
    switch (c) {
        case 1: temp.set(WHITE); break;
        case 2: temp.set(BLACK); break;
        case 3: temp.set(RED);   break;
        case 4: temp.set(GREEN); break;
        case 5: temp.set(BLUE);  break;
    }
    glClearColor(temp.R, temp.G, temp.B, 1.0);
    display();
}

void mirrorMenu(GLint opt)
{
    /***********************
     *����ѡ��
    ***********************/
    Painter.mirror = opt;
    mouseRight = true;
}

void mouseRulerMenu(GLint opt)
{
    /********************
     *�����
    ********************/
    if (opt == 1) {
        mouseRuler = true;
    }
    else {
        mouseRuler = false;
    }
    display();
}

void saveAndReadMenu(GLint opt)
{
    /*******************
     *�������ȡ
    ******************/
    cancelMotion();
    if (opt == 0)
        Painter.save();
    else
        Painter.read();
    display();
}


void optionMenu(GLint opt)
{
    //do nothing
}

//////////////////////////////////////////////////////////////////////////��ɫѡȡ
void colorSubMenu(GLint colorOption)
{
    //û�¸�
}

void setRGBred(GLint colorOption)
{
    config.c.set(red[colorOption]);
    changeGraph(1);
}

void setRGByellow(GLint colorOption)
{
    config.c.set(yellow[colorOption]);
    changeGraph(1);
}

void setRGBgreen(GLint colorOption)
{

    config.c.set(green[colorOption]);
    changeGraph(1);
}

void setRGBblue(GLint colorOption)
{
    config.c.set(blue[colorOption]);
    changeGraph(1);
}

void setRGBpurple(GLint colorOption)
{
    config.c.set(purple[colorOption]);
    changeGraph(1);
}

void setRGBgrey(GLint colorOption)
{
    config.c.set(grey[colorOption]);
    changeGraph(1);
}


//////////////////////////////////////////////////////////////////////////���˵�

void mainMenu (GLint renderingOption)
{
    /**********************
     *���˵�
    **********************/
    mouseRight = true;
    if (renderingOption == -1) {
        cancelMotion();
        if (choose) {
            chooseSubMenu(0);
        }
        //ֹͣ����
        if (shape == POLYGON || shape == FOLDLINE) {
            if (Painter.empty() || Painter.getLast() == NULL)
                return;
            if (Painter.getLast()->s == POLYGON || shape == FOLDLINE) {
                Painter.getLast()->ok = true;
                if (Painter.mirror) {
                    Painter.m->ok = true;
                    Painter.panel.push_back(Painter.m);
                }
            }

        }
    }
    display();
}


void Menu()
{
    //�˵�
    //------------------------------------
    GLint subMenu1; //�����Ӳ˵�
    GLint subMenu2;
    GLint subMenu3;
    GLint subMenu4;
    GLint subMenu5;
    GLint subMenu6;
    GLint subMenu7;
    GLint subMenu8;
    GLint subMenu9;

    /**********************��״**********************/
    GLint subMenuLine = glutCreateMenu(lineWhatMenu);
        glutAddMenuEntry ("�߶�", 1);
        glutAddMenuEntry ("����", 2);
        glutAddMenuEntry ("����Bezier����", 3);

    GLint subMenuRec = glutCreateMenu(recWhatMenu);
        glutAddMenuEntry ("������", 1);
        glutAddMenuEntry ("������", 2);
        glutAddMenuEntry ("Բ�Ǿ���", 3);

    GLint subMenuCic = glutCreateMenu(cirWhatMenu);
        glutAddMenuEntry ("��Բ", 1);
        glutAddMenuEntry ("��Բ", 2);

    subMenu1 = glutCreateMenu (shapeSubMenu);
        glutAddMenuEntry ("����", 0);
        glutAddSubMenu   ("��", subMenuLine);
        glutAddMenuEntry ("������", 2);
        glutAddSubMenu   ("����", subMenuRec);
        glutAddSubMenu   ("Բ��", subMenuCic);
        glutAddMenuEntry ("�����", 5);

    /**********************����***************************/
    subMenu3 = glutCreateMenu (lineSizeSubMenu);
        glutAddMenuEntry ("��ϸ", 1);
        glutAddMenuEntry ("ϸ", 2);
        glutAddMenuEntry ("����", 3);
        glutAddMenuEntry ("��", 4);
        glutAddMenuEntry ("�ϴ�", 5);

    subMenu4 = glutCreateMenu (lineSubMenu);
        glutAddMenuEntry ("ʵ��", 0);
        glutAddMenuEntry ("����", 1);

    subMenu6 = glutCreateMenu (chooseSubMenu);
        glutAddMenuEntry ("ѡ��ͼ��", 1);
        glutAddMenuEntry ("ȡ��ѡ��", 2);

    GLint subChangeSize = glutCreateMenu(changeSizeMenu);
        glutAddMenuEntry ("��С�α�", 1);
        glutAddMenuEntry ("�����α�", 2);


    subMenu7 = glutCreateMenu (motionMenu);
        glutAddMenuEntry ("��", 0);
        glutAddMenuEntry ("ƽ��", 1);
        glutAddMenuEntry ("����", 2);
        glutAddSubMenu   ("�α�", subChangeSize);
        glutAddMenuEntry ("����", 4);
        glutAddMenuEntry ("ɾ��", 3);

    subMenu8 = glutCreateMenu (SetPaintMode);
        glutAddMenuEntry("��Ե����ģʽ",0);
        glutAddMenuEntry("�ޱ߿����ģʽ",1);
        glutAddMenuEntry("�б߿����ģʽ",2);

    /*****************ѡ��*******************/
    GLint subMenuRuler = glutCreateMenu (setRuler);
        glutAddMenuEntry ("�򿪱��", 1);
        glutAddMenuEntry ("�رձ��", 2);

    GLint subMenuBackColor = glutCreateMenu (backColorMenu);
        glutAddMenuEntry ("��ɫ", 1);
        glutAddMenuEntry ("��ɫ", 2);
        glutAddMenuEntry ("��ɫ", 3);
        glutAddMenuEntry ("��ɫ", 4);
        glutAddMenuEntry ("��ɫ", 5);

    GLint subMenuMirror = glutCreateMenu (mirrorMenu);
        glutAddMenuEntry ("�رվ���", 0);
        glutAddMenuEntry ("���Ҿ���", 1);
        glutAddMenuEntry ("���¾���", 2);
        glutAddMenuEntry ("б����", 3);

    GLint subMenuMouseRuler = glutCreateMenu (mouseRulerMenu);
        glutAddMenuEntry ("�ر������", 0);
        glutAddMenuEntry ("�������", 1);

    GLint subMenuSaveRead = glutCreateMenu (saveAndReadMenu);
        glutAddMenuEntry ("����", 0);
        glutAddMenuEntry ("��ȡ", 1);

    subMenu9 = glutCreateMenu (optionMenu);
        glutAddSubMenu ("����ɫ", subMenuBackColor);
        glutAddSubMenu ("����", subMenuMirror);
        glutAddSubMenu ("���", subMenuRuler);
        glutAddSubMenu ("�����", subMenuMouseRuler);
        glutAddSubMenu ("����/��ȡ", subMenuSaveRead);

/***************************************************��ɫѡȡ***************************************************/
    //��ɫ�˵�
    GLint subMenuRED;
    GLint subMenuYELLOW;
    GLint subMenuGREEN;
    GLint subMenuBLUE;
    GLint subMenuPURPLE;
    GLint subMenuGREY;
    GLint subMeanWhite;
    GLint subMeanBlack;
    subMenuRED = glutCreateMenu(setRGBred);
        glutAddMenuEntry("���",1);
        glutAddMenuEntry("��",2);
        glutAddMenuEntry("�ۺ�",3);
        glutAddMenuEntry("õ���",4);

    subMenuYELLOW = glutCreateMenu(setRGByellow);
        glutAddMenuEntry("��ɫ",1);
        glutAddMenuEntry("�ۻ�",2);
        glutAddMenuEntry("ǳ�ۻ�",3);
        glutAddMenuEntry("��ɫ",4);
        glutAddMenuEntry("�ػ�",5);
        glutAddMenuEntry("���ɫ",6);
        glutAddMenuEntry("���ɫ",7);
        glutAddMenuEntry("���ɫ",8);
        glutAddMenuEntry("��ɫ",9);
        glutAddMenuEntry("ǳ��",10);

    subMenuGREEN = glutCreateMenu(setRGBgreen);
        glutAddMenuEntry("����",1);
        glutAddMenuEntry("��ɫ",2);
        glutAddMenuEntry("����",3);
        glutAddMenuEntry("����",4);
        glutAddMenuEntry("ǳ��",5);
        glutAddMenuEntry("��ɫ",6);
        glutAddMenuEntry("����",7);
        glutAddMenuEntry("ǳ����",8);

    subMenuBLUE = glutCreateMenu(setRGBblue);
        glutAddMenuEntry("�����",1);
        glutAddMenuEntry("��ʯ��",2);
        glutAddMenuEntry("����",3);
        glutAddMenuEntry("��ɫ",4);
        glutAddMenuEntry("ǳ��1",5);
        glutAddMenuEntry("����",6);
        glutAddMenuEntry("ǳ��2",7);
        glutAddMenuEntry("����",8);
        glutAddMenuEntry("����",9);

    subMenuPURPLE = glutCreateMenu(setRGBpurple);
        glutAddMenuEntry("��ɫ",1);
        glutAddMenuEntry("÷��",2);
        glutAddMenuEntry("����",3);

    subMenuGREY = glutCreateMenu(setRGBgrey);
        glutAddMenuEntry("��ɫ", 0);
        glutAddMenuEntry("��",1);
        glutAddMenuEntry("50%��",2);
        glutAddMenuEntry("40%��",3);
        glutAddMenuEntry("25%��",4);
        glutAddMenuEntry("��ɫ", 5);

    GLint subColorDog = glutCreateMenu (setColorDog);
        glutAddMenuEntry ("��ǳ", 0);
        glutAddMenuEntry ("R", 1);
        glutAddMenuEntry ("G", 2);
        glutAddMenuEntry ("B", 3);

    subMenu2 = glutCreateMenu (colorSubMenu);
        glutAddSubMenu("��ɫ��", subColorDog);
        glutAddSubMenu("��",subMenuRED);
        glutAddSubMenu("��",subMenuYELLOW);
        glutAddSubMenu("��",subMenuGREEN);
        glutAddSubMenu("��",subMenuBLUE);
        glutAddSubMenu("��",subMenuPURPLE);
        glutAddSubMenu("��",subMenuGREY);


    glutCreateMenu (mainMenu);      // �����˵�
        glutAddSubMenu ("ͼ��", subMenu1);
        glutAddSubMenu ("��ɫ", subMenu2);
        glutAddSubMenu ("��ϸ", subMenu3);
        glutAddSubMenu ("����", subMenu4);
        glutAddSubMenu ("���ģʽ", subMenu8);
        glutAddSubMenu ("ѡ��", subMenu6);
        glutAddSubMenu ("����", subMenu7);
        glutAddSubMenu ("ѡ��", subMenu9);
        glutAddMenuEntry ("ֹͣ", -1);
    glutAttachMenu (GLUT_RIGHT_BUTTON);

}




#endif // MENU_H_INCLUDED
