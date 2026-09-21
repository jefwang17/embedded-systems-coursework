#ifndef GRADE_REPORT_H
#define GRADE_REPORT_H

#include <string>
class Student;

class GradeReport {
private:
    std::string title; // e.g., "Midterm Results"
    std::string asOf;  // date or version

public:
    // Constructors
    GradeReport();                                  // "Grade Report", ""
    GradeReport(const std::string& title, const std::string& asOf);

    // Printing API (formatted table with <iomanip>) 
    void printHeader() const;
    void printRow(const Student& s) const;
    void printFooter(double avgMarks, double avgPercent) const;
};

#endif
