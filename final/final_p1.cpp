#include <iostream>
#include <string>
using namespace std;

struct Course
{
    string courseID; // any string like "IM 1003"
    string courseName; // any string like " Programming Design "
    // int grade; // should be within 0 and 100
    int credit; // should be 1, 2, 3, or 4
};

struct StudentCourse
{
    Course course; // 課程資訊
    int grade;     // 成績，應在 0 到 100 之間
};


class Student
{
protected:
    string studentID;
    string studentName;
    string major;
    int year;
    int courseCnt;
    StudentCourse courseGrades[200];
public :
    Student (string studentID, string studentName, string major, int year)
    : studentID(studentID), studentName(studentName), major(major), year(year), courseCnt(0) 
    {
    }
    void setYear(int year) {this->year = year;}
    void takeCourse(const StudentCourse& sc);
    double getAvgGrade() const;
};

void Student::takeCourse(const StudentCourse& sc)
{
    if (courseCnt >= 200) { // 檢查是否超出陣列容量
        throw std::runtime_error("課程數量超出最大限制");
    }
    courseGrades[courseCnt] = sc;
    courseCnt++;
}
double Student::getAvgGrade() const
{
    if (courseCnt == 0) {
        throw std::runtime_error("沒有課程資料，無法計算平均成績");
    }

    int totalGradeTimesCredits = 0;
    int totalCredits = 0;
    for (int i = 0; i < courseCnt; i++) {
        totalGradeTimesCredits += courseGrades[i].grade * courseGrades[i].course.credit;
        totalCredits += courseGrades[i].course.credit;
    }

    if (totalCredits == 0) {
        throw std::runtime_error("沒有課程資料，無法計算平均成績");
    }

    return static_cast<double>(totalGradeTimesCredits) / totalCredits;
    // to be implemented
}



class BachelorStudent : public Student {
private:
    string secondMajor; // 用於存儲第二個主修的名稱
public:
    // 建構子，初始化基本資訊，第二主修預設為空
    BachelorStudent(const string& studentID, const string& studentName, 
                    const string& major, int year)
    : Student(studentID, studentName, major, year), secondMajor("") {}

    // 設置第二主修的函數
    void setSecondMajor(const string& newSecondMajor) {
        secondMajor = newSecondMajor;
    }

    // 獲取第二主修的函數
    string getSecondMajor() const {
        return secondMajor;
    }

    // 其他成員函數...
};



class MasterStudent : public Student {
private:
    string advisor; // 用於存儲指導教授的姓名

public:
    // 建構子，初始化基本資訊，指導教授姓名預設為空
    MasterStudent(const string& studentID, const string& studentName, 
                  const string& major, int year, const string& advisor = "")
    : Student(studentID, studentName, major, year), advisor(advisor) {}

    // 設置指導教授的函數
    void setAdvisor(const string& newAdvisor) {
        advisor = newAdvisor;
    }

    // 獲取指導教授的函數
    string getAdvisor() const {
        return advisor;
    }

    // 其他成員函數...
};


int main()
{

}