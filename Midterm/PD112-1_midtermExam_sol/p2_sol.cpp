#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

struct Date {
    int month;
    int day;

    int between(Date d);
};

int getDaysOfMonth(int month);

int main() {
    int dateCnt = 0;
    cin >> dateCnt;

    Date* date = new Date[dateCnt]();
    int* diff = new int[dateCnt - 1]();

    for (int i = 0; i < dateCnt; i++)
        cin >> date[i].month >> date[i].day;
    
    for (int i = 0; i < dateCnt - 1; i++)
        diff[i] = date[i].between(date[i + 1]);

    cout << *min_element(diff, diff + dateCnt - 1);

    delete[] date;
    delete[] diff;
    date = nullptr;
    diff = nullptr;

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