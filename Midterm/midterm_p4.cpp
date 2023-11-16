#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int n = 0;
    cin >> n;
    int** distance = new int* [n];
    for (int i = 0; i < n; i++)
    {
        distance[i] = new int [n];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> distance[i][j];
        }
    }
    int save = 0, count = 0, indexI = n+1, indexJ = n+1, maxSaveCount = 1, kCount = 0;
    int maxSave = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i >= j) continue;
            int kCount = 0;
            
            for (int k = 0; k < n; k++)
            {
                if (k == i || k == j) continue;
                if (distance[i][k] + distance[k][j] < distance[i][j])
                {
                    save = (distance[i][j] - (distance[i][k] + distance[k][j]));
                    cout << i << "," << j << "," << k << "\n";
                    // cout << count <<"\n";
                    cout << "save: " << save << "\n";
                    cout << "maxSave: " << maxSave << "\n";
                    if (indexI == i && indexJ == j)
                    {
                        if (save == maxSave && maxSave != 0)
                        {
                            kCount++;
                            maxSaveCount++;
                        }
                        if (save > maxSave)
                        {
                            maxSave = save;
                            kCount = 1;
                            maxSaveCount = 1;
                        }
                        if (maxSaveCount > 1)
                        {
                            maxSave *= maxSaveCount;
                        }
                    }
                    cout << "save: " << save << "\n";
                    cout << "maxSave: " << maxSave << "\n";
                    if (indexI != i || indexJ != j)
                    {
                        if (save == maxSave && maxSave != 0)
                        {
                            count++;
                            maxSave++;
                        }
                        if (save > maxSave)
                        {
                            maxSave = save;
                            count++;
                        }
                    }
                    cout << "count: " << count << "\n";
                    indexI = i;
                    indexJ = j;
                    // cout << count << "\n";
                }
                count += kCount;
            }
        }
    }
    cout << count << "," << maxSave;
}
