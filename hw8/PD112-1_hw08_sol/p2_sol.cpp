#include<iostream>
using namespace std;

class Point
{
private:
    int x;
    int y;
public:
    Point(int x, int y) : x(x), y(y) {}
friend class Polygon;
};

class Polygon
{
private:
    int pointCnt;
    Point** endPoints;
public:
    Polygon();
    Polygon(int pc, int x[], int y[]);
    Polygon(const Polygon& p);
    ~Polygon();
    void print();
    void movePoint(int index, int x, int y);
};

Polygon::Polygon()
{ 
    this->pointCnt = 0; 
    this->endPoints = nullptr; 
}

Polygon::Polygon(int pc, int x[], int y[])
{
    this->pointCnt = pc;
    this->endPoints = new Point*[pc];
    for(int i = 0; i < pc; i++)
        endPoints[i] = new Point(x[i], y[i]);
}

Polygon::Polygon(const Polygon& p)
{ 
    this->pointCnt = p.pointCnt;
    this->endPoints = new Point*[this->pointCnt];
    for(int i = 0; i < this->pointCnt; i++)
    	this->endPoints[i] = new Point(p.endPoints[i]->x, p.endPoints[i]->y);
}

Polygon::~Polygon()
{
    for(int i = 0; i < this->pointCnt; i++) {
        delete endPoints[i];
        endPoints[i] = nullptr;
    }
    delete [] endPoints;
    endPoints = nullptr;
}

void Polygon::print()
{
    cout << "(";
    for(int i = 0; i < this->pointCnt; i++)
    {
        cout << "(" << this->endPoints[i]->x << ", " << this->endPoints[i]->y << ")";
    }
    cout << ")";
}

void Polygon::movePoint(int index, int x, int y)
{
    this->endPoints[index]->x = x;
    this->endPoints[index]->y = y;
}

int main()
{
    int pointCnt = 0;
    cin >> pointCnt;
    int* x = new int[pointCnt];
    int* y = new int[pointCnt];
    for(int i = 0; i < pointCnt; i++)
        cin >> x[i];    
    for(int i = 0; i < pointCnt; i++)
        cin >> y[i];    
    
    Polygon p1(pointCnt, x, y);
    Polygon p2(p1);
    p2.movePoint(0, 0, 0);
    p1.print();
    cout << "\n";
    p2.print();
    delete [] x;
    x = nullptr;
    delete [] y;
    y = nullptr;
    
    return 0;
} 
