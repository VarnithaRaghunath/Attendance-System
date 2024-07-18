#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

namespace AttendanceSystem {
    // Base class Person
    class Person {
    protected:
        string name;

    public:
        Person() : name("") {}
        Person(string n) : name(n) {}
        virtual ~Person() {}

        string getName() const { return name; }
        virtual void displayDetails() const = 0;
    };

    // Derived class Student from Person
    class Student : public Person {
    private:
        string rollNumber;
        int totalLectures;
        int attendedLectures;

    public:
        Student(string r, string n) : Person(n), rollNumber(r), totalLectures(0), attendedLectures(0) {}

        void displayDetails() const override {
            cout << "Name: " << name << ", Roll Number: " << rollNumber << endl;
        }

        friend class AttendanceManager;
    };

    // Derived class Subject
    class Subject {
    private:
        string subjectCode;
        string name;
        int totalLectures;

    public:
        Subject(string code, string n) : subjectCode(code), name(n), totalLectures(0) {}

        void displayDetails() const {
            cout << "Subject Code: " << subjectCode << ", Name: " << name << endl;
        }

        friend class AttendanceManager;
    };

    // Attendance Manager class
    class AttendanceManager {
    private:
        vector<Student> students;
        vector<Subject> subjects;

    public:
        AttendanceManager() {}

        void addStudent(string roll, string name) {
            students.push_back(Student(roll, name));
        }

        void addSubject(string code, string name) {
            subjects.push_back(Subject(code, name));
        }

        void takeAttendance() {
            for (auto& student : students) {
                char status;
                cout << "Is student " << student.getName() << " present? (Y/N): ";
                cin >> status;
                if (status == 'Y' || status == 'y') {
                    student.attendedLectures++;
                }
                student.totalLectures++;
            }
        }

        void displayAttendanceReport() const {
            cout << "Attendance Report:" << endl;
            cout << "Roll Number   Name          Total Lectures   Attended Lectures   Percentage" << endl;
            for (const auto& student : students) {
                double percentage = (static_cast<double>(student.attendedLectures) / student.totalLectures) * 100;
                cout << setw(12) << left << student.getName() << setw(14) << left << student.getName() << setw(17) << left << student.totalLectures << setw(20) << left << student.attendedLectures << setw(10) << left << fixed << setprecision(2) << percentage << "%" << endl;
            }
        }
    };
} // namespace AttendanceSystem

int main() {
    AttendanceSystem::AttendanceManager attendanceManager;

    int choice;
    do {
        cout << "1. Take Attendance" << endl;
        cout << "2. Display Attendance Report" << endl;
        cout << "3. Add Student" << endl;
        cout << "4. Add Subject" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                attendanceManager.takeAttendance();
                break;
            case 2:
                attendanceManager.displayAttendanceReport();
                break;
            case 3: {
                string roll, name;
                cout << "Enter roll number: ";
                cin >> roll;
                cout << "Enter student name: ";
                cin.ignore();
                getline(cin, name);
                attendanceManager.addStudent(roll, name);
                break;
            }
            case 4: {
                string code, subjectName;
                cout << "Enter subject code: ";
                cin >> code;
                cout << "Enter subject name: ";
                cin.ignore();
                getline(cin, subjectName);
                attendanceManager.addSubject(code, subjectName);
                break;
            }
            case 5:
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
                break;
        }

        cout << endl;
    } while (choice != 5);

    return 0;
}
