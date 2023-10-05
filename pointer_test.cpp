#include<iostream>
using namespace std;

int main()
{
    int a[5] = {0};
    for (int i = 0; i < 5; i++)
        cin >> a[i];
    int* p = a;
    for (int i = 0; i < 5; i++) {
        *p += 3;
        p++;
    }
    for (int i = 0; i < 5; i++)
        cout << a[i] << "";
    return 0;
}