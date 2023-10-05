#include <iostream>
#include <climits>
using namespace std;

int main() {
    
    // 淨上車人數 z 有可能全部皆為負數
    int n = 0, w = 0, y = 0, x = 0, z = INT_MIN, temp = 0;
    // cout << "Enter n, w: \n";
    cin >> n >> w;

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
        w += xArray[i];
        w -= yArray[i];

        temp = xArray[i] - yArray[i];
        if (temp > z)
            z = temp;
    }

    cout << w << "," << z << "\n";
}
