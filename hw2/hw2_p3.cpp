#include <iostream>
using namespace std;
const int MAX_BUS_NUM = 50;
const int MAX_STATION_NUM = 20;

// function 的 prototype
void checkCorrectness(int n, int m, int K, const int bus[][2 * MAX_STATION_NUM - 1], int ret[]);

int main() {
    int n = 0, m = 0, K = 0;
    int bus[MAX_BUS_NUM][2 * MAX_STATION_NUM - 1] = {0};
    int ret[3] = {0};
    
    cin >> n >> m >> K;

    // bus[j][0] 放第 i 台巴士的起點上車人數
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < 2 * n - 1; i++)
            cin >> bus[j][i];
    }

    checkCorrectness(n, m, K, bus, ret);

    cout << ret[0] << "," << ret[1] << "," << ret[2] << "\n";

    return 0;
}

void checkCorrectness(int n, int m, int K, const int bus[MAX_BUS_NUM][2 * MAX_STATION_NUM - 1], int ret[]) {
    
    int w = 0;

    for (int j = 0; j < m; j++) {
        
        w = bus[j][0];

        // 每換檢查一台公車，countN, countC 需重置
        int countN = 0, countC = 0;

        for (int i = 1; i < n; i++) {
            
            w -= bus[j][i + n - 1];
            if (w < 0)
                countN++;

            // 乘客每一站上車人數從 bus[][1] 開始到 bus[][n - 1]
            // 乘客每一站下車人數從 bus[][n] 開始到 bus[][2 * (n - 1)]
            
            w += bus[j][i];
            if (w > K)
                countC++;
            
            if (countC != 0 || countN != 0)
                break;
        }
        
        if (countN == 0 && countC == 0) {
            ret[0] += 0;
            ret[1] += 0;
            ret[2] += 0;
        }
        else {
            if (countN != 0 && countC == 0)
                ret[0] += 1;
            if (countN == 0 && countC != 0)
                ret[1] += 1;
            if (countN != 0 && countC != 0)
                ret[2] += 1;
        }
    }
    
}
