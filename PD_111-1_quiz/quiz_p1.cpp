#include <iostream>
using namespace std;

int main()
{
    int x = 0, y = 0, z = 0;
    cin >> x >> y >> z;
    
    if (x == y)
    {
        if (y == z) cout << 1;
        else cout << 3;
    }
    else if (x != y) // 這裡還有 x = z != y 要考慮
    {
        if (y != z)
        {
            if (x == z) cout << 3;
            else cout << 2;
        }
        else cout << 3;
    }
}
