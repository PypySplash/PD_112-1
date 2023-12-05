#include <iostream>
using namespace std;
#include <cstdio> // 包含 sscanf 函數

const int CURRENT_YEAR = 2023;
const int CURRENT_MONTH = 11;
const int CURRENT_DAY = 21;

const int MAX_ANIMALS = 101;



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



class Animal 
{
friend class Zoo;
protected:
    int id;
    Date birthday;
    string name;
public:
    Animal(int id, const Date& b, const string& n);
    Animal(int id, Date b);
    virtual ~Animal();  // virtual destructor: ensure the child's destructor will be invoked
    int getAge() const;
    int getId() const;
    string getName() const;
    void setName(const string& n);
    virtual void print() const;
    virtual bool isShowAnimal() const;
};

Animal::Animal(int id, const Date& b, const string& n)
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
void Animal::setName(const string& n) {
    this->name = n;
}
void Animal::print() const {
    cout << this->getName() << "," 
         << this->birthday.year << "/"
         << formatWithLeadingZero(this->birthday.month) << '/' 
         << formatWithLeadingZero(this->birthday.day) << ","
         << this->getAge();
}
bool Animal::isShowAnimal() const {
    // this function is only overridden by ShowAnimal
    /*
        since the function is virtual... 
        if the calling object is not of type ShowAnimal, the parent's implementation returns false;
        if the calling object is of type ShowAnimal, the overridden implementaion in ShowAnimal returns true
    */
    return false;
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
    DisplayAnimal(int id, const Date& b, const string& n);
    // DisplayAnimal(int id, Date b);
    ~DisplayAnimal();
    void setDisplayTime(const Time& start, const Time& end);
    void getDisplayTime(Time& start, Time& end) const;
    void print() const override;
};

DisplayAnimal::DisplayAnimal(int id, const Date& b, const string& n)
  : Animal(id, b, n), isTimeSet(false)
{  // the parent's constructor Animal(id, b, n) is invoked
}
// DisplayAnimal::DisplayAnimal(int id, Date b)
//   : Animal(id, b)
// {
// }
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
    Animal::print();
    // cout << this->getName() << ","
    //      << this->birthday.year << "/"
    //      << formatWithLeadingZero(this->birthday.month) << "/"
    //      << formatWithLeadingZero(this->birthday.day) << ","
    //      << this->getAge() << ",";
    if (isTimeSet) {
        cout << ","
             << formatWithLeadingZero(this->start.hour) << ":" 
             << formatWithLeadingZero(this->start.minute) << ":" 
             << formatWithLeadingZero(this->start.second) << ","
             << formatWithLeadingZero(this->end.hour) << ":" 
             << formatWithLeadingZero(this->end.minute) << ":" 
             << formatWithLeadingZero(this->end.second) << endl;
    } else {
        cout << ",none" << endl;
    }
}



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



class ShowAnimal : public Animal {
private :
    Date** showDates;
    int showCnt;
    int currentCapacity;  // 当前数组容量
    static const int CAPACITY_INCREMENT = 10;  // 容量增量
public :
    ShowAnimal(int id, const Date& b, const string& n);
    // ShowAnimal(int id, Date b);
    ShowAnimal(const ShowAnimal& sa);  // header of copy constructor
    ~ShowAnimal();
    const ShowAnimal& operator=(const ShowAnimal& sa);
    void addShowDate(const Date& d);
    int getShowCnt() const;
    int getShowCnt(const Date& start, const Date& end) const;
    void print(const Date& start, const Date& end) const;
    void print() const override;
    bool isShowAnimal() const override;
};

ShowAnimal::ShowAnimal(int id, const Date& b, const string& n)
  : Animal(id, b, n), showCnt(0), showDates(nullptr), currentCapacity(CAPACITY_INCREMENT) {
    showDates = new Date*[currentCapacity];  // 分配初始容量
}
// ShowAnimal::ShowAnimal(int id, Date b)
//   : Animal(id, b), showCnt(0), showDates(nullptr), currentCapacity(CAPACITY_INCREMENT) {
//     showDates = new Date*[currentCapacity];  // 分配初始容量
// }
ShowAnimal::ShowAnimal(const ShowAnimal& sa)  // copy constructor
 : Animal(sa.getId(), sa.birthday, sa.getName())  // 因 parent class 沒有 default copy constructor，故這邊需加這行
{
    this->showCnt = sa.showCnt;
    this->currentCapacity = sa.currentCapacity;  // 您可能也需要複製容量
    this->showDates = new Date* [this->currentCapacity];
    for (int i = 0; i < this->showCnt; i++) {
        this->showDates[i] = new Date(*(sa.showDates[i]));
    }
}
ShowAnimal::~ShowAnimal()
{
    for (int i = 0; i < showCnt; i++) {
        delete showDates[i];
    }
    delete[] showDates;
}
const ShowAnimal& ShowAnimal::operator=(const ShowAnimal& sa)
{
    if (this != &sa)
    {
        for (int i = 0; i < this->showCnt; i++) {
            delete this->showDates[i];
        }
        delete [] this->showDates;
        this->id = sa.id;
        this->birthday = sa.birthday;
        this->name = sa.name;
        this->showCnt = sa.showCnt;
        this->currentCapacity = sa.currentCapacity;
        this->showDates = new Date*[this->currentCapacity];
        for(int i = 0; i < this->showCnt; i++)
            this->showDates[i] = new Date(*(sa.showDates[i]));
    }
    return *this;
}
void ShowAnimal::addShowDate(const Date& d)
{
    if (d.year < this->birthday.year || 
       (d.year == this->birthday.year && d.month < birthday.month) || 
       (d.year == birthday.year && d.month == birthday.month && d.day < birthday.day)) {
        return;
    }
    // 检查日期是否重复或早于出生日期
    for (int i = 0; i < showCnt; i++) {
        if ((showDates[i]->year == d.year && showDates[i]->month == d.month && showDates[i]->day == d.day) || 
            (d.year < this->birthday.year || 
            (d.year == this->birthday.year && d.month < birthday.month) || 
            (d.year == birthday.year && d.month == birthday.month && d.day < birthday.day))) {
            return; // 日期重复或早于出生日期，跳过
        }
    }

    // 当数组已满时扩展数组
    if (showCnt >= currentCapacity) {
        int newCapacity = currentCapacity * 2; // 容量翻倍
        Date** newShowDates = new Date*[newCapacity];
        for (int i = 0; i < showCnt; i++) {
            newShowDates[i] = showDates[i];
        }
        delete[] showDates;
        showDates = newShowDates;
        currentCapacity = newCapacity;
    }

    // 添加新日期
    this->showDates[this->showCnt] = new Date(d);
    this->showCnt++;
}
int ShowAnimal::getShowCnt() const {
    return this->showCnt;
}
int ShowAnimal::getShowCnt(const Date& start, const Date& end) const
{
    int count = 0;
    for (int i = 0; i < this->showCnt; i++) {
        // 检查日期是否在指定范围内
        if ((showDates[i]->year > start.year || 
            (showDates[i]->year == start.year && showDates[i]->month > start.month) ||
            (showDates[i]->year == start.year && showDates[i]->month == start.month && showDates[i]->day >= start.day)) &&
            (showDates[i]->year < end.year || 
            (showDates[i]->year == end.year && showDates[i]->month < end.month) ||
            (showDates[i]->year == end.year && showDates[i]->month == end.month && showDates[i]->day <= end.day))) {
            count++;
        }
    }
    return count;
}
void ShowAnimal::print() const
{
    Animal::print();  // utilize the parent's print() function
    cout << "," << this->showCnt << endl;
}
void ShowAnimal::print(const Date& start, const Date& end) const
{
    Animal::print();  // utilize the parent's print() function
    cout << "," << this->getShowCnt(start, end) << endl;
}

bool ShowAnimal::isShowAnimal() const {
    return true;
}



const int ZOO_CAP = 100;
class Zoo {
private :
    int displayAnimalCnt;
    int showAnimalCnt;
    Animal* animals[ZOO_CAP];  // using polymorphism:
    // ex. 拿 Animal 的指標去指向 DA or SA
    // i.e. 拿 parent 的指標去指 child object => polymorphism 的定義
public :
    Zoo();  // default constructor: set the number of animals to zero
    ~Zoo();  // destructor: delete dynamic objects/animals (those constructed by the syntax "new")
    // Zoo(const Zoo& z);
    // const Zoo& operator=(const Zoo& z);
    int getDisplayAnimalCnt() const;
    int getShowAnimalCnt() const;
    void setName(int id, string n);
    void setDisplayTime(string name, const Time& start, const Time& end);
    void addShowDate(string name, const Date& d);

    bool addAnimal(const Animal* a, bool isShowAnimal);
    void print() const;
    // return a pointer to the show animal with the largest number of shows participated in;
    // if case of a tie, the animal with the smaller ID is selected
    const Animal* findMostBusyShowAnimal() const;
};
Zoo::Zoo()
  : displayAnimalCnt(0), showAnimalCnt(0)
{
    for (int i = 0; i < ZOO_CAP; i++) {
        this->animals[i] = nullptr;
    }
}
Zoo::~Zoo()
{
    int totalCnt = this->displayAnimalCnt + this->showAnimalCnt;
    for (int i = 0; i < totalCnt; i++) {
        delete this->animals[i];
    }
}
int Zoo::getDisplayAnimalCnt() const {
    return this->displayAnimalCnt;
}
int Zoo::getShowAnimalCnt() const {
    return this->showAnimalCnt;
}
bool Zoo::addAnimal(const Animal* a, bool isShowAnimal)
{
    int totalCnt = this->displayAnimalCnt + this->showAnimalCnt;
    if (totalCnt >= ZOO_CAP) {
        return false;
    }
    else
    {
        if (isShowAnimal)
        {
            this->animals[totalCnt] = new ShowAnimal(a->id, a->birthday, a->name);
            showAnimalCnt++;
        }
        else
        {
            this->animals[totalCnt] = new DisplayAnimal(a->id, a->birthday, a->name);
            displayAnimalCnt++;
        }
        return true;
    }
}
void Zoo::setName(int id, string n)
{
    int totalCnt = this->displayAnimalCnt + this->showAnimalCnt;
    for (int i = 0; i < totalCnt; i++)
    {
        if (id == this->animals[i]->getId())
        {
            this->animals[i]->setName(n);
            break;
        }
    }
}
void Zoo::setDisplayTime(string name, const Time& start, const Time& end)
{
    int totalCnt = this->displayAnimalCnt + this->showAnimalCnt;
    for (int i = 0; i < totalCnt; i++) {
        if (name == this->animals[i]->getName() && !this->animals[i]->isShowAnimal()) {
            // to access the function "setDisplayTime" defined in DisplayAnimal (NOT in Animal),
            // we have to cast Animal* to DisplayAnimal*
                // remark 1: dynamic_cast is typically used for handling polymorphism;
                //           it converts a pointer of the parent class to a pointer of the child class
                // remark 2: we may move the defition of "setDisplayTime" to Animal,
                //           and make it a pure virtual function that will be overridden by DisplayAnimal;
                //           dynamic_cast is not needed for this strategy
            dynamic_cast<DisplayAnimal*>(this->animals[i])->setDisplayTime(start, end);
            break;
        }
    }
}
void Zoo::addShowDate(string name, const Date& d)
{
    
    int totalCnt = this->displayAnimalCnt + this->showAnimalCnt;
    for (int i = 0; i < totalCnt; i++)
    {
        if (name == this->animals[i]->getName() && this->animals[i]->isShowAnimal())
        {
            dynamic_cast<ShowAnimal*>(this->animals[i])->addShowDate(d);
            return;
        }
    }
}
void Zoo::print() const
{
    int totalCnt = this->displayAnimalCnt + this->showAnimalCnt;
    cout << totalCnt << "\n";
    for (int i = 0; i < totalCnt; i++) {
        this->animals[i]->print();
        // with late binding and virtual functions,
        // now parent's print() function is virtual, 
        // allowing the child's implementation to be invoked
    }
}
const Animal* Zoo::findMostBusyShowAnimal() const
{
    // assume there is at least a show animal in the zoo
    // better implementation: exception handling
    int opt = -1;
    for(int i = 0; i < this->displayAnimalCnt + this->showAnimalCnt; i++)
    {
        if(this->animals[i]->isShowAnimal())
        {
            if(opt == -1)
                opt = i;
            else
            {
                int curShowCnt = dynamic_cast<ShowAnimal*>(this->animals[i])->getShowCnt();
                int optShowCnt = dynamic_cast<ShowAnimal*>(this->animals[opt])->getShowCnt();
                int curID = this->animals[i]->getId();
                int optID = this->animals[opt]->getId();
                if(curShowCnt > optShowCnt || (curShowCnt == optShowCnt && curID < optID))
                    opt = i;
            }
        }
    }
    return this->animals[opt]; 
}



int main()
{
    Zoo myZoo;

    int t = 0;
    cin >> t;
    // DisplayAnimal** displayAnimalPtr = new DisplayAnimal*[MAX_ANIMALS];
    // ShowAnimal** showAnimalPtr = new ShowAnimal*[MAX_ANIMALS];
    // int displayAnimalCnt = 0;
    // int showAnimalCnt = 0;

    for (int i = 0; i < t; i++)
    {
        char record;
        cin >> record;

        if (record == 'C')
        {
            string type;
            cin >> type;
            int id;
            string name;
            char dateStr[11];
            cin >> id >> name >> dateStr;
            Date birthday = parseDate(dateStr);

            if (type == "Show")
            {
                // since "addAnimal" perform a deep copy of the given show/display animal,
                // there is no concern about the local variable "sa/da" being destroyed after the if-block 
                ShowAnimal sa(id, birthday, name);
                myZoo.addAnimal(&sa, true);
                // myZoo.addAnimal(id, birthday, name, true);
                // myZoo.addAnimal(&sa, true);  // true = isShowAnimal
                // showAnimalPtr[showAnimalCnt++] = new ShowAnimal(id, showDate, name);
            }
            if (type == "Display")
            {
                DisplayAnimal da(id, birthday, name);
                myZoo.addAnimal(&da, false);
                // myZoo.addAnimal(id, birthday, name, false);
                // myZoo.addAnimal(&da, false);  // false = !isShowAnimal
                // displayAnimalPtr[displayAnimalCnt++] = new DisplayAnimal(id, birthday, name);
            }
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

            myZoo.setDisplayTime(name, startTime, endTime);
        }

        if (record == 'N')
        {
            int id;
            string newName;
            cin >> id >> newName;

            myZoo.setName(id, newName);
        }

        if (record == 'A')
        {
            string name;
            char showDateStr[11];
            cin >> name >> showDateStr;
            Date showDate = parseDate(showDateStr);

            myZoo.addShowDate(name, showDate);
        }
    }

    myZoo.print();
    myZoo.findMostBusyShowAnimal()->print();
}
