#include <iostream>
#include <string> 
using namespace std;

// class Date
// ==================================================
class Date
{
friend istream& operator>>(istream& os, Date& d);
friend ostream& operator<<(ostream& os, const Date& d);
private:    
    int year;
    int month;
    int day;
public:
    Date();
    Date(int year, int month, int day);
    int yearUntil(const Date& d) const;
    bool operator==(const Date& d) const;
    bool operator<=(const Date& d) const;
};
const Date TODAY(2023, 11, 21);

Date::Date() : year(0), month(0), day(0) 
{
}

Date::Date(int year, int month, int day) : year(year), month(month), day(day)  // constructor 限定
{
    this->year = year;  // 等價於這種寫法
    this->month = month;
    // 只有在一種情況下不行：ex. year 是 const, this.year會發生compilation error，因為 this.year值不能被更動
}

int Date::yearUntil(const Date& d) const
{
    int y = d.year - this->year;
    if(this->month > d.month || (this->month == d.month && this->day > d.day))
        y--;
    return y;
}

bool Date::operator==(const Date& d) const
{
    return (this->year == d.year && this->month == d.month && this->day == d.day);
} 

bool Date::operator<=(const Date& d) const
{
    if(this->year < d.year)
        return true;
    else if(this->year == d.year && this->month < d.month)
        return true;
    else if(this->year == d.year && this->month == d.month && this->day <= d.day)
        return true;
    return false;   
}
// ==================================================










// class Time
// ==================================================
class Time
{
friend istream& operator>>(istream& os, Time& t);
friend ostream& operator<<(ostream& os, const Time& t);
private:
    int hour;
    int minute;
    int second;
public:
    Time();
    Time(int hour, int minute, int second);
    bool isValidTime() const;
    bool operator<=(const Time& t) const;
};

Time::Time() : hour(0), minute(0), second(0)
{
}

Time::Time(int hour, int minute, int second) : hour(hour), minute(minute), second(second)
{
} 

bool Time::isValidTime() const
{
    return (0 <= this->hour && this->hour <= 23 && 
            0 <= this->minute && this->minute <= 59 &&
            0 <= this->second && this->second <= 59);
}

bool Time::operator<=(const Time& t) const
{
    if(this->hour < t.hour)
        return true;
    else if(this->hour == t.hour && this->minute < t.minute)
        return true;
    else if(this->hour == t.hour && this->minute == t.minute && this->second <= t.second)
        return true;
    return false;
}
// ==================================================










// class Animal
// ==================================================
class Animal
{
protected:
    int id;
    Date birthday;
    string name;
public:
    // constructor: specify the ID, birthday, and name of the animal
    Animal(int id, const Date& b, const string& n);  // 大 class 包小 class 時，小的需要有default constructor
    
    // call by reference: 省記憶體，但不小心改到b，就會連原本的date都會被改到，故加一個const來確保傳入的date(b)不會被改到

    // virtual destructor: ensure the child's destructor will be invoked
    virtual ~Animal();
    
    // return the ID of the animal
    int getID() const;
    
    // return the age of the animal
    int getAge() const;
    
    // return the name of the animal
    string getName() const;
    
    // set the name of the animal to "n"
    void setName(const string& n);
    
    // print the name, birthday, and age of the animal
    // this function is overridden by the child class of Animal
    virtual void print() const;
};

Animal::Animal(int id, const Date& b, const string& n) : id(id), birthday(b), name(n)
{  // direct assignment of types int, Datem and string is fine
}

Animal::~Animal()
{
}

int Animal::getID() const  // const: 不會改到 member variable ex. id, birthday, name
{
    return this->id;   
}

int Animal::getAge() const
{
    return this->birthday.yearUntil(TODAY);   
}

string Animal::getName() const
{
    return this->name;
}

void Animal::setName(const string& n)
{
    this->name = n;
}

void Animal::print() const
{
    cout << this->name << ',' << this->birthday << ',' << this->getAge();
}
// ==================================================










// class DisplayAnimal
// ==================================================
class DisplayAnimal : public Animal  // 繼承時通常都會寫 public
{
private:
    Time start;
    Time end;    
    bool hasDisplayTime;  // true if the animal has display time, false otherwise
public:
    // constructor: specify the ID, birthday, and name of the display animal
    DisplayAnimal(int id, const Date& b, const string& n);
    
    // set the display time of the display animal
    // if the start time or end time is not valid, nothing will be set 
    void setDisplayTime(const Time& start, const Time& end);
    
    // return the display time of the display animal using the call-by-reference mechanism
    void getDisplayTime(Time& start, Time& end) const;
    
    // print the name, birthday, age, and display time of the display animal
    // the keyword "override" is a reminder that this function is overridden
    void print() const override;
};
// child construtor 後面就塞一個適合的 parent constructor
// 因為他會呼叫 parent 的 constructor
DisplayAnimal::DisplayAnimal(int id, const Date& b, const string& n) : Animal(id, b, n), hasDisplayTime(false)
{  // the parent's constructor Animal(id, b, n) is invoked
}

void DisplayAnimal::setDisplayTime(const Time& start, const Time& end)
{
    // better implementation: exception handling
    if(start.isValidTime() && end.isValidTime() && start <= end)
    {
        this->start = start;
        this->end = end;
        this->hasDisplayTime = true;
    }
}

void DisplayAnimal::getDisplayTime(Time& start, Time& end) const
{
    start = this->start;
    end = this->end;
}

void DisplayAnimal::print() const 
{
    Animal::print();  // utilize the parent's print() function
    if(this->hasDisplayTime)
        cout << ',' << this->start << ',' << this->end << '\n';
    else
        cout << ",none\n";
}
// ==================================================










// global function headers and global variables
// ==================================================
void printFourDigit(int n);
void printTwoDigit(int n);

// return the index of the first animal in "animals" whose ID matches "id"
int findTargetByID(DisplayAnimal* animals[], int cnt, int id);

// return the index of the first animal in "animals" whose name matches "name"
int findTargetByName(DisplayAnimal* animals[], int cnt, const string& name);

const int MAX_ANIMAL_CNT = 100;
const int NOT_FOUND_CODE = -1;



// main function
// ==================================================
int main()
{
    int t = 0;
    cin >> t;
    cin.ignore();
    
    int animalCnt = 0;
    DisplayAnimal* animals[MAX_ANIMAL_CNT];
    
    int id = 0;
    char task = 0;
    string name;
    
    for(int i = 0; i < t; i++)
    {
        cin >> task;
        if(task == 'C')
        {
            // the cin operator is overloaded for Date to enhance the readability of the code
            Date birthday;
            cin >> id >> name >> birthday;
            
            // since no animal will be named "Unknown",
            // we can safely assign "Unknown" to unnamed animals without any error            
            animals[animalCnt] = new DisplayAnimal(id, birthday, name);
            animalCnt++;
        }
        else if(task == 'S')
        {
            Time start, end;
            cin >> name >> start >> end;  // cin is overloaded for Time
            int aID = findTargetByName(animals, animalCnt, name);
            if(aID != NOT_FOUND_CODE)
                animals[aID]->setDisplayTime(start, end);
        }
        else if(task == 'N')
        {
            cin >> id >> name;
            int aID = findTargetByID(animals, animalCnt, id);
            if(aID != NOT_FOUND_CODE)
                animals[aID]->setName(name);
        }
    }
    /*
    for(int i = 0; i < animalCnt; i++)
        animals[i]->print();
    */
    cin >> task >> name;
    
    cout << animalCnt << '\n';
    
    int toPrintID = findTargetByName(animals, animalCnt, name);
    animals[toPrintID]->print();
    
    for(int i = 0; i < animalCnt; i++)
        delete animals[i];  // not delete [] animals[i]
    
    return 0;
}



// global function implemetations
// ==================================================
void printFourDigit(int n)
{
    int zeroCnt = 4 - to_string(n).length();
    for(int i = 0; i < zeroCnt; i++)
        cout << "0";
    cout << n;
    // alternative implementation: use setw(4) and setfill('0') from <iomanip>
}

void printTwoDigit(int n)
{
    cout << (n < 10 ? "0" : "") << n;
}

istream& operator>>(istream& os, Date& d)
{
    // input format: yyyy/mm/dd
    os >> d.year;
    os.ignore();
    os >> d.month;
    os.ignore();
    os >> d.day;
    return os;
}

ostream& operator<<(ostream& os, const Date& d)
{
    printFourDigit(d.year);
    cout << "/";
    printTwoDigit(d.month);
    cout << "/";
    printTwoDigit(d.day);
    return os;
}

istream& operator>>(istream& os, Time& t)
{
    // input format: hh:mm:ss
    os >> t.hour;
    os.ignore();
    os >> t.minute;
    os.ignore();
    os >> t.second;
    return os;
}

ostream& operator<<(ostream& os, const Time& t)
{
    printTwoDigit(t.hour);
    cout << ":";
    printTwoDigit(t.minute);
    cout << ":";
    printTwoDigit(t.second);
    return os;
}

int findTargetByID(DisplayAnimal* animals[], int cnt, int id)
{
    for(int i = 0; i < cnt; i++)
    {
        if(id == animals[i]->getID())
            return i;
    }
    return NOT_FOUND_CODE;
}

int findTargetByName(DisplayAnimal* animals[], int cnt, const string& name)
{
    for(int i = 0; i < cnt; i++)
    {
        if(name == animals[i]->getName())
            return i;
    }
    return NOT_FOUND_CODE;
}

