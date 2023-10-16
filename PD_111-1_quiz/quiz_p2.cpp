#include <iostream>
using namespace std;

int main()
{
    int n = 0;
    cin >> n;

    int* x = new int [n];
    for (int i = 0; i < n; i++) cin >> x[i];

    int count = 0, increaseCount = 0, decreaseCount = 0, answer = 0;
    bool breakPoint = 0;

    while (count < n - 1 && x[count] < x[count + 1])
    {
        increaseCount++;
        count++;
    }
    if (increaseCount == n - 1) answer = 1;
    else if (increaseCount != n - 1) 
    {
        breakPoint = 1;
        while (count < n - 1 && x[count] > x[count + 1])
        {
        decreaseCount++;
        count++;
        }
    }
    if (increaseCount + decreaseCount == n - 1 && breakPoint == 1) answer = 3;

    while (count < n - 1 && x[count] > x[count + 1])
    {
        decreaseCount++;
        count++;
    }
    if (decreaseCount == n - 1) answer = 2;
    
    if (answer == 0) answer = 4;
    cout << answer;
}
