#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>

enum Group {Fei11, Fei12, Fei13, Fem11, Fes11, Fes12, Fei21, Fei22, Fei23, Fem22, Fes21};
enum Year {First, Second};
class Student
{
public:
    Student();
    Student(std::string studentName, Group studentGroup, Year courseYear);

    void setStudentName(std::string studentName);
    std::string getStudentName () const;
    void setStudentGroup(Group studentGroup);
    Group getStudentGroup() const;
    void setCourseYear(Year courseYear);
    Year getCourseYear() const;

    void displayStatistics() const;

private:
    std::string studentName;
    Group studentGroup;
    Year courseYear;
};

#endif // STUDENT_H
