# include <iostream>
# include <cstring>
using namespace std;



class Time
{
private:
    int hour;
    int minute;
    int second;
public:
    Time() : hour(0), minute(0), second(0) {}
    Time(int h, int m, int s)
    : hour(h), minute(m), second(s) {}
    void print();
    // 新增的取值函數
    int getHour() const { return hour; }
    int getMinute() const { return minute; }
    int getSecond() const { return second; }
};

void Time::print() {   
    cout << hour << ":" << minute << ":" << second << "\n";
}

// 輔助函數來格式化時間
string formatTimePart(int timePart, bool pad) {
    return pad && timePart < 10 ? "0" + to_string(timePart) : to_string(timePart);
}

// 模板函數用於打印時間
template <bool pad>
void printTime(const Time& t) {
    cout << formatTimePart(t.getHour(), pad) << ":"
         << formatTimePart(t.getMinute(), pad) << ":"
         << formatTimePart(t.getSecond(), pad);
}



class Event
{
private:
    char* name;
    Time start;
    Time end;
public:
    Event(char* n, Time* s, Time* t);
    ~ Event() {delete [] name;}
    void print();
    void setName(char* n);
};

Event::Event(char* n, Time* s, Time* t)
{
    int nameLen = strlen(n);
    name = new char[nameLen + 1];
    strcpy(name, n);
    start = *s;
    end = *t;
}

void Event::print()
{
    cout << "\"" << name << "\"\n";
    start.print();
    end.print();
}

void Event::setName(char* n)
{
    delete [] name;
    int nameLen = strlen(n);
    name = new char[nameLen + 1];
    strcpy(name, n);
}



int main()
{
    char n1 [] = "PD"; // (1)
    Time t1(14, 20, 0); // (2)
    Time t2(17, 20, 0); // (3)
    Event e1(n1, &t1, &t2); // (4)
    e1.print(); // (5)
    Event e2(e1); // (6)
    char n2[] = "Calculus"; // (7)
    e2.setName(n2); // (8)
    e2.print(); // (9)
    e1.print(); // (10)
    cout << "test\n"; // (11)

    Time t(14, 8, 4);
    // 使用模板函數打印時間
    printTime<false>(t); // 將輸出 "14:8:4"
    cout << endl;
    printTime<true>(t);  // 將輸出 "14:08:04"

    return 0; // (12)
}
