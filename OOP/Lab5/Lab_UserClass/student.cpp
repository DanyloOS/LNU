#include "student.h"

Student::Student()
{
    studentName = "";
    studentGroup = Fei11;
    courseYear = First;
    amountOfStudents++;
    studentID = amountOfStudents;
}

Student::Student(std::string studentName, Group studentGroup, Year courseYear)
{
    this->studentName = studentName;
    this->studentGroup = studentGroup;
    this->courseYear = courseYear;
}

void Student::setStudentName(std::string studentName)
{
    this->studentName = studentName;
}
std::string Student::getStudentName() const
{
    return studentName;
}
void Student::setStudentGroup(Group studentGroup)
{
    this->studentGroup = studentGroup;
}
Group Student::getStudentGroup() const
{
    return studentGroup;
}
void Student::setCourseYear(Year courseYear)
{
    this->courseYear = courseYear;
}
Year Student::getCourseYear() const
{
    return courseYear;
}

void Student::displayStatistics() const
{
    std::string groupName;

    switch(studentGroup){
    case Fei11: groupName = "Fei11"; break;
    case Fei12: groupName = "Fei12"; break;
    case Fei13: groupName = "Fei13"; break;
    case Fem11: groupName = "Fem11"; break;
    case Fes11: groupName = "Fes11"; break;
    case Fes12: groupName = "Fes12"; break;
    case Fei21: groupName = "Fei21"; break;
    case Fei22: groupName = "Fei22"; break;
    case Fei23: groupName = "Fei23"; break;
    case Fem22: groupName = "Fem22"; break;
    case Fes21: groupName = "Fes21"; break;
    }
    std::cout << "ID: " << studentID
              << "\nName: " << studentName
              << "\nGroup: " << groupName
              << "\nYear: " << courseYear << std::endl;
}
