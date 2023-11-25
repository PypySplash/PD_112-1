#include <iostream>
#include <cstdlib> // 用於abs函數
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
    // 輸入的三個日期
    int month1, day1, month2, day2, month3, day3;
    cin >> month1 >> day1;
    cin >> month2 >> day2;
    cin >> month3 >> day3;

    // 計算每個日期到年初的總天數
    int days1 = daysTillDate(month1, day1);
    int days2 = daysTillDate(month2, day2);
    int days3 = daysTillDate(month3, day3);

    // 計算兩個日期之間的天數差異
    int diff1 = abs(days2 - days1) - 1;
    int diff2 = abs(days3 - days2) - 1;

    // 輸出較小的天數差異
    cout << min(diff1, diff2) << endl;

    return 0;
}