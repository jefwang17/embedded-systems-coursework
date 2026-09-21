#ifndef STUDENT_H
#define STUDENT_H

#include <string>
using std::string;

class Student {
private:
    string name;      // Student’s name
    int    rollNo;    // Roll number
    int    totalMarks; // Out of 500

public:
    // Constructors
    Student();                                   // name="", rollNo=0, totalMarks=0
    Student(const string& name, int rollNo, int totalMarks);

    // Accessors
    string getName() const;
    int    getRollNo() const;
    int    getTotalMarks() const;

    // Percentage out of 100
    double percentage() const;   // (totalMarks / 500.0) * 100.0  

    // Static: compute averages for two students
    static void computeAverages(const Student& s1, const Student& s2,
                                double& avgMarks, double& avgPercent); // 
};

#endif
