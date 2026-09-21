#include "GradeReport.h"
#include "Student.h"
#include <iostream>
#include <iomanip>
using namespace std;

GradeReport::GradeReport() : title("Grade Report"), asOf("") {}
GradeReport::GradeReport(const string& t, const string& d) : title(t), asOf(d) {}

void GradeReport::printHeader() const {
    cout << fixed << setprecision(2);
    cout << "\n" << title;
    if (!asOf.empty()) cout << "  (" << asOf << ")";
    cout << "\n";

    // Column headers
    cout << left  << setw(20) << "Name"
         << right << setw(8)  << "Roll"
         << right << setw(12) << "Marks/500"
         << right << setw(12) << "Percent"
         << "\n";

    cout << string(20 + 8 + 12 + 12, '-') << "\n";
}

void GradeReport::printRow(const Student& s) const {
    cout << left  << setw(20) << s.getName()
         << right << setw(8)  << s.getRollNo()
         << right << setw(12) << s.getTotalMarks()
         << right << setw(11) << s.percentage() << "%"   // show % sign
         << "\n";
}

void GradeReport::printFooter(double avgMarks, double avgPercent) const {
    cout << string(20 + 8 + 12 + 12, '-') << "\n";
    cout << left  << setw(20) << "Averages"
         << right << setw(8)  << ""
         << right << setw(12) << avgMarks
         << right << setw(11) << avgPercent << "%\n\n";
}
