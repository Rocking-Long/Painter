#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <GL/glut.h>
#include "HappyDog.h"



// 图形菜单界面
// 提供所有操作的选择
// 如果要增加新东西，务必修改该文件







//////////////////////////////////////////////////////////////////////////选择时改变参数、复原的动作
void cancelMotion()
{
    /****************************
     *某些选项可自动取消选择状态
    ****************************/
    myMotion = NO;
    choose = false;
    optionID = -1;
    Painter.cancelChoose();
}

void changeGraph(int option)
{
    /****************************
     *修改图形参数
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



//////////////////////////////////////////////////////////////////////////图形选择子菜单

void shapeSubMenu(GLint shapeOption)
{
    /********************
     *图形子菜单
     *选择要绘画的图形
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
     *折线，线段选择
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
     *矩形选择
    ************************/
    if (rec == 1)
        shape = RECTANGLE;
    else if (rec == 2)
        shape = SQUARE;
    else
        shape = CRECTANGLE;
    cancelMotion();
}

/* 圆形选择 */
void cirWhatMenu(GLint cir)
{
    if (cir == 1)
        shape = CIRCLE;
    else
        shape = ELLIPSE;
    cancelMotion();
}


//////////////////////////////////////////////////////////////////////////图形参数子菜单

void lineSizeSubMenu(GLint lineSizeOption)
{
    /**********************
     *线粗细选择
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
     *线形选择
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
     *选中图形
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
     *填充模式
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
    mouseRight = true;  //防止bug
    display();
}

void setColorDog(GLint c)
{
    if (optionID == -1)
        return;
    Painter.whatColorDog = c;
    Painter.setColorFunc(optionID);
    myMotion = SETCOLOR;
    mouseRight = true;  //防止bug
    display();
}

void motionMenu(GLint m)
{
    /********************
     *图形动作
    ********************/

    //没有图形可以操作
    if (optionID == -1) {
        myMotion = NO;
        return;
    }
    //删除
    if (m == 3) {
        Painter.deleteGraph(optionID);
        optionID = -1;
        myMotion = NO;
        display();
    }
    else if (m == 4) {
        //复制
        Painter.mirror = 0;  //镜像需要关闭，否则崩溃
        Painter.createGraph(Painter[optionID]->s, Painter[optionID]->conf);
        Painter[optionID]->copy(Painter.getLast());
        //将新复制的图形的conf设定为前一个图形的conf
        Painter.getLast()->conf.c = Painter[optionID]->conf.c;
        Painter.getLast()->conf.lineSize = Painter[optionID]->conf.lineSize;
        Painter.getLast()->conf.isDashes = Painter[optionID]->conf.isDashes;
        myMotion = MOVING;
        display();
        Painter.mirror = 1;  //镜像重开
    }

    switch (m) {
        case 0: myMotion = NO;      break;
        case 1: myMotion = MOVING;  break;
        case 2: myMotion = DRAG;    break;
    }
    mouseRight = true;  //防止bug
    display();
}



//////////////////////////////////////////////////////////////////////////选项子菜单
void setRuler(GLint opt)
{
    /*******************
     *标尺选择
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
     *背景色选择
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
     *镜像选择
    ***********************/
    Painter.mirror = opt;
    mouseRight = true;
}

void mouseRulerMenu(GLint opt)
{
    /********************
     *鼠标标尺
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
     *保存与读取
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

//////////////////////////////////////////////////////////////////////////颜色选取
void colorSubMenu(GLint colorOption)
{
    //没事干
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


//////////////////////////////////////////////////////////////////////////主菜单

void mainMenu (GLint renderingOption)
{
    /**********************
     *主菜单
    **********************/
    mouseRight = true;
    if (renderingOption == -1) {
        cancelMotion();
        if (choose) {
            chooseSubMenu(0);
        }
        //停止绘制
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
    //菜单
    //------------------------------------
    GLint subMenu1; //定义子菜单
    GLint subMenu2;
    GLint subMenu3;
    GLint subMenu4;
    GLint subMenu5;
    GLint subMenu6;
    GLint subMenu7;
    GLint subMenu8;
    GLint subMenu9;

    /**********************形状**********************/
    GLint subMenuLine = glutCreateMenu(lineWhatMenu);
        glutAddMenuEntry ("线段", 1);
        glutAddMenuEntry ("折线", 2);
        glutAddMenuEntry ("三次Bezier曲线", 3);

    GLint subMenuRec = glutCreateMenu(recWhatMenu);
        glutAddMenuEntry ("长方形", 1);
        glutAddMenuEntry ("正方形", 2);
        glutAddMenuEntry ("圆角矩形", 3);

    GLint subMenuCic = glutCreateMenu(cirWhatMenu);
        glutAddMenuEntry ("正圆", 1);
        glutAddMenuEntry ("椭圆", 2);

    subMenu1 = glutCreateMenu (shapeSubMenu);
        glutAddMenuEntry ("画笔", 0);
        glutAddSubMenu   ("线", subMenuLine);
        glutAddMenuEntry ("三角形", 2);
        glutAddSubMenu   ("矩形", subMenuRec);
        glutAddSubMenu   ("圆形", subMenuCic);
        glutAddMenuEntry ("多边形", 5);

    /**********************参数***************************/
    subMenu3 = glutCreateMenu (lineSizeSubMenu);
        glutAddMenuEntry ("较细", 1);
        glutAddMenuEntry ("细", 2);
        glutAddMenuEntry ("正常", 3);
        glutAddMenuEntry ("粗", 4);
        glutAddMenuEntry ("较粗", 5);

    subMenu4 = glutCreateMenu (lineSubMenu);
        glutAddMenuEntry ("实线", 0);
        glutAddMenuEntry ("虚线", 1);

    subMenu6 = glutCreateMenu (chooseSubMenu);
        glutAddMenuEntry ("选择图形", 1);
        glutAddMenuEntry ("取消选择", 2);

    GLint subChangeSize = glutCreateMenu(changeSizeMenu);
        glutAddMenuEntry ("大小形变", 1);
        glutAddMenuEntry ("矩形形变", 2);


    subMenu7 = glutCreateMenu (motionMenu);
        glutAddMenuEntry ("无", 0);
        glutAddMenuEntry ("平移", 1);
        glutAddMenuEntry ("拉扯", 2);
        glutAddSubMenu   ("形变", subChangeSize);
        glutAddMenuEntry ("复制", 4);
        glutAddMenuEntry ("删除", 3);

    subMenu8 = glutCreateMenu (SetPaintMode);
        glutAddMenuEntry("边缘绘制模式",0);
        glutAddMenuEntry("无边框填充模式",1);
        glutAddMenuEntry("有边框填充模式",2);

    /*****************选项*******************/
    GLint subMenuRuler = glutCreateMenu (setRuler);
        glutAddMenuEntry ("打开标尺", 1);
        glutAddMenuEntry ("关闭标尺", 2);

    GLint subMenuBackColor = glutCreateMenu (backColorMenu);
        glutAddMenuEntry ("白色", 1);
        glutAddMenuEntry ("黑色", 2);
        glutAddMenuEntry ("红色", 3);
        glutAddMenuEntry ("绿色", 4);
        glutAddMenuEntry ("蓝色", 5);

    GLint subMenuMirror = glutCreateMenu (mirrorMenu);
        glutAddMenuEntry ("关闭镜像", 0);
        glutAddMenuEntry ("左右镜像", 1);
        glutAddMenuEntry ("上下镜像", 2);
        glutAddMenuEntry ("斜镜像", 3);

    GLint subMenuMouseRuler = glutCreateMenu (mouseRulerMenu);
        glutAddMenuEntry ("关闭鼠标标尺", 0);
        glutAddMenuEntry ("打开鼠标标尺", 1);

    GLint subMenuSaveRead = glutCreateMenu (saveAndReadMenu);
        glutAddMenuEntry ("保存", 0);
        glutAddMenuEntry ("读取", 1);

    subMenu9 = glutCreateMenu (optionMenu);
        glutAddSubMenu ("背景色", subMenuBackColor);
        glutAddSubMenu ("镜像", subMenuMirror);
        glutAddSubMenu ("标尺", subMenuRuler);
        glutAddSubMenu ("鼠标标尺", subMenuMouseRuler);
        glutAddSubMenu ("保存/读取", subMenuSaveRead);

/***************************************************颜色选取***************************************************/
    //颜色菜单
    GLint subMenuRED;
    GLint subMenuYELLOW;
    GLint subMenuGREEN;
    GLint subMenuBLUE;
    GLint subMenuPURPLE;
    GLint subMenuGREY;
    GLint subMeanWhite;
    GLint subMeanBlack;
    subMenuRED = glutCreateMenu(setRGBred);
        glutAddMenuEntry("深红",1);
        glutAddMenuEntry("红",2);
        glutAddMenuEntry("粉红",3);
        glutAddMenuEntry("玫瑰红",4);

    subMenuYELLOW = glutCreateMenu(setRGByellow);
        glutAddMenuEntry("褐色",1);
        glutAddMenuEntry("桔黄",2);
        glutAddMenuEntry("浅桔黄",3);
        glutAddMenuEntry("金色",4);
        glutAddMenuEntry("棕黄",5);
        glutAddMenuEntry("橄榄色",6);
        glutAddMenuEntry("深黄色",7);
        glutAddMenuEntry("酸橙色",8);
        glutAddMenuEntry("黄色",9);
        glutAddMenuEntry("浅黄",10);

    subMenuGREEN = glutCreateMenu(setRGBgreen);
        glutAddMenuEntry("深绿",1);
        glutAddMenuEntry("绿色",2);
        glutAddMenuEntry("海绿",3);
        glutAddMenuEntry("鲜绿",4);
        glutAddMenuEntry("浅绿",5);
        glutAddMenuEntry("青色",6);
        glutAddMenuEntry("青绿",7);
        glutAddMenuEntry("浅青绿",8);

    subMenuBLUE = glutCreateMenu(setRGBblue);
        glutAddMenuEntry("深灰蓝",1);
        glutAddMenuEntry("宝石蓝",2);
        glutAddMenuEntry("深蓝",3);
        glutAddMenuEntry("蓝色",4);
        glutAddMenuEntry("浅蓝1",5);
        glutAddMenuEntry("天蓝",6);
        glutAddMenuEntry("浅蓝2",7);
        glutAddMenuEntry("靛蓝",8);
        glutAddMenuEntry("蓝灰",9);

    subMenuPURPLE = glutCreateMenu(setRGBpurple);
        glutAddMenuEntry("紫色",1);
        glutAddMenuEntry("梅红",2);
        glutAddMenuEntry("淡紫",3);

    subMenuGREY = glutCreateMenu(setRGBgrey);
        glutAddMenuEntry("黑色", 0);
        glutAddMenuEntry("灰",1);
        glutAddMenuEntry("50%灰",2);
        glutAddMenuEntry("40%灰",3);
        glutAddMenuEntry("25%灰",4);
        glutAddMenuEntry("白色", 5);

    GLint subColorDog = glutCreateMenu (setColorDog);
        glutAddMenuEntry ("深浅", 0);
        glutAddMenuEntry ("R", 1);
        glutAddMenuEntry ("G", 2);
        glutAddMenuEntry ("B", 3);

    subMenu2 = glutCreateMenu (colorSubMenu);
        glutAddSubMenu("变色条", subColorDog);
        glutAddSubMenu("红",subMenuRED);
        glutAddSubMenu("黄",subMenuYELLOW);
        glutAddSubMenu("绿",subMenuGREEN);
        glutAddSubMenu("蓝",subMenuBLUE);
        glutAddSubMenu("紫",subMenuPURPLE);
        glutAddSubMenu("灰",subMenuGREY);


    glutCreateMenu (mainMenu);      // 创建菜单
        glutAddSubMenu ("图形", subMenu1);
        glutAddSubMenu ("颜色", subMenu2);
        glutAddSubMenu ("粗细", subMenu3);
        glutAddSubMenu ("线型", subMenu4);
        glutAddSubMenu ("填充模式", subMenu8);
        glutAddSubMenu ("选择", subMenu6);
        glutAddSubMenu ("动作", subMenu7);
        glutAddSubMenu ("选项", subMenu9);
        glutAddMenuEntry ("停止", -1);
    glutAttachMenu (GLUT_RIGHT_BUTTON);

}




#endif // MENU_H_INCLUDED
