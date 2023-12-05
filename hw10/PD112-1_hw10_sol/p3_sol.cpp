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

Date::Date(int year, int month, int day) : year(year), month(month), day(day) 
{
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
friend class Zoo;  // allow "Zoo" to access its animals' ID, birthday, and name
protected:
    int id;
    Date birthday;
    string name;
public:
    // constructor: specify the ID, birthday, and name of the animal
    Animal(int id, const Date& b, const string& n);
    
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
    
    // retrun true if the calling object is of type ShowAnimal, false otherwise
    // this function is only overridden by ShowAnimal
    virtual bool isShowAnimal() const;
};

Animal::Animal(int id, const Date& b, const string& n) : id(id), birthday(b), name(n)
{  // direct assignment of types int, Datem and string is fine
}

Animal::~Animal()
{
}

int Animal::getID() const
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

bool Animal::isShowAnimal() const
{
    // this function is only overridden by ShowAnimal
    /*
        since the function is virtual... 
        if the calling object is not of type ShowAnimal, the parent's implementation returns false;
        if the calling object is of type ShowAnimal, the overridden implementaion in ShowAnimal returns true
    */
    return false;
}
// ==================================================










// class DisplayAnimal
// ==================================================
class DisplayAnimal : public Animal
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











// class ShowAnimal
// ==================================================
class ShowAnimal : public Animal
{
private:
    Date** showDates;
    int showCnt;
    int curCapacity;  // the current length of "showDates"
    static const int maxCapacity = 20000;  // the maximum length of "showDates" 
    static const int initCapacity = 1;     // the initial length of "showDates" when a show animal is created;
                                           // other small values also work
    
    // double the current length of "showDates" when the capacity is full
    // this is an efficient way to dynamically adjust the length of an array
        // remark 1: this is similar to the implementation in the <vector> library  
        // remark 2: this function should be private and should not be invoked by other programmers
    void doubleCapacity();
public:
    // constructor: specify the ID, birthday, and name of the show animal
    ShowAnimal(int id, const Date& b, const string& n);
    
    // copy constructor: perform a deep copy as there is a member variable of type pointer
    ShowAnimal(const ShowAnimal& sa);
    
    // destructor: to delete to dynamically allocated memory
    ~ShowAnimal();
    
    // assignment operator: perform a deep copy as there is a member variable of type pointer
        // remark: THE RULE OF THREE - *****************************************************************************************************
        //         if we need to define any of the copy constructor, assignment operator, and destructor,
        //         we have to define all of them (regardless of whether other programmers actually need to use them)
    const ShowAnimal& operator=(const ShowAnimal& sa);
    
    // add a show date record for the show animal
    // if the show animal is not born before the given date or the date already exists, nothing will be added 
    void addShowDate(const Date& d);
    
    // return the number of shows that the show animal participated in
    int getShowCnt() const;
    
    // return the number of shows that the show animal participated in within the given period
    int getShowCnt(const Date& start, const Date& end) const;
    
    // print the name, birthday, age, and the number of shows in which the show animal has participated 
    // the keyword "override" is a reminder that this function is overridden
    void print() const override;
    
    // print the name, birthday, age, and the number of shows in which the show animal has participated within the given period
    // this function is NOT overriden one as the function signature is different from that of the parent's
    void print(const Date& start, const Date& end) const;
    
    // print all the details of the show animal 
    void debug() const;
    
    // always return true
    // the keyword "override" is a reminder that this function is overridden
    bool isShowAnimal() const override;
};

ShowAnimal::ShowAnimal(int id, const Date& b, const string& n) : Animal(id, b, n)
{  // the parent's constructor Animal(id, b, n) is invoked
    this->showCnt = 0;
    this->curCapacity = ShowAnimal::initCapacity;
    this->showDates = new Date*[curCapacity];
}

ShowAnimal::ShowAnimal(const ShowAnimal& sa) : Animal(sa.id, sa.birthday, sa.name)
{
    this->showCnt = sa.showCnt;
    this->curCapacity = sa.curCapacity;
    this->showDates = new Date*[this->curCapacity];
    for(int i = 0; i < this->showCnt; i++)
        this->showDates[i] = new Date(*(sa.showDates[i]));
}

ShowAnimal::~ShowAnimal()
{
    for(int i = 0; i < this->showCnt; i++)
        delete this->showDates[i];
    delete [] this->showDates;
}

const ShowAnimal& ShowAnimal::operator=(const ShowAnimal& sa)
{
    if(this != &sa)
    {
        for(int i = 0; i < this->showCnt; i++)
            delete this->showDates[i];
        delete [] this->showDates;
        // parent 的 member variable 要自己做，因為在 assignment operator 時不會去呼叫 parent 的
        this->id = sa.id;
        this->birthday = sa.birthday;
        this->name = sa.name;
        this->showCnt = sa.showCnt;
        this->curCapacity = sa.curCapacity;
        this->showDates = new Date*[this->curCapacity];
        for(int i = 0; i < this->showCnt; i++)
            this->showDates[i] = new Date(*(sa.showDates[i]));
    }
    return *this;
}

void ShowAnimal::doubleCapacity()
{
    this->curCapacity *= 2;
    if(this->curCapacity > ShowAnimal::maxCapacity)
        this->curCapacity = ShowAnimal::maxCapacity;
    
    Date** oldShowDates = this->showDates;
    this->showDates = new Date*[this->curCapacity];
    for(int i = 0; i < this->showCnt; i++)
        this->showDates[i] = oldShowDates[i];  // pointer assignment
    delete [] oldShowDates;  // remember to release the memory allocated previously 
}

void ShowAnimal::addShowDate(const Date& d)
{
    // better implementation: exception handling
    if(this->birthday <= d)
    {
        for(int i = 0; i < this->showCnt; i++)
        {
            if(*(this->showDates[i]) == d)
                return;            
        }
        if(this->showCnt >= this->curCapacity)  // here to determine whether to expand the length of "showDates"
            this->doubleCapacity();
        this->showDates[this->showCnt] = new Date(d);
        this->showCnt++;
    }
}

int ShowAnimal::getShowCnt() const
{
    return this->showCnt;
}

int ShowAnimal::getShowCnt(const Date& start, const Date& end) const
{
    int cnt = 0;
    for(int i = 0; i < this->showCnt; i++)
    {
        if(start <= *(this->showDates[i]) && *(this->showDates[i]) <= end)
            cnt++;
    }
    return cnt;
}

void ShowAnimal::print() const
{
    Animal::print();  // utilize the parent's print() function
    cout << ',' << this->showCnt << '\n';
}

void ShowAnimal::print(const Date& start, const Date& end) const
{
    Animal::print();  // utilize the parent's print() function
    cout << ',' << this->getShowCnt(start, end) << '\n';
}

// void ShowAnimal::debug() const
// {
//     Animal::print();
//     cout << "\nshowCnt: " << this->showCnt << "; curCapacity: " << this->curCapacity << '\n';
//     for(int i = 0; i < this->showCnt; i++)
//         cout << *(this->showDates[i]) << '\n';
// }

bool ShowAnimal::isShowAnimal() const
{
    return true;
}
// ==================================================










// class Zoo
// ==================================================
const int ZOO_CAP = 100;  // alternative: a static member variable
class Zoo
{
private:
    int displayAnimalCnt;
    int showAnimalCnt;
    Animal* animals[ZOO_CAP];  // using polymorphism
    // 我是 animal 的指標，但我指向的是 DA or SA
    // 拿 parent 的指標去指 child object = polymorphism
public:
    // default constructor: set the number of animals to zero
    Zoo();
    
    // destructor: delete dynamic objects/animals (those constructed by the syntax "new")
    ~Zoo();
    // 有 destructor 就要有 copy construtor & assignment operator
    // according to THE RULE OF THREE, since the destructor is required for this class,
    // the copy construtor and the assignment operator should also be implemented (regardless of whether other programmers really need them);
    // however, their implementations are omitted for simplicity in this problem
    
    // Zoo(const Zoo& z);
    // const Zoo& operator=(const Zoo& z);
    
    // return the number of display animals in the zoo
    int getDisplayAnimalCnt() const;
    
    // return the number of show animals in the zoo
    int getShowAnimalCnt() const;
    
    // return true and add an animal to the zoo if there the capacity is still enough;
    // otherwise, return false and no animal will be added
    bool addAnimal(const Animal* a, bool isShowAnimal);
    
    // set the name of the animal whose ID matches "id" to "n"
    void setName(int id, string n);
    
    // set the display time of the display animal whose name matches "name"
    void setDisplayTime(string name, const Time& start, const Time& end);
    
    // add a show date record for the show animal whose name matches "name" 
    void addShowDate(string name, const Date& d);
    
    // print the information of all animals in the zoo
    void print() const;
    
    // return a pointer to the show animal with the largest number of shows participated in;
    // if case of a tie, the animal with the smaller ID is selected
    const Animal* findMostBusyShowAnimal() const;
};

Zoo::Zoo() : displayAnimalCnt(0), showAnimalCnt(0)
{
    for(int i = 0; i < ZOO_CAP; i++)
        this->animals[i] = nullptr;
}

Zoo::~Zoo()
{
    for(int i = 0; i < this->displayAnimalCnt + this->showAnimalCnt; i++)
        delete this->animals[i];
}

int Zoo::getDisplayAnimalCnt() const
{
    return this->displayAnimalCnt;
}

int Zoo::getShowAnimalCnt() const
{
    return this->showAnimalCnt;
}

bool Zoo::addAnimal(const Animal* a, bool isShowAnimal)
{
    int totalCnt = this->displayAnimalCnt + this->showAnimalCnt;
    if(totalCnt >= ZOO_CAP)
        return false;
    else
    {
        if(isShowAnimal)
        {   
            // Zoo is a friend of Animal;
            // using public functions getID(), getBirthday(), and getName() also works     
            this->animals[totalCnt] = new ShowAnimal(a->id, a->birthday, a->name);  // polymorphism
            this->showAnimalCnt++;
        }
        else
        {
            this->animals[totalCnt] = new DisplayAnimal(a->id, a->birthday, a->name);  // polymorphism
            this->displayAnimalCnt++;
        }
        return true;
    }
}

void Zoo::setName(int id, string n)
{
    for(int i = 0; i < this->displayAnimalCnt + this->showAnimalCnt; i++)
    {
        if(id == this->animals[i]->getID())
        {
            this->animals[i]->setName(n);
            return;
        }
    }
}

void Zoo::setDisplayTime(string name, const Time& start, const Time& end)
{
    for(int i = 0; i < this->displayAnimalCnt + this->showAnimalCnt; i++)
    {
        if(name == this->animals[i]->getName() && !this->animals[i]->isShowAnimal())
        {
            // to access the function "setDisplayTime" defined in DisplayAnimal (NOT in Animal),
            // we have to cast Animal* to DisplayAnimal*

                // remark 1: dynamic_cast is typically used for handling polymorphism;
                //           it converts a pointer of the parent class to a pointer of the child class

                // remark 2: we may move the defition of "setDisplayTime" to Animal,
                //           and make it a pure virtual function that will be overridden by DisplayAnimal;
                //           dynamic_cast is not needed for this strategy
                // 這種做法較不建議，若有數十個 function 要 move 太耗工夫
            dynamic_cast<DisplayAnimal*>(this->animals[i])->setDisplayTime(start, end);
            return;
        }
    }
}

void Zoo::addShowDate(string name, const Date& d)
{
    for(int i = 0; i < this->displayAnimalCnt + this->showAnimalCnt; i++)
    {
        if(name == this->animals[i]->getName() && this->animals[i]->isShowAnimal())
        {
            // see the explaination above for dynamic_cast
            dynamic_cast<ShowAnimal*>(this->animals[i])->addShowDate(d);
            return;
        }
    }
}

void Zoo::print() const
{
    int totalCnt = this->displayAnimalCnt + this->showAnimalCnt;
    cout << totalCnt << '\n';
    for(int i = 0; i < totalCnt; i++)
        this->animals[i]->print();
    // with late binding and virtual functions,
    // now parent's print() function is virtual, allowing the child's implementation to be invoked
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
                int curID = this->animals[i]->getID();
                int optID = this->animals[opt]->getID();
                if(curShowCnt > optShowCnt || (curShowCnt == optShowCnt && curID < optID))
                    opt = i;
            }
        }
    }
    return this->animals[opt];    
}
// ==================================================










// main function
// ==================================================
int main()
{
    Zoo myZoo;
    
    int t = 0;
    cin >> t;
    cin.ignore();
    
    int id = 0;
    char task = 0;
    string type, name;
    
    for(int i = 0; i < t; i++)
    {
        cin >> task;
        if(task == 'C')
        {
            // the cin operator is overloaded for Date to enhance the readability of the code
            Date birthday;
            cin >> type >> id >> name >> birthday;
            
            // since no animal will be named "Unknown",
            // we can safely assign "Unknown" to unnamed animals without any error            
            if(type == "Show")
            {
                // since "addAnimal" perform a deep copy of the given show/display animal,
                // there is no concern about the local variable "sa/da" being destroyed after the if-block 
                ShowAnimal sa(id, birthday, name);
                myZoo.addAnimal(&sa, true);
            }
            else
            {
                DisplayAnimal da(id, birthday, name);
                myZoo.addAnimal(&da, false);
            }
        }
        else if(task == 'S')
        {
            Time start, end;
            cin >> name >> start >> end;  // cin is overloaded for Time
            myZoo.setDisplayTime(name, start, end);
        }
        else if(task == 'N')
        {
            cin >> id >> name;
            myZoo.setName(id, name);
        }
        else if(task == 'A')
        {
            Date showDate;
            cin >> name >> showDate;  // cin is overloaded for Date
            myZoo.addShowDate(name, showDate);
        }
    }
    
    myZoo.print();
    myZoo.findMostBusyShowAnimal()->print();
    
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

