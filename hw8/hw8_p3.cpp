#include <iostream>
#include <cstdlib>
using namespace std;

class Point
{
private:
    int x;
    int y;
public:
    Point(int x, int y) : x(x), y(y) {}
    void print();
friend class Polygon;
};

void Point::print()
{
    cout << "(" << this->x << ", " << this->y << ")";
}

class Polygon
{
private:
    int pointCnt;
    Point** endPoints;
public:
    Polygon();
    Polygon(int pc, int x[], int y[]);
    ~Polygon();
    void print();
    void movePoint(int index, int x, int y);
    bool operator==(const Polygon& p);
    Point operator[](int index);
    const Polygon& operator=(const Polygon& p);
};

Polygon::Polygon()
{ 
    this->pointCnt = 0;  // Initialize
    this->endPoints = nullptr;  // Initialize
}

Polygon::Polygon(int pc, int x[], int y[])
{
    this->pointCnt = pc;
    this->endPoints = new Point*[pc];
    for(int i = 0; i < pc; i++)
        endPoints[i] = new Point(x[i], y[i]);  // 每個端點
}
// --------------- Problem 2 -----------------
// Polygon::Polygon(const Polygon& p)
// {
//     pointCnt = p.pointCnt;  // 這行不加會錯      （*想）
//     this->endPoints = new Point*[pointCnt]; 
//     for (int i = 0; i < p.pointCnt; i++)
//         endPoints[i] = new Point(p.endPoints[i]->x, p.endPoints[i]->y);
// }

Polygon::~Polygon()  // Destructor
{
    for(int i = 0; i < this->pointCnt; i++)
    {
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
        cout << "(" << this->endPoints[i]->x
             << "," << this->endPoints[i]->y << ")";
    }
    cout << ")";
}

void Polygon::movePoint(int index, int x, int y)
{
    this->endPoints[index]->x = x;
    this->endPoints[index]->y = y;
}

// -------------------- Problem 3 ---------------------------
bool Polygon::operator==(const Polygon& p)
{
    if (this->pointCnt != p.pointCnt) return false;
    else
    {
        for (int i = 0; i < this->pointCnt; i++)
        {
            if (this->endPoints[i]->x != p.endPoints[i]->x || this->endPoints[i]->y != p.endPoints[i]->y)
                return false;
        }
    }
    return true;
}

Point Polygon::operator[](int index)
{
    if (index < 0 || index >= this->pointCnt) exit(1);
    return *this->endPoints[index];  // this.endPoints[index] 回傳的是一個 address，但我們需要的是回傳一個 Point
}

const Polygon& Polygon::operator=(const Polygon& p)  // const: 被 return 的東西就不能放在等號左邊，就可以避免 (a1 = a2) = a3 這種情況
{
    if (this->pointCnt != p.pointCnt)
    {
        for (int i = 0; i < this->pointCnt; i++){
            delete [] this->endPoints[i];
        }
        delete [] this->endPoints;

        this->pointCnt = p.pointCnt;
        this->endPoints = new Point*[pointCnt];
    }
    for (int i = 0; i < pointCnt; i++)
        endPoints[i] = new Point(p.endPoints[i]->x, p.endPoints[i]->y);
    return *this;
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
    Polygon p2;
    p2 = p1;
    if(p2 == p1)
        cout << "Identical\n";
    else
        cout << "Different\n";
    p2[0].print();
    cout << "\n";
    p2.movePoint(0, 0, 0);
    p1[0].print();
    cout << "\n";
    if(p2 == p1)
        cout << "Identical\n";
    else
        cout << "Different\n";
    delete[] x;
    x = nullptr;
    delete[] y;
    y = nullptr;
    
    return 0;
}