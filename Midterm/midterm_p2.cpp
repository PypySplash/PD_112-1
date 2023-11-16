#include <iostream>
using namespace std;

int main()
{
    int n = 0;
    cin >> n;
    int** date = new int* [n];
    for (int i = 0; i < n; i++)
    {
        date[i] = new int [2];
    }
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cin >> date[i][j];
        }
    }
    int difference = 0, minDiffer = 365;

    for (int i = 0; i < n; i++)
    {
        // if (date[i][0] > date[i+1][0])
        // {
        //     difference = (date[i][0] - date[i+1][0]) * 30 + date
        // }
        int difference = 0;
        if (i == 2) break;
        if (abs(date[i][0] - date[i + 1][0]) == 0)
        {
            difference = abs(date[i][1] - date[i + 1][1]) - 1;
        }
        if (abs(date[i][0] - date[i + 1][0]) > 0)
        {
            if (date[i][0] > date[i+1][0])  // 等等回來考慮跨多個月份
            {
                if (date[i+1][0] == 1 || date[i+1][0] == 3 || date[i+1][0] == 5 || date[i+1][0] == 7 || date[i+1][0] == 8 || date[i+1][0] == 10 || date[i+1][0] == 12)
                {
                    difference = 30 * (abs(date[i][0] - date[i + 1][0]) - 1) + (31 - date[i+1][1]) + date[i][1] - 1;
                }
                if (date[i+1][0] == 2 || date[i+1][0] == 4 || date[i+1][0] == 6 || date[i+1][0] == 9 || date[i+1][0] == 11)
                {
                    difference = 30 * (abs(date[i][0] - date[i + 1][0]) - 1) + (30 - date[i+1][1]) + date[i][1] - 1;
                }
            }
            if (date[i][0] < date[i+1][0])  // 等等回來考慮跨多個月份
            {
                if (date[i][0] == 1 || date[i][0] == 3 || date[i][0] == 5 || date[i][0] == 7 || date[i][0] == 8 || date[i][0] == 10 || date[i][0] == 12)
                {
                    difference = 30 * (abs(date[i][0] - date[i + 1][0]) - 1) + (31 - date[i][1]) + date[i+1][1] - 1;
                }
                if (date[i][0] == 2 || date[i][0] == 4 || date[i][0] == 6 || date[i][0] == 9 || date[i][0] == 11)
                {
                    difference = 30 * (abs(date[i][0] - date[i + 1][0]) - 1) + (30 - date[i][1]) + date[i+1][1] - 1;
                }
            }
        }
        if (difference < minDiffer)
        {
            minDiffer = difference;
        }
    }
    cout << minDiffer;

    for (int i = 0; i < n; i++)
    {
        delete [] date[i];
    }
    delete [] date;
    date = nullptr;
}
