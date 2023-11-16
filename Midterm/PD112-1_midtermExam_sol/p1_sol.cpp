#include <iostream>
#include <cmath>
using namespace std;

const int DATE_CNT = 3;

struct Date {
    int month;
    int day;

    int between(Date d);
};

int getDaysOfMonth(int month);

int main() {
    Date date[DATE_CNT];
    int diff[DATE_CNT - 1] = {0};

    for (int i = 0; i < DATE_CNT; i++)
        cin >> date[i].month >> date[i].day;
    
    diff[0] = date[0].between(date[1]);
    diff[1] = date[1].between(date[2]);

    if (diff[0] < diff[1])
        cout << diff[0];
    else cout << diff[1];

    return 0;
}

// calculate the days between two dates
int Date::between(Date d) {
    if (month == d.month)
        return abs(day - d.day) - 1;
    else {
        int earlyMonth = 0, earlyDay = 0, lateMonth = 0, lateDay = 0;
        if (month < d.month) {
            earlyMonth = month;
            earlyDay = day;
            lateMonth = d.month;
            lateDay = d.day;
        } else {
            earlyMonth = d.month;
            earlyDay = d.day;
            lateMonth = month;
            lateDay = day;
        }

        int days = getDaysOfMonth(earlyMonth) - earlyDay;
        int currentMonth = earlyMonth + 1;
        while (currentMonth != lateMonth) {
            days += getDaysOfMonth(currentMonth);
            currentMonth++;
        }
        days += lateDay - 1;
    
        return days;
    }
    
}

// return how many days is in a specific month
int getDaysOfMonth(int month) {
    if (month == 2) return 28;
    else if (month == 1 || month == 3 || month == 5 || month == 7 
        || month == 8 || month == 10 || month == 12)
        return 31;
    else return 30;
}