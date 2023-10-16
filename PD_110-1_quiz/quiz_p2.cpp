#include <iostream>
using namespace std;

int main()
{
    int n = 0, q = 0;
    cin >> n >> q;

    int* p = new int [n];
    int* x = new int [n];

    for (int i = 0; i < n; i++) cin >> p[i];
    for (int i = 0; i < n; i++) cin >> x[i];

    for (int i = 0; i < n; i++)
    {
        if ((x[i] == 1 && q > p[i]) || (x[i] == 0 && p[i] <= q / 2))
            q -= p[i];
            
        cout << q;
        if (i != n - 1) cout << ",";
    }
}
