#include <iostream>
using namespace std;

int main() {
    
    int n = 0, w = 0, y = 0, x = 0, z = 0, temp = 0;
    
    // cout << "Enter n, w: \n";
    cin >> n >> w;

    int* xArray = new int[n - 1];
    int* yArray = new int[n - 1];
    
    // 創建 xArray 並把輸入的上車人數 x 依序放入 array
    for (int i = 0; i < (n - 1); i++) {
        cin >> x;
        xArray[i] = x;
    }
    
    // 創建 yArray 並把輸入的下車人數 y 依序放入 array
    for (int i = 0; i < (n - 1); i++) {
        cin >> y;
        yArray[i] = y;
    }

    // 1. 計算 w（車上人數）
    // 2. 計算淨上車人數
    for (int i = 0; i < (n - 1); i++) {
        
        w -= yArray[i];
        if (w < 0) {
            temp = i + 1;  // ex. i = 1 為第 2 站
            break;
        }
        w += xArray[i];
    }

    cout << temp;
}
