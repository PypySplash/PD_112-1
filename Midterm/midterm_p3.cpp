#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int n = 0, K = 0;
    cin >> n >> K;

    int** xycp = new int* [n];
    for (int i = 0; i < n; i++) xycp[i] = new int [4];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 4; j++) cin >> xycp[i][j];
    }
    int revenue = 0, maxRev = 0, tempRev = 0, indexI = 0;
    for (int i = 0; i < n; i++)
    {
        if (xycp[i][0] < xycp[i][1])
        {
            if (K > xycp[i][1] - xycp[i][0])
            {
                tempRev = xycp[i][3] * xycp[i][1] - xycp[i][2] * xycp[i][1];
            }
            if (K < xycp[i][1] - xycp[i][0])
            {
                tempRev = xycp[i][3] * (xycp[i][0] + K) - xycp[i][2] * (xycp[i][0] + K);
            }
        }
        if (tempRev > maxRev)
        {
            maxRev = tempRev;
            indexI = i;
        }
    }
    // cout << maxRev << "\n";
    // cout << indexI << "\n";
    for (int i = 0; i < n; i++)
    {
        
        if (i == indexI && maxRev != 0)
        {
            revenue += maxRev;
        }
        else
            revenue += xycp[i][3] * min(xycp[i][0], xycp[i][1]) - xycp[i][2] * xycp[i][0];
    }

    cout << revenue;

    for (int i = 0; i < n; i++){
        delete [] xycp[i];
    }

    delete [] xycp;
    xycp = nullptr;
}
