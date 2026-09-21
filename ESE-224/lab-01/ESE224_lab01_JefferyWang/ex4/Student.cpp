#include "Student.h"

// Constructors
Student::Student() : name(""), rollNo(0), totalMarks(0) {}

Student::Student(const string& nm, int rn, int tm)
    : name(nm), rollNo(rn), totalMarks(tm) {}

// Accessors
string Student::getName() const { return name; }
int    Student::getRollNo() const { return rollNo; }
int    Student::getTotalMarks() const { return totalMarks; }

// Percentage (out of 500 total) -> [0,100]
double Student::percentage() const {
    return (totalMarks / 500.0) * 100.0;
}

// Static average calculator
void Student::computeAverages(const Student& s1, const Student& s2,
                              double& avgMarks, double& avgPercent) {
    avgMarks   = (s1.getTotalMarks() + s2.getTotalMarks()) / 2.0;
    avgPercent = (s1.percentage()   + s2.percentage())     / 2.0;
}
