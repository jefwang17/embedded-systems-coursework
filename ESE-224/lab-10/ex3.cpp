#include <iostream>
#include <iomanip>
using namespace std;

class Time {
private:
    int hours;
    int minutes;
    int seconds;

    void normalize() {
        // If any part is negative, clamp to 0:0:0
        if (hours < 0 || minutes < 0 || seconds < 0) {
            hours = minutes = seconds = 0;
            return;
        }

        // Carry seconds into minutes
        minutes += seconds / 60;
        seconds %= 60;

        // Carry minutes into hours
        hours += minutes / 60;
        minutes %= 60;
    }

    long totalSeconds() const {
        return static_cast<long>(hours) * 3600
             + static_cast<long>(minutes) * 60
             + static_cast<long>(seconds);
    }

public:
    // Constructors
    Time() : hours(0), minutes(0), seconds(0) {}
    Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {
        normalize();
    }

    // Addition
    Time operator+(const Time& other) const {
        Time result(hours + other.hours,
                    minutes + other.minutes,
                    seconds + other.seconds);
        result.normalize();
        return result;
    }

    // Subtraction (clamp to 0 if negative)
    Time operator-(const Time& other) const {
        long diff = totalSeconds() - other.totalSeconds();
        if (diff <= 0) return Time();  // 00:00:00

        int h = static_cast<int>(diff / 3600);
        diff %= 3600;
        int m = static_cast<int>(diff / 60);
        int s = static_cast<int>(diff % 60);
        return Time(h, m, s);
    }

    // Comparisons
    bool operator==(const Time& other) const {
        return totalSeconds() == other.totalSeconds();
    }
    bool operator<(const Time& other) const {
        return totalSeconds() < other.totalSeconds();
    }
    bool operator>(const Time& other) const {
        return totalSeconds() > other.totalSeconds();
    }

    // Output: HH:MM:SS
    friend ostream& operator<<(ostream& os, const Time& t) {
        os << setw(2) << setfill('0') << t.hours   << ":"
           << setw(2) << setfill('0') << t.minutes << ":"
           << setw(2) << setfill('0') << t.seconds;
        return os;
    }

    // Input: HH:MM:SS  (format B)
    friend istream& operator>>(istream& is, Time& t) {
        int h, m, s;
        char c1, c2;
        if (is >> h >> c1 >> m >> c2 >> s) {
            t.hours = h;
            t.minutes = m;
            t.seconds = s;
            t.normalize();
        }
        return is;
    }
};

int main() {
    Time t1, t2;

    cout << "Enter Time 1 (HH:MM:SS): ";
    cin >> t1;

    cout << "Enter Time 2 (HH:MM:SS): ";
    cin >> t2;

    cout << "\nChoose operation:\n";
    cout << "1. Add (Time 1 + Time 2)\n";
    cout << "2. Subtract (Time 1 - Time 2)\n";
    cout << "3. Compare (Time 1 vs Time 2)\n";
    cout << "Enter choice (1-3): ";

    int choice;
    cin >> choice;

    cout << "\nTime 1: " << t1 << "\n";
    cout << "Time 2: " << t2 << "\n";

    switch (choice) {
    case 1: {
        Time sum = t1 + t2;
        cout << "Sum of Time 1 and Time 2: " << sum << "\n";
        break;
    }
    case 2: {
        Time diff = t1 - t2;
        cout << "Difference between Time 1 and Time 2: " << diff << "\n";
        break;
    }
    case 3: {
        if (t1 == t2) {
            cout << "Time 1 is equal to Time 2.\n";
        } else if (t1 > t2) {
            cout << "Time 1 is later than Time 2.\n";
        } else {
            cout << "Time 1 is earlier than Time 2.\n";
        }
        break;
    }
    default:
        cout << "Invalid choice.\n";
        break;
    }

    return 0;
}
