#include <iostream>
#include <cstdlib> // 用於abs函數
#include <limits>  // 為了使用 INT_MAX
using namespace std;

// 函數來計算某個月份到年初的總天數
int daysTillDate(int month, int day) {
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int totalDays = 0;
    for (int i = 1; i < month; ++i) {
        totalDays += daysInMonth[i];
    }
    totalDays += day;
    return totalDays;
}

int main() {
    // 讀入日期數量
    int n;
    cin >> n;

    // 假設最多只有100個日期
    int months[100], days[100]; 

    for (int i = 0; i < n; ++i) {
        cin >> months[i] >> days[i];
    }

    int minDiff = 366; // 最小天數差
    for (int i = 0; i < n - 1; ++i) {
        int days1 = daysTillDate(months[i], days[i]);
        int days2 = daysTillDate(months[i + 1], days[i + 1]);
        int diff = abs(days2 - days1) - 1;
        minDiff = min(minDiff, diff);
    }

    cout << minDiff << endl;

    return 0;
}
