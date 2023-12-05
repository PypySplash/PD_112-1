#include <iostream>
using namespace std;

class Course
{
protected:
    string title;
    string dept;
    int unit;
    int instCount;
    string* instructor;
    int day;
    int startTime;
public:
    // Course(const string& title, const string& dept, int unit) noexcept;  // TA version
    Course(string title, string dept, int unit);  // normal version
    Course(const Course& c);  // header of copy constructor
    ~Course();
    bool setTime(int day, int startTime);
    virtual void print();
    void enterInstructor();

};
Course::Course(string title, string dept, int unit) {
    this->title = title;
    this->dept = dept;
    this->unit = unit;
    this->instCount = 0;
    this->instructor = nullptr;
    this->day = 0;  // or other values you like
    this->startTime = 0;
}
Course::Course(const Course& c) {  // copy constructor
    this->title = c.title;
    this->dept = c.dept;
    this->unit = c.unit;
    this->instCount = c.instCount;
    if (c.instructor != nullptr) {
        this->instructor = new string[instCount];
        for (int i = 0; i < instCount; i++) {
            instructor[i] = c.instructor[i];
        }
    }
    else {
        this->instructor = nullptr;
    }
    this->day = c.day;  // or other values you like
    this->startTime = c.startTime;
}
Course::~Course()
{
    delete [] this->instructor;
    this->instructor = nullptr;
}

bool Course::setTime(int day, int startTime) {
    if (day < 1 || day > 5 || startTime < 1 || startTime > 9 || (day + startTime > 10)) {
        return false;
        // throw logic_error("default error");
    }
    this->day = day;
    this->startTime = startTime;
    return true;
}
void Course::print() {
    cout << title << ", " << dept << ", " << unit << " unit(s)" << endl;
    cout << instCount << " instructor(s):";
    for (int i = 0; i < instCount; i++) {
        cout << instructor[i] << " ";
    }
    cout << endl;
    if (this->day == 1) cout << "Monday: ";
    if (this->day == 2) cout << "Tuesday: ";
    if (this->day == 3) cout << "Wednesday: ";
    if (this->day == 4) cout << "Thursday: ";
    if (this->day == 5) cout << "Friday: ";
    cout << this->startTime << "-" << this->startTime + this->unit - 1 << endl;
}
void Course::enterInstructor() {
    delete [] instructor;
    this->instructor = nullptr;

    cin >> instCount;

    instructor = new string[instCount];
    for (int i = 0; i < instCount; i++) {
        cin >> instructor[i];
    }
}


class LECourse : public Course
{
private:
    int category;
public:
    LECourse(string title, string dept, int unit, int category);
    void print() override;
};

LECourse::LECourse(string title, string dept, int unit, int category) 
  : Course(title, dept, unit), category(category)
{
}
void LECourse::print() {
    Course::print();
    cout << category << endl;
}

int main()
{
    Course c("TA_lab", "IM", 3);
    c.setTime(2, 6);
    c.enterInstructor();
    c.print();

    LECourse d("TA_lab", "IM", 3, 7);
    d.setTime(3, 2);
    d.print();
    c.setTime(2, 10);
    c.print();

    return 0;
}
