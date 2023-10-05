#include <iostream>
using namespace std;

int main()
{
    int x1 = 0, x2 = 0, x3 = 0;
    cin >> x1 >> x2 >> x3;
    if (x1 > x2)
        swap(x1, x2);
    if (x1 > x3)
        swap(x1, x3);
    if (x2 > x3)
        swap(x2, x3);
    
    cout << x2;
}

void swap(int& x, int& y)
{
    if (x > y)
    {
        int temp = x;
        x = y;
        y = temp;
    }
}
