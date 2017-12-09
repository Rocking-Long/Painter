#include "Graph.h"


///////////////////////////////////////////////////////基本参数设置

void Graph::setColor(const Color &col)
{
    conf.c.set(col);
}

void Graph::setLineSize(LineSize lineSize)
{
    conf.lineSize = lineSize;
}

void Graph::setDash(bool isDashes)
{
    conf.isDashes = isDashes;
}

void Graph::setpolymode(bool isFilled)
{
    conf.isFilled = isFilled;
}

void Graph::setConfig(const GraphConfig &config)
{
    conf.c.set(config.c);
    conf.lineSize = config.lineSize;
    conf.isDashes = config.isDashes;
    conf.isFilled = config.isFilled;
    conf.frame = config.frame;
}

bool Graph::finish()
{
    return ok;
}



///////////////////////////////////////////////////////////////点设置

/**
 *  @brief  加入一个顶点到图形中
 *  @param  x, y 为当前鼠标点击的坐标
 */
void Graph::setPoint(int x, int y)
{
    // 需要判断加入的是哪个点
    // 点全部加入后，ok = true
    // 三角形，画笔需要重写该函数
    if (ok) return;
    if (pArray.empty()) {
        pArray = vector<Point>(2, Point(x, y));
    }
    else {
        pArray[1].set(x, y);
        ok = true;
    }
}

/**
 *  @brief  修改正在绘制的点的坐标
 */
void Graph::changePoint(int x, int y)
{
    pArray[1].x = x;
    pArray[1].y = y;
}


///////////////////////////////////////////////////////////////////////////动作

/**
 *  @brief  对图形顶点进行拖拽
 *  @param  originalPoint 鼠标点击的位置
 *  @param  x, y 鼠标拖拽的距离
 */
void Graph::drag(const Point &originalPoint, int x, int y)
{
    double dis1 = PPDistance(originalPoint, pArray[0]);
    double dis2 = PPDistance(originalPoint, pArray[1]);
    int size = conf.lineSize + 2;
    //选择最近点进行拉扯
    if (dis1 < dis2) {
        pArray[0].x += x;
        pArray[0].y += y;
    }
    else {
        pArray[1].x += x;
        pArray[1].y += y;
    }
}

/*位移*/
void Graph::move(int x, int y)
{
    for (int i = 0; i < pArray.size(); i++) {
        pArray[i].x += x;
        pArray[i].y += y;
    }
}

/////////////////////////////////////////////////////////////////////其他设置

/**
 *  @brief  赋值一个自己，并把所有顶点横坐标+10
 *  @param  g 保存复制的指针
 */
void Graph::copy(Graph *g)
{
    g->s = s;
    g->pArray = pArray;
    for (int i = 0; i < pArray.size(); i++)
        pArray[i].x += 10;

    g->ok = ok;
    g->conf.c = conf.c;
    g->conf.frame = conf.frame;
    g->conf.isDashes = conf.isDashes;
    g->conf.isFilled = conf.isFilled;
    g->conf.lineSize = conf.lineSize;
}

/**
 *  @brief  修改OpenGL当前设置参数，
 *  用于图形绘制前
 */
void Graph::config()
{
    glColor3f(conf.c.R, conf.c.G, conf.c.B);
    glLineWidth(conf.lineSize);

    if (conf.isDashes) {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0x00FF);
    }
    else {
        glDisable(GL_LINE_STIPPLE);
    }

    if(conf.isFilled)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}


/**
 *  @brief  获取能包围图形的矩形的左上角与右下角
 */
void Graph::getRectangle(Point &p1, Point &p2)
{
    p1.x = p2.y = 999999;
    p1.y = p2.x = -1;
    for (int i = 0; i < pArray.size(); i++) {
        int x = pArray[i].x;
        int y = pArray[i].y;
        if (x < p1.x)
            p1.x = x;
        if (x > p2.x)
            p2.x = x;
        if (y > p1.y)
            p1.y = y;
        if (y < p2.y)
            p2.y = y;
    }

}

