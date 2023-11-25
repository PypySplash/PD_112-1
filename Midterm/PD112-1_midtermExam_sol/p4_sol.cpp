#include <iostream>
using namespace std;

int findFasterWay(int cityNum, int start, int end, const int** dis);

int main() {
    int cityNum = 0;
    cin >> cityNum;

    int** dis = new int*[cityNum]();
    for (int i = 0; i < cityNum; i++) {
        dis[i] = new int[cityNum]();
        for (int j = 0; j < cityNum; j++)
            cin >> dis[i][j];
    }

    int hasFasterWay = 0, totalSavedTime = 0;
    for (int i = 0; i < cityNum; i++) {
        for (int j = 0; j < cityNum; j++) {
            if (j <= i) continue;
            
            int savedTime = findFasterWay(cityNum, i, j, const_cast<const int**>(dis));
            if (savedTime == -1) continue;
            else {
                hasFasterWay++;
                totalSavedTime += savedTime;
            }
        }
    }

    cout << hasFasterWay << "," << totalSavedTime;

    for (int i = 0; i < cityNum; i++) {
        delete[] dis[i];
        dis[i] = nullptr;
    }
    delete[] dis;
    dis = nullptr;

    return 0;
}

// return -1 if there is no faster way
// otherwise return the most time can be saved
int findFasterWay(int cityNum, int start, int end, const int** dis) {
    int mostSavedTime = -1;
    int direct = dis[start][end];

    for (int i = 0; i < cityNum; i++) {
        if (i == start || i == end) continue;

        int indirect = dis[start][i] + dis[i][end];
        int savedTime = direct - indirect;
        if (savedTime > 0 && (mostSavedTime == -1 || savedTime > mostSavedTime))
            mostSavedTime = savedTime;
    }

    return mostSavedTime;
}
