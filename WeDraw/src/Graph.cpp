#include "Graph.h"



/******************************************������������**********************************************/
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



/*********************************************������**************************************************/

void Graph::setPoint(int x, int y)
{
    /*************************
     *����һ����
     *��Ҫ�жϼ�������ĸ���
     *��ȫ�������ok = true
     *�����Σ�������Ҫ��д�ú���
    *************************/
    if (ok) return;
    if (pArray.empty()) {
        pArray = vector<Point>(2, Point(x, y));
    }
    else {
        pArray[1].set(x, y);
        ok = true;
    }
}


void Graph::changePoint(int x, int y)
{
    /*************************
     *�޸����ڻ��Ƶĵ������
     *ֻ���޸ĵڶ�����
    **************************/
    pArray[1].x = x;
    pArray[1].y = y;
}

/********************************************����***********************************************/
void Graph::drag(const Point &originalPoint, int x, int y)
{
    double dis1 = PPDistance(originalPoint, pArray[0]);
    double dis2 = PPDistance(originalPoint, pArray[1]);
    int size = conf.lineSize + 2;
    //ѡ��������������
    if (dis1 < dis2) {
        pArray[0].x += x;
        pArray[0].y += y;
    }
    else {
        pArray[1].x += x;
        pArray[1].y += y;
    }
}

void Graph::move(int x, int y)
{
    for (int i = 0; i < pArray.size(); i++) {
        pArray[i].x += x;
        pArray[i].y += y;
    }
}

/*******************************************��������****************************************************/
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

void Graph::config() {
    /*******************
     *ͼ�λ���ǰ
     *��ʼ������
    *******************/
    glColor3f(conf.c.R, conf.c.G, conf.c.B);  //������ɫ
    glLineWidth(conf.lineSize);  //�����߿�
    //��������
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

