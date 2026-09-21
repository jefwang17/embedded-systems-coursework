#include "Student.h"
#include "GradeReport.h"
#include <iostream>
using namespace std;
// g++ main.cpp Student.cpp GradeReport.cpp -o main

int main() {
    // Create two students
    Student s1("Alice Johnson", 101, 420);
    Student s2("Bob Singh", 102, 385);

    // Create GradeReport
    GradeReport report("ESE 224 - Midterm Results", "2025-09-06");

    // Print report
    report.printHeader();
    report.printRow(s1);
    report.printRow(s2);

    // Compute averages using static method
    double avgMarks, avgPercent;
    Student::computeAverages(s1, s2, avgMarks, avgPercent);

    // Print footer
    report.printFooter(avgMarks, avgPercent);

    return 0;
}
