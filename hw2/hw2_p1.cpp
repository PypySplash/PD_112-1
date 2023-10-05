#include <iostream>
#include <climits>
using namespace std;

int main() {
    
    int n = 0, w = 0, K = 0, y = 0, x = 0, stationNumber = 0, countN = 0, countC = 0;
    char wrongType = '0';

    // cout << "Enter n, w, K: \n";
    cin >> n >> w >> K;

    int* xArray = new int[n - 1];
    int* yArray = new int[n - 1];
    
    // 創建 xArray 並把輸入的 x 依序放入 array
    for (int i = 0; i < (n - 1); i++) {
        cin >> x;
        xArray[i] = x;
    }
    
    // 創建 yArray 並把輸入的 y 依序放入 array
    for (int i = 0; i < (n - 1); i++) {
        cin >> y;
        yArray[i] = y;
    }

    // 1. 計算 w（車上人數）
    // 2. 計算淨上車人數
    for (int i = 0; i < (n - 1); i++) {
        
        w -= yArray[i];
        if (w < 0)
            countN ++;

        w += xArray[i];
        if (w > K)
            countC++;

        // 只需紀錄發生問題時，編號最小的站，故若已發生問題，就直接跳出迴圈
        if (countC != 0 || countN != 0) {
            stationNumber = i + 1;  // ex. i = 1 為第 2 站
            break;
        }
    }

    if (countN == 0 && countC == 0)
        cout << wrongType;
    else {
        if (countN != 0)
            wrongType = 'N';

        if (countC != 0) {
            wrongType = 'C';
            if (countN != 0)
                wrongType = 'B';
        }

        cout << stationNumber << "," << wrongType << "\n";
    }
}
