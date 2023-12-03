#include <iostream>
#include <string>
#include <stdexcept>
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
protected:
    int id;
    Date birthday;
    string name;
public:
    // constructor: specify the ID, birthday, and name of the animal
    Animal(int id, const Date& b, const string& n) noexcept;
    
    // virtual destructor: ensure the child's destructor will be invoked
    virtual ~Animal() noexcept;
    
    // return the ID of the animal
    int getID() const noexcept;
    
    // return the age of the animal
    int getAge() const noexcept;
    
    // return the name of the animal
    string getName() const noexcept;
    
    // set the name of the animal to "n"
    void setName(const string& n) noexcept;
    
    // print the name, birthday, and age of the animal
    // this function is overridden by the child class of Animal
    virtual void print() const noexcept;
    
    // retrun true if the calling object is of type ShowAnimal, false otherwise
    // this function is only overridden by ShowAnimal
    virtual bool isShowAnimal() const noexcept;
};

Animal::Animal(int id, const Date& b, const string& n) noexcept : id(id), birthday(b), name(n) 
{  // direct assignment of types int, Datem and string is fine
}

Animal::~Animal()
{
}

int Animal::getID() const noexcept
{
    return this->id;   
}

int Animal::getAge() const noexcept
{
    return this->birthday.yearUntil(TODAY);   
}

string Animal::getName() const noexcept
{
    return this->name;
}

void Animal::setName(const string& n) noexcept
{
    this->name = n;
}

void Animal::print() const noexcept
{
    cout << this->name << ',' << this->birthday << ',' << this->getAge();
}

bool Animal::isShowAnimal() const noexcept
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
    DisplayAnimal(int id, const Date& b, const string& n) noexcept;
    
    // set the display time of the display animal
    // if the start time or end time is not valid, nothing will be set 
    void setDisplayTime(const Time& start, const Time& end) noexcept(false);
    
    // return the display time of the display animal using the call-by-reference mechanism
    void getDisplayTime(Time& start, Time& end) const noexcept(false);
    
    // print the name, birthday, age, and display time of the display animal
    // the keyword "override" is a reminder that this function is overridden
    void print() const noexcept override;
};

DisplayAnimal::DisplayAnimal(int id, const Date& b, const string& n) noexcept : Animal(id, b, n), hasDisplayTime(false)
{  // the parent's constructor Animal(id, b, n) is invoked
}

void DisplayAnimal::setDisplayTime(const Time& start, const Time& end) noexcept(false)
{
    // ===== exception handling =====
    // enforce the caller to catch the exception (and do something) when the given display time is invalid 
    if(!(start.isValidTime() && end.isValidTime() && start <= end)) 
        throw logic_error("invalid display time");
    this->start = start;
    this->end = end;
    this->hasDisplayTime = true;
}

void DisplayAnimal::getDisplayTime(Time& start, Time& end) const noexcept(false)
{
    // ===== exception handling =====
    // enforce the caller to catch the exception (and do something) when the animal has no display time
    if(!this->hasDisplayTime)
        throw logic_error("display time does not exist");
    start = this->start;
    end = this->end;
}

void DisplayAnimal::print() const noexcept
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
    void doubleCapacity() noexcept;
public:
    // constructor: specify the ID, birthday, and name of the show animal
    ShowAnimal(int id, const Date& b, const string& n) noexcept;
    
    // copy constructor: perform a deep copy as there is a member variable of type pointer
    ShowAnimal(const ShowAnimal& sa) noexcept;
    
    // destructor: to delete to dynamically allocated memory
    ~ShowAnimal() noexcept;
    
    // assignment operator: perform a deep copy as there is a member variable of type pointer
        // remark: THE RULE OF THREE - 
        //         if we need to define any of the copy constructor, assignment operator, and destructor,
        //         we have to define all of them (regardless of whether other programmers actually need to use them)
    const ShowAnimal& operator=(const ShowAnimal& sa) noexcept;
    
    // add a show date record for the show animal
    // if the show animal is not born before the given date or the date already exists, nothing will be added 
    void addShowDate(const Date& d) noexcept(false);
    
    // return the number of shows that the show animal participated in
    int getShowCnt() const noexcept;
    
    // return the number of shows that the show animal participated in within the given period
    int getShowCnt(const Date& start, const Date& end) const noexcept;
    
    // print the name, birthday, age, and the number of shows in which the show animal has participated 
    // the keyword "override" is a reminder that this function is overridden
    void print() const noexcept override;
    
    // print the name, birthday, age, and the number of shows in which the show animal has participated within the given period
    // this function is NOT overriden one as the function signature is different from that of the parent's
    void print(const Date& start, const Date& end) const noexcept;
    
    // print all the details of the show animal 
    void debug() const noexcept;
    
    // always return true
    // the keyword "override" is a reminder that this function is overridden
    bool isShowAnimal() const noexcept override;
};

ShowAnimal::ShowAnimal(int id, const Date& b, const string& n) noexcept : Animal(id, b, n)
{  // the parent's constructor Animal(id, b, n) is invoked
    this->showCnt = 0;
    this->curCapacity = ShowAnimal::initCapacity;
    this->showDates = new Date*[curCapacity];
}

ShowAnimal::ShowAnimal(const ShowAnimal& sa) noexcept : Animal(sa.id, sa.birthday, sa.name)
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

const ShowAnimal& ShowAnimal::operator=(const ShowAnimal& sa) noexcept
{
    if(this != &sa)
    {
        for(int i = 0; i < this->showCnt; i++)
            delete this->showDates[i];
        delete [] this->showDates;
        
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

void ShowAnimal::doubleCapacity() noexcept
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

void ShowAnimal::addShowDate(const Date& d) noexcept(false)
{
    // ===== exception handling =====
    // enforce the caller to catch the exception (and do something) when the given show date is invalid 
    if(!(this->birthday <= d))
        throw logic_error("invalid show date");
    
    for(int i = 0; i < this->showCnt; i++)
    {
        if(*(this->showDates[i]) == d)
            throw logic_error("show date already exists");
    }
    
    if(this->showCnt >= this->curCapacity)  // here to determine whether to expand the length of "showDates"
        this->doubleCapacity();
    this->showDates[this->showCnt] = new Date(d);
    this->showCnt++;
}

int ShowAnimal::getShowCnt() const noexcept
{
    return this->showCnt;
}

int ShowAnimal::getShowCnt(const Date& start, const Date& end) const noexcept
{
    int cnt = 0;
    for(int i = 0; i < this->showCnt; i++)
    {
        if(start <= *(this->showDates[i]) && *(this->showDates[i]) <= end)
            cnt++;
    }
    return cnt;
}

void ShowAnimal::print() const noexcept
{
    Animal::print();  // utilize the parent's print() function
    cout << ',' << this->showCnt << '\n';
}

void ShowAnimal::print(const Date& start, const Date& end) const noexcept
{
    Animal::print();  // utilize the parent's print() function
    cout << ',' << this->getShowCnt(start, end) << '\n';
}

void ShowAnimal::debug() const noexcept
{
    Animal::print();
    cout << "\nshowCnt: " << this->showCnt << "; curCapacity: " << this->curCapacity << '\n';
    for(int i = 0; i < this->showCnt; i++)
        cout << *(this->showDates[i]) << '\n';
}

bool ShowAnimal::isShowAnimal() const noexcept
{
    return true;
}
// ==================================================










// global function headers and global variables
// ==================================================
void printFourDigit(int n);
void printTwoDigit(int n);

// without template
/* 
int findDisplayTargetByID(DisplayAnimal* animals[], int cnt, int id);
int findDisplayTargetByName(DisplayAnimal* animals[], int cnt, const string& name);
int findShowTargetByID(ShowAnimal* animals[], int cnt, int id);
int findShowTargetByName(ShowAnimal* animals[], int cnt, const string& name);
*/

// template helps avoid defining two very similiar function, which may lead to potential inconsistency  
// (the introduction of template can be found in Lecture 15)

// return the index of the first animal in "animals" whose ID matches "id" 
template <typename AnimalType>
int findTargetByID(AnimalType* animals[], int cnt, int id) noexcept(false);

// return the index of the first animal in "animals" whose name matches "name"
template <typename AnimalType>
int findTargetByName(AnimalType* animals[], int cnt, const string& name) noexcept(false);

const int MAX_ANIMAL_CNT = 100;
// const int NOT_FOUND_CODE = -1;  // no need for this global variable when using exception handling



// main function
// ==================================================
int main()
{
    int t = 0;
    cin >> t;
    cin.ignore();
    
    int displayAnimalCnt = 0, showAnimalCnt = 0;
    DisplayAnimal* displayAnimals[MAX_ANIMAL_CNT]; 
    ShowAnimal* showAnimals[MAX_ANIMAL_CNT]; 
    
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
                showAnimals[showAnimalCnt] = new ShowAnimal(id, birthday, name);
                showAnimalCnt++;
            }
            else
            {
                displayAnimals[displayAnimalCnt] = new DisplayAnimal(id, birthday, name);
                displayAnimalCnt++;
            }
        }
        else if(task == 'S')
        {
            Time start, end;
            cin >> name >> start >> end;  // cin is overloaded for Time
            try
            {
                int aID = findTargetByName<DisplayAnimal>(displayAnimals, displayAnimalCnt, name);
                try
                {
                    displayAnimals[aID]->setDisplayTime(start, end);
                }
                catch(logic_error e)
                {
                    // cout << e.what();  // do something to handle the exception, e.g., print the error message
                                          // remove the comment to see what message will be printed
                }
            }
            catch(out_of_range e)
            {  // do something to handle the exception
            }
        }
        else if(task == 'N')
        {
            cin >> id >> name;
            try
            {
                int aID = findTargetByID<DisplayAnimal>(displayAnimals, displayAnimalCnt, id);
                displayAnimals[aID]->setName(name);
            }
            catch(out_of_range e)
            {
                try
                {
                   int aID = findTargetByID<ShowAnimal>(showAnimals, showAnimalCnt, id);
                   showAnimals[aID]->setName(name);
                }
                catch(out_of_range e)
                {  // do something to handle the exception
                }
            }
        }
        else if(task == 'A')
        {
            Date showDate;
            cin >> name >> showDate;  // cin is overloaded for Date
            try
            {
                int aID = findTargetByName<ShowAnimal>(showAnimals, showAnimalCnt, name);
                try
                {
                    showAnimals[aID]->addShowDate(showDate);
                }
                catch(logic_error e)
                {  // do something to handle the exception
                } 
            }
            catch(out_of_range e)
            {  // do something to handle the exception
            }
        }
    }
    
    Date start, end;
    cin >> task >> name >> start >> end;  // cin is overloaded for Date
    
    cout << displayAnimalCnt << ',' << showAnimalCnt << '\n';
    
    try
    {
        int toPrintID = findTargetByName<ShowAnimal>(showAnimals, showAnimalCnt, name);
        showAnimals[toPrintID]->print(start, end);        
    }
    catch(out_of_range e)
    {  // do something to handle the exception
    }
    
    for(int i = 0; i < displayAnimalCnt; i++)
        delete displayAnimals[i];  // not delete [] displayAnimals[i]
    for(int i = 0; i < showAnimalCnt; i++)
        delete showAnimals[i];  // not delete [] showAnimals[i]
    
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

template <typename AnimalType>
int findTargetByID(AnimalType* animals[], int cnt, int id) noexcept(false)
{
    for(int i = 0; i < cnt; i++)
    {
        if(id == animals[i]->getID())
            return i;
    }
    throw out_of_range("ID not found");
}

template <typename AnimalType>
int findTargetByName(AnimalType* animals[], int cnt, const string& name) noexcept(false)
{
    for(int i = 0; i < cnt; i++)
    {
        if(name == animals[i]->getName())
            return i;
    }
    throw out_of_range("name not found");
}

