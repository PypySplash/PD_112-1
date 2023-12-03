#include <iostream>
using namespace std;
#include <cstdio> // 包含 sscanf 函數

const int CURRENT_YEAR = 2023;
const int CURRENT_MONTH = 11;
const int CURRENT_DAY = 21;

const int MAX_ANIMALS = 101;
const int MAX_NAME_LEN = 21;

// 函數來添加前導零，用來處理 ex. 2023/1/5 -> 2023/01/05 這種情況
string formatWithLeadingZero(int number) {
    return (number < 10 ? "0" : "") + to_string(number);
}



struct Date {
    int year;
    int month;
    int day;
};
// 解析日期字符串，返回 Date 結構
Date parseDate(const char* dateStr) {
    Date date;
    sscanf(dateStr, "%d/%d/%d", &date.year, &date.month, &date.day);
    return date;
}



class Animal {
protected:
    int id;
    Date birthday;
    string name;
public:
    Animal(int id, Date b, string n);
    Animal(int id, Date b);
    ~Animal();
    int getAge() const;
    int getId() const;
    string getName() const;
    void setName(string n);
    virtual void print() const = 0;
};

Animal::Animal(int id, Date b, string n)
  : id(id), birthday(b), name(n)
{
}
Animal::Animal(int id, Date b)
  : id(id), birthday(b)
{
}
Animal::~Animal()
{
}
int Animal::getAge() const
{
    int age = 0;
    age = CURRENT_YEAR - birthday.year;
    // 如果生日尚未到達，年齡減一
    if (birthday.month > CURRENT_MONTH || (birthday.month == CURRENT_MONTH && birthday.day > CURRENT_DAY)) {
        age--;
    }
    return age;
}
int Animal::getId() const {
    return this->id;
}
string Animal::getName() const {
    return this->name;
}
void Animal::setName(string n) {
    this->name = n;
}



struct Time {
    int hour;   
    int minute; 
    int second; 
};
Time parseTime(const char* timeStr) {
    Time time;
    sscanf(timeStr, "%d:%d:%d", &time.hour, &time.minute, &time.second);
    return time;
}



class DisplayAnimal : public Animal {
private:
    Time start;
    Time end;
    bool isTimeSet; // 新增一個標誌來檢查時間是否被設定
public:
    DisplayAnimal(int id, Date b, string n);
    DisplayAnimal(int id, Date b);
    ~DisplayAnimal();
    void setDisplayTime(const Time& start, const Time& end);
    void getDisplayTime(Time& start, Time& end) const;
    void print() const;
};

DisplayAnimal::DisplayAnimal(int id, Date b, string n)
  : Animal(id, b, n)
{
}
DisplayAnimal::DisplayAnimal(int id, Date b)
  : Animal(id, b)
{
}
DisplayAnimal::~DisplayAnimal()
{
}
void DisplayAnimal::setDisplayTime(const Time& start, const Time& end)
{
    this->start = start;
    this->end = end;
    this->isTimeSet = true; // 標記展示時間已經被設定
}
void DisplayAnimal::getDisplayTime(Time& start, Time& end) const
{
    start = this->start;
    end = this->end;
}
void DisplayAnimal::print() const
{
    cout << this->getName() << "," 
         << this->birthday.year << "/" 
         << formatWithLeadingZero(this->birthday.month) << "/" 
         << formatWithLeadingZero(this->birthday.day) << ","
         << this->getAge() << ",";
    if (isTimeSet) {
        cout << formatWithLeadingZero(this->start.hour) << ":" 
                << formatWithLeadingZero(this->start.minute) << ":" 
                << formatWithLeadingZero(this->start.second) << ","
                << formatWithLeadingZero(this->end.hour) << ":" 
                << formatWithLeadingZero(this->end.minute) << ":" 
                << formatWithLeadingZero(this->end.second) << endl;
    } else {
        cout << "none" << endl;
    }
}


// 這邊跟 Time 有關的 function 其實可以包進 Time 的 class
// 檢查時間是否在00:00:00和23:59:59之間
bool isValidTime(const Time& time) {
    return time.hour >= 0 && time.hour <= 23 &&
           time.minute >= 0 && time.minute <= 59 &&
           time.second >= 0 && time.second <= 59;
}

// 檢查結束時間是否晚於開始時間
bool isEndTimeLater(const Time& start, const Time& end) {
    if (end.hour < start.hour) return false;
    if (end.hour == start.hour && end.minute < start.minute) return false;
    if (end.hour == start.hour && end.minute == start.minute && end.second <= start.second) return false;
    return true;
}



int main()
{
    int t = 0;
    cin >> t;
    DisplayAnimal** displayAnimalPtr = new DisplayAnimal*[MAX_ANIMALS];
    int animalCnt = 0;

    for (int i = 0; i < t; i++)
    {
        char record;
        cin >> record;
        if (record == 'C')
        {
            int id;
            string name;
            // char name[MAX_NAME_LEN];
            char birthdayStr[11];
            cin >> id >> name >> birthdayStr;
            Date birthday = parseDate(birthdayStr);
            // string name;
            displayAnimalPtr[animalCnt++] = new DisplayAnimal(id, birthday, name);
        }
        if (record == 'S')
        {
            string name;
            char startTimeStr[9], endTimeStr[9];
            cin >> name >> startTimeStr >> endTimeStr;
            Time startTime = parseTime(startTimeStr);
            Time endTime = parseTime(endTimeStr);

            // 檢查時間是否有效且結束時間是否晚於開始時間
            if (!isValidTime(startTime) || !isValidTime(endTime) || !isEndTimeLater(startTime, endTime)) {
                continue; // 如果時間無效或結束時間早於開始時間，則跳過此次處理
            }

            for (int j = 0; j < animalCnt; j++) 
            {
                DisplayAnimal *displayAnimal = dynamic_cast<DisplayAnimal*>(displayAnimalPtr[j]);
                if (displayAnimal && name == displayAnimal->getName())
                {
                    displayAnimal->setDisplayTime(startTime, endTime);
                    break; // 假設每個名稱是唯一的，找到後即可跳出迴圈
                }
            }
        }
        if (record == 'N')
        {
            int id;
            string newName;
            cin >> id >> newName;

            for (int j = 0; j < animalCnt; j++) {
                if (id == displayAnimalPtr[j]->getId()) { // 假設 Animal 類中有一個 getId() 方法
                    displayAnimalPtr[j]->setName(newName);
                    break; // 假設每個 ID 是唯一的，找到後即可跳出迴圈
                }
            }
        }
    }
    char inquiry;
    cin >> inquiry;
    if (inquiry == 'Q')
    {
        cout << animalCnt << endl;

        string name;
        cin >> name;

        for (int j = 0; j < animalCnt; j++) {
            if (name == displayAnimalPtr[j]->getName()) {
                displayAnimalPtr[j]->print();
                break; // 假設每個名稱是唯一的，找到後即可跳出迴圈
            }
        }
    }
    
    for (int i = 0; i < animalCnt; i++) {
        delete displayAnimalPtr[i];
    }
    delete[] displayAnimalPtr;
}
