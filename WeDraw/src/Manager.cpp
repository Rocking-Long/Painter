#include "Manager.h"
#include <fstream>


Manager::Manager()
{
    clearDay = 7;
    rec = new myRectangle(99999);
    cir = new Circle(89898);
    tempRec = new myRectangle(99998);
    tempRec->pArray = vector<Point>(4);
    tempPerRec = new myRectangle(99997);
    tempPerRec->pArray = vector<Point>(4);

    cir->setColor(WHITE);
    cir->setDash(false);
    cir->setLineSize(l1);
    cir->setpolymode(true);
    cir->conf.frame = true;
    cir->pArray = vector<Point>(2);
    cir->ok = true;

    rec->conf.isDashes = true;
    rec->conf.isFilled = false;
    rec->conf.c.set(BLACK);
    rec->conf.frame = false;
    rec->conf.lineSize = l1;
    rec->pArray = vector<Point>(4);
    rec->ok = true;
}

/***************************************Debug******************************************/

void Manager::check(const string &name, int id, bool ifNull = true)
{
    /********************
     *异常处理
    ********************/
    if (id < 0 || id >= panel.size()) {
        cout << "Manager函数：" << name << " 发生panel非法访问\n";
        cout << "非法下标：" << id << "\n";
        cout << "panel.size = " << panel.size() << endl;
    }
    else if (ifNull && panel[id] == NULL) {
        cout << "Manager函数：" << name << " 发生panel空指针访问\n";
        cout << "访问下标：" << id << "\n";
    }
}

void Manager::print() {
    /*******************
     *打印panel检查
    *******************/
    for (int i = 0; i < panel.size(); i++) {
        if (panel[i] == NULL)
            cout << "NULL ";
        else
            cout << graphName[panel[i]->s] << ' ';
    }
    cout << '\n';
}




/***************************************获取信息*************************************/
unsigned int Manager::size()
{
    /************************
     *返回图形数量
    ************************/
    return panel.size();
}

Graph* Manager::getLast()
{
    /**************************
     *返回panel的最后一个元素
     *通常该元素是在绘画中
    **************************/
    return panel[panel.size()-1];
}


bool Manager::enable()
{
    /****************************
     *是否在绘画中
     *不在绘画中，鼠标松开时无反应
    *****************************/
    if (panel.empty()) return false;
    if (getLast() == NULL) return false;
    return !getLast()->finish();
}

bool Manager::empty()
{
    /****************************
     *判断panel是否为空
    ****************************/
    if (panel.empty())
        return true;
    for (int i = 0; i < panel.size(); i++)
        if (panel[i] != NULL)
            return false;
    return true;
}

Graph* Manager::operator [](int i)
{
    /**************************
     *重载[]，取panel元素
    **************************/
    if (i < panel.size())
        return panel[i];
    return NULL;
}




/************************************************操作图形*********************************************/

void Manager::deleteGraph(int id) {
    print();
    /***************
     *删除图形
    ***************/
    if (id == -1)
        return;
    check("deleteGraph", id, true);
    cout << "DELETE " << id << "  " << graphName[panel[id]->s]<< '\n';
    delete panel[id];
    panel[id] = NULL;
}

void Manager::createGraph(Shape s, const GraphConfig &config) {
    /*************************************
     *创建新图形
     *创建镜像图形
     *条件：panel最后一个图形已经完成
     *      panel为空
     *      末尾元素为空指针(已删除)
    **************************************/
    if (panel.empty() || getLast()==NULL || getLast()->finish()) {
        int id = panel.size();
        Graph *g;
        //加入图形入panel
        //--------------------------------
        switch (s) {
            case PAN:
                g = new Pan(id); m = new Pan(id+1);break;
            case LINE:
                g = new Line(id); m = new Line(id+1);break;
            case CIRCLE:
                g = new Circle(id); m = new Circle(id+1);break;
            case RECTANGLE:
                g = new myRectangle(id); m = new myRectangle(id+1);break;
            case TRIANGLE:
                g = new Triangle(id); m = new Triangle(id+1);break;
            case POLYGON:
                g = new myPolygon(id); m = new myPolygon(id+1);break;
            case FOLDLINE:
                g = new foldLine(id); m = new foldLine(id+1);break;
            case SQUARE:
                g = new Square(id); m = new Square(id+1);break;
            case CRECTANGLE:
                g = new CRectangle(id); m = new CRectangle(id+1);break;
            case ELLIPSE:
                g = new Ellipse(id); m = new Ellipse(id+1); break;
        }
        panel.push_back(g);
        getLast()->setConfig(config);
        if (mirror) {
            cout << "镜像绘制\n";
            g->copy(m);
        }
        else {
            delete m;
            m = NULL;
        }
        cout << "ID:" << panel.size() << "  绘制:"<< graphName[s] << '\n';
    }
}



void Manager::changePoint(int x, int y)
{
    /***************************
     *动态改变图形某点坐标
    ***************************/
    getLast()->changePoint(x, y);
}

void Manager::setPoint(int x, int y)
{
    /***************************
     *给图形加入顶点
    ***************************/
    getLast()->setPoint(x, y);
}

void Manager::move(int id, int x, int y)
{
    /*************************
     *图形平移操作
    *************************/
    panel[id]->move(x, y);
    Point p1, p2;
    panel[id]->getRectangle(p1, p2);
    setRectangle(p1, p2);
}

void Manager::drag(int id, const Point &p, int x, int y)
{
    /***********************
     *拉扯图形
    ***********************/
    panel[id]->drag(p, x, y);
    Point p1, p2;
    panel[id]->getRectangle(p1, p2);
    setRectangle(p1, p2);
}

void Manager::setOriginalRec(int id)
{
    /******************************
     *形变初始化
     *初始化临时矩形（保存原矩形）
     *初始化比例矩形
    *******************************/
    Point p1, p2;
    panel[id]->getRectangle(p1, p2);

    //初始化tempRec和tempPerRec
    tempRec->pArray[0].set(p1);
    tempRec->pArray[2].set(p2);
    tempRec->pArray[1].x = p2.x;
    tempRec->pArray[1].y = p1.y;
    tempRec->pArray[3].x = p1.x;
    tempRec->pArray[3].y = p2.y;
    tempPerRec->pArray[0].set(p1);
    tempPerRec->pArray[2].set(p2);
    tempPerRec->pArray[1].x = p2.x;
    tempPerRec->pArray[1].y = p1.y;
    tempPerRec->pArray[3].x = p1.x;
    tempPerRec->pArray[3].y = p2.y;

    //初始化tempArray
    tempArray = vector<Point>(panel[id]->pArray.size());
    for (int i = 0; i < tempArray.size(); i++)
        tempArray[i].set(panel[id]->pArray[i]);
}

void Manager::changeSize(int id, int x, int y)
{
    /*******************************
     *改变图形大小
     *原图形 * 比例(仅宽比例)
    *******************************/
    //比例矩形
    tempPerRec->pArray[1].x += x;
    tempPerRec->pArray[2].x += x;
    tempPerRec->pArray[2].y += y;
    tempPerRec->pArray[3].y += y;

    //比例： 新矩形宽 / 原矩形宽
    double percent = 1.0 * (tempPerRec->pArray[1].x-tempPerRec->pArray[0].x) / (tempRec->pArray[1].x-tempRec->pArray[0].x);
    //原点
    int ox = tempRec->pArray[0].x;
    int oy = tempRec->pArray[0].y;

    //计算新点坐标
    for (int i = 0; i < tempArray.size(); i++) {
        double width = tempArray[i].x - ox;
        double high   = oy - tempArray[i].y;
        width *= percent;
        high  *= percent;
        panel[id]->pArray[i].set(ox+width, oy-high);
    }

    Point p1, p2;
    panel[id]->getRectangle(p1, p2);
    setRectangle(p1, p2);
}

void Manager::changeShape(int id, int x, int y)
{
    /**********************************
     *矩形形变
     *原图形高 * 高比例
     *原图形宽 * 宽比例
    **********************************/

    //比例矩形
    tempPerRec->pArray[1].x += x;
    tempPerRec->pArray[2].x += x;
    tempPerRec->pArray[2].y += y;
    tempPerRec->pArray[3].y += y;

    //比例： 新矩形宽 / 原矩形宽
    double percent1 = 1.0 * (tempPerRec->pArray[1].x-tempPerRec->pArray[0].x) / (tempRec->pArray[1].x-tempRec->pArray[0].x);
    double percent2 = 1.0 * (tempPerRec->pArray[0].y-tempPerRec->pArray[3].y) / (tempRec->pArray[0].y-tempRec->pArray[3].y);
    //原点
    int ox = tempRec->pArray[0].x;
    int oy = tempRec->pArray[0].y;

    //计算新点坐标
    for (int i = 0; i < tempArray.size(); i++) {
        double width = tempArray[i].x - ox;
        double high   = oy - tempArray[i].y;
        width *= percent1;
        high   *= percent2;
        panel[id]->pArray[i].set(ox+width, oy-high);
    }

    Point p1, p2;
    panel[id]->getRectangle(p1, p2);
    setRectangle(p1, p2);
}


/*********************
 *颜色条
 *初始化
 *改变
*********************/


void Manager::setColorFunc(int id)
{
    cir->pArray[0].x = screenWidth / 8 - 6;
    cir->pArray[1].x = screenWidth / 8 + 6;
    Color c(panel[id]->conf.c);
    double x;
    //深浅
    if (whatColorDog == 0) {
        cir->conf.c.set(WHITE);
        //得到RGB的二元一次方程
        x = (c.R + c.B + c.G) / 3;   //取定方程的x值
        a1 = (c.R-x) / (x*x-x);
        b1 = 1-a1;
        a2 = (c.G-x) / (x*x-x);
        b2 = 1-a2;
        a3 = (c.B-x) / (x*x-x);
        b3 = 1-a3;
    }
    //R
    else if (whatColorDog == 1) {
        cir->conf.c.set(RED);
        x = c.R;
    }
    //G
    else if (whatColorDog == 2) {
        cir->conf.c.set(GREEN);
        x = c.G;
    }
    //B
    else if (whatColorDog == 3) {
        cir->conf.c.set(BLUE);
        x = c.B;
    }
    cir->pArray[0].y = cir->pArray[1].y = screenHeight/4 + (screenHeight/2) * x;

}

void Manager::colorDog(int id, int y)
{
    cir->pArray[0].y += y;
    cir->pArray[1].y += y;
    if (cir->pArray[0].y > screenHeight*3/4)
        cir->pArray[0].y = cir->pArray[1].y = screenHeight * 3 / 4;
    else if (cir->pArray[0].y < screenHeight / 4)
        cir->pArray[0].y = cir->pArray[1].y = screenHeight / 4;
    //计算比例
    double x = (cir->pArray[0].y-screenHeight/4)*1.0 / (screenHeight/2);
    //深浅
    if (whatColorDog == 0) {
        panel[id]->conf.c.R = a1*x*x + b1*x;
        panel[id]->conf.c.G = a2*x*x + b2*x;
        panel[id]->conf.c.B = a3*x*x + b3*x;
    }
    //R
    else if (whatColorDog == 1) {
        panel[id]->conf.c.R = x;
    }
    //G
    else if (whatColorDog == 2) {
        panel[id]->conf.c.G = x;
    }
    //B
    else if (whatColorDog == 3) {
        panel[id]->conf.c.B = x;
    }

}


/************************************************选择图形*************************************************/
void Manager::setRectangle(const Point &p1, const Point &p2)
{
    /**********************
     *绘制包围图形的矩形
    **********************/
    int w = 5;
    rec->pArray[0].set(p1.x-w, p1.y+w);
    rec->pArray[2].set(p2.x+w, p2.y-w);
    rec->pArray[1].set(p2.x+w, p1.y+w);
    rec->pArray[3].set(p1.x-w, p2.y-w);
}

int Manager::getNearestGraph(int x, int y)
{
    /**********************
     *查找最临近近图形id
    **********************/
    bool findGraph = false;
    int minVal = 99999999;
    int id = 0;
    for (int i = 0; i < panel.size(); i++) {
        if (panel[i] == NULL)
            continue;
        findGraph = true;
        int dis = panel[i]->getDistance(x, y);
        if (dis < minVal) {
            id = i;
            minVal = dis;
        }
    }
    if (!findGraph)
        return -1;


    //将被选中图形放置到最前面
    panel.push_back(panel[id]);
    panel[id] = NULL;
    id = panel.size()-1;

    cout << "选择  " << graphName[panel[id]->s] << '\n' << "RGB(" << panel[id]->conf.c.R
         << ", " << panel[id]->conf.c.G << ", " << panel[id]->conf.c.B << ")  "<< "距离 " << minVal << '\n';
    //绘制矩形
    Point p1, p2;
    panel[id]->getRectangle(p1, p2);
    setRectangle(p1, p2);

    return id;
}

void Manager::cancelChoose()
{
    /*****************
     *取消图形选择
    *****************/
    clearBoy();
}

/******************************************读取与保存**************************************************/
void Manager::save()
{
    string name;
    cout << "输入文件名：";
    cin >> name;
    name += ".dat";
    ofstream output(name.c_str());
    //保存
    for (int i = 0; i < panel.size(); i++)
    {
        if (panel[i] == nullptr)
            continue;
        output << panel[i]->s << ' ';
        output << panel[i]->conf.c.R << ' ' << panel[i]->conf.c.G << ' ' << panel[i]->conf.c.B << ' ';
        output << panel[i]->conf.lineSize << ' ';
        output << panel[i]->conf.isDashes << ' ';
        output << panel[i]->conf.isFilled << ' ';
        output << panel[i]->conf.frame << ' ';
        output << panel[i]->pArray.size() << ' ';
        for (int j = 0; j < panel[i]->pArray.size(); j++) {
            output << panel[i]->pArray[j].x << ' ';
            output << panel[i]->pArray[j].y << ' ';
        }
        output << endl;
    }

    output.close();
    cout << "保存成功！" << endl;
}

void Manager::read()
{
    string name;
    cout << "输入文件名：";
    cin >> name;
    name += ".dat";
    fstream ifExist(name.c_str(), ios::in);
    if (!ifExist) {
        cout << "文件不存在！\n";
        return;
    }
    ifExist.close();
    ifstream input(name.c_str());
    for (int i = 0; i < panel.size(); i++)
        delete panel[i];
    panel.clear();
    Shape s = PAN;
    GraphConfig conf;
    int psize;
    int index = 0;
    int px, py;
    int shape, linesize;
    while (!input.eof())
    {
        input >> shape;
        s = Shape(shape);
        input >> conf.c.R;
        input >> conf.c.G;
        input >> conf.c.B;
        input >> linesize;
        conf.lineSize = LineSize(linesize);
        input >> conf.isDashes;
        input >> conf.isFilled;
        input >> conf.frame;
        createGraph(s, conf);
        input >> psize;

        for (int i = 0; i < psize; i++) {
            if (input.fail())
                goto Test;
            input >> px >> py;
            panel[index]->pArray.push_back(Point(px, py));
        }
        panel[index]->id = index;
        panel[index]->ok = true;
        index++;
    }
Test:
    panel.pop_back();
/*    cout << panel.size() << endl;

    cout << panel.size() << endl;*/

/*    for (int i = 0; i < panel.size(); i++) {
        for (int j = 0; j < panel[i]->pArray.size(); j++) {
            cout << panel[i]->s;
            cout << panel[i]->conf.c.R;
            cout << panel[i]->conf.c.G;
            cout << panel[i]->conf.c.B;
            cout << panel[i]->conf.lineSize;
            cout << panel[i]->conf.isDashes;
            cout << panel[i]->conf.isFilled;
            cout << panel[i]->conf.frame << endl;
            cout << panel[i]->pArray[j].x << ' ' <<  panel[i]->pArray[j].y << endl;
        }
//    cout << panel[i]->pArray.size() << endl;
    }*/

    input.close();
    cout << "读取成功！" << endl;
}
/*
    Shape s;   //形状
    bool ok;   //图形是否绘制完成
    GraphConfig conf;  //基本参数
    vector<Point> pArray;  //点集

     Color c;
    LineSize lineSize = l3;  //线粗细
    bool isDashes = false;   //是否虚线
    bool isFilled = false;
    bool frame = false;
*/

/*******************************清洁工******************************/
//清理空指针
void Manager::clearBoy()
{
    static int letsClear = 0;
    if (letsClear++ % clearDay != 0)  //没到清理周期
        return;

    vector<Graph*> temp;
    for (int i = 0; i < panel.size(); i++)
        if (panel[i] != NULL) {
            temp.push_back(panel[i]);
            temp[temp.size()-1]->id = temp.size()-1;
        }
    panel = temp;
    cout << "执行内存清理\n";
}
