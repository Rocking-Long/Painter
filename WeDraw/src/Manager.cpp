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
     *�쳣����
    ********************/
    if (id < 0 || id >= panel.size()) {
        cout << "Manager������" << name << " ����panel�Ƿ�����\n";
        cout << "�Ƿ��±꣺" << id << "\n";
        cout << "panel.size = " << panel.size() << endl;
    }
    else if (ifNull && panel[id] == NULL) {
        cout << "Manager������" << name << " ����panel��ָ�����\n";
        cout << "�����±꣺" << id << "\n";
    }
}

void Manager::print() {
    /*******************
     *��ӡpanel���
    *******************/
    for (int i = 0; i < panel.size(); i++) {
        if (panel[i] == NULL)
            cout << "NULL ";
        else
            cout << graphName[panel[i]->s] << ' ';
    }
    cout << '\n';
}




/***************************************��ȡ��Ϣ*************************************/
unsigned int Manager::size()
{
    /************************
     *����ͼ������
    ************************/
    return panel.size();
}

Graph* Manager::getLast()
{
    /**************************
     *����panel�����һ��Ԫ��
     *ͨ����Ԫ�����ڻ滭��
    **************************/
    return panel[panel.size()-1];
}


bool Manager::enable()
{
    /****************************
     *�Ƿ��ڻ滭��
     *���ڻ滭�У�����ɿ�ʱ�޷�Ӧ
    *****************************/
    if (panel.empty()) return false;
    if (getLast() == NULL) return false;
    return !getLast()->finish();
}

bool Manager::empty()
{
    /****************************
     *�ж�panel�Ƿ�Ϊ��
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
     *����[]��ȡpanelԪ��
    **************************/
    if (i < panel.size())
        return panel[i];
    return NULL;
}




/************************************************����ͼ��*********************************************/

void Manager::deleteGraph(int id) {
    print();
    /***************
     *ɾ��ͼ��
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
     *������ͼ��
     *��������ͼ��
     *������panel���һ��ͼ���Ѿ����
     *      panelΪ��
     *      ĩβԪ��Ϊ��ָ��(��ɾ��)
    **************************************/
    if (panel.empty() || getLast()==NULL || getLast()->finish()) {
        int id = panel.size();
        Graph *g;
        //����ͼ����panel
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
            cout << "�������\n";
            g->copy(m);
        }
        else {
            delete m;
            m = NULL;
        }
        cout << "ID:" << panel.size() << "  ����:"<< graphName[s] << '\n';
    }
}



void Manager::changePoint(int x, int y)
{
    /***************************
     *��̬�ı�ͼ��ĳ������
    ***************************/
    getLast()->changePoint(x, y);
}

void Manager::setPoint(int x, int y)
{
    /***************************
     *��ͼ�μ��붥��
    ***************************/
    getLast()->setPoint(x, y);
}

void Manager::move(int id, int x, int y)
{
    /*************************
     *ͼ��ƽ�Ʋ���
    *************************/
    panel[id]->move(x, y);
    Point p1, p2;
    panel[id]->getRectangle(p1, p2);
    setRectangle(p1, p2);
}

void Manager::drag(int id, const Point &p, int x, int y)
{
    /***********************
     *����ͼ��
    ***********************/
    panel[id]->drag(p, x, y);
    Point p1, p2;
    panel[id]->getRectangle(p1, p2);
    setRectangle(p1, p2);
}

void Manager::setOriginalRec(int id)
{
    /******************************
     *�α��ʼ��
     *��ʼ����ʱ���Σ�����ԭ���Σ�
     *��ʼ����������
    *******************************/
    Point p1, p2;
    panel[id]->getRectangle(p1, p2);

    //��ʼ��tempRec��tempPerRec
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

    //��ʼ��tempArray
    tempArray = vector<Point>(panel[id]->pArray.size());
    for (int i = 0; i < tempArray.size(); i++)
        tempArray[i].set(panel[id]->pArray[i]);
}

void Manager::changeSize(int id, int x, int y)
{
    /*******************************
     *�ı�ͼ�δ�С
     *ԭͼ�� * ����(�������)
    *******************************/
    //��������
    tempPerRec->pArray[1].x += x;
    tempPerRec->pArray[2].x += x;
    tempPerRec->pArray[2].y += y;
    tempPerRec->pArray[3].y += y;

    //������ �¾��ο� / ԭ���ο�
    double percent = 1.0 * (tempPerRec->pArray[1].x-tempPerRec->pArray[0].x) / (tempRec->pArray[1].x-tempRec->pArray[0].x);
    //ԭ��
    int ox = tempRec->pArray[0].x;
    int oy = tempRec->pArray[0].y;

    //�����µ�����
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
     *�����α�
     *ԭͼ�θ� * �߱���
     *ԭͼ�ο� * �����
    **********************************/

    //��������
    tempPerRec->pArray[1].x += x;
    tempPerRec->pArray[2].x += x;
    tempPerRec->pArray[2].y += y;
    tempPerRec->pArray[3].y += y;

    //������ �¾��ο� / ԭ���ο�
    double percent1 = 1.0 * (tempPerRec->pArray[1].x-tempPerRec->pArray[0].x) / (tempRec->pArray[1].x-tempRec->pArray[0].x);
    double percent2 = 1.0 * (tempPerRec->pArray[0].y-tempPerRec->pArray[3].y) / (tempRec->pArray[0].y-tempRec->pArray[3].y);
    //ԭ��
    int ox = tempRec->pArray[0].x;
    int oy = tempRec->pArray[0].y;

    //�����µ�����
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
 *��ɫ��
 *��ʼ��
 *�ı�
*********************/


void Manager::setColorFunc(int id)
{
    cir->pArray[0].x = screenWidth / 8 - 6;
    cir->pArray[1].x = screenWidth / 8 + 6;
    Color c(panel[id]->conf.c);
    double x;
    //��ǳ
    if (whatColorDog == 0) {
        cir->conf.c.set(WHITE);
        //�õ�RGB�Ķ�Ԫһ�η���
        x = (c.R + c.B + c.G) / 3;   //ȡ�����̵�xֵ
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
    //�������
    double x = (cir->pArray[0].y-screenHeight/4)*1.0 / (screenHeight/2);
    //��ǳ
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


/************************************************ѡ��ͼ��*************************************************/
void Manager::setRectangle(const Point &p1, const Point &p2)
{
    /**********************
     *���ư�Χͼ�εľ���
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
     *�������ٽ���ͼ��id
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


    //����ѡ��ͼ�η��õ���ǰ��
    panel.push_back(panel[id]);
    panel[id] = NULL;
    id = panel.size()-1;

    cout << "ѡ��  " << graphName[panel[id]->s] << '\n' << "RGB(" << panel[id]->conf.c.R
         << ", " << panel[id]->conf.c.G << ", " << panel[id]->conf.c.B << ")  "<< "���� " << minVal << '\n';
    //���ƾ���
    Point p1, p2;
    panel[id]->getRectangle(p1, p2);
    setRectangle(p1, p2);

    return id;
}

void Manager::cancelChoose()
{
    /*****************
     *ȡ��ͼ��ѡ��
    *****************/
    clearBoy();
}

/******************************************��ȡ�뱣��**************************************************/
void Manager::save()
{
    string name;
    cout << "�����ļ�����";
    cin >> name;
    name += ".dat";
    ofstream output(name.c_str());
    //����
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
    cout << "����ɹ���" << endl;
}

void Manager::read()
{
    string name;
    cout << "�����ļ�����";
    cin >> name;
    name += ".dat";
    fstream ifExist(name.c_str(), ios::in);
    if (!ifExist) {
        cout << "�ļ������ڣ�\n";
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
    cout << "��ȡ�ɹ���" << endl;
}
/*
    Shape s;   //��״
    bool ok;   //ͼ���Ƿ�������
    GraphConfig conf;  //��������
    vector<Point> pArray;  //�㼯

     Color c;
    LineSize lineSize = l3;  //�ߴ�ϸ
    bool isDashes = false;   //�Ƿ�����
    bool isFilled = false;
    bool frame = false;
*/

/*******************************��๤******************************/
//�����ָ��
void Manager::clearBoy()
{
    static int letsClear = 0;
    if (letsClear++ % clearDay != 0)  //û����������
        return;

    vector<Graph*> temp;
    for (int i = 0; i < panel.size(); i++)
        if (panel[i] != NULL) {
            temp.push_back(panel[i]);
            temp[temp.size()-1]->id = temp.size()-1;
        }
    panel = temp;
    cout << "ִ���ڴ�����\n";
}
