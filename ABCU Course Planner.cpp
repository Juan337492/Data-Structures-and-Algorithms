//============================================================================
// Name        : ABCU.cpp
// Author      : Juan Rodriguez
// Version     :
// Copyright   : 
// Description : Course Planner
//============================================================================
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// Define a Course class
class Course {
public:
    string courseNumber;
    string name;
    vector<string> prerequisites;

    Course() = default;
    Course(string courseNumber, string name, vector<string> prerequisites)
        : courseNumber(courseNumber), name(name), prerequisites(prerequisites) {}
};

// Function to display the menu
void displayMenu() {
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
    cout << "What would you like to do? ";
}

// Function to load courses from file into a map (hash table)
void loadCoursesFromFile(const string& filename, map<string, Course>& courses) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open the file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 2) {
            cout << "Error: Invalid line format - " << line << endl;
            continue;
        }

        string courseNumber = tokens[0];
        string courseTitle = tokens[1];
        vector<string> prerequisites(tokens.begin() + 2, tokens.end());

        Course course(courseNumber, courseTitle, prerequisites);
        courses[courseNumber] = course;
    }

    file.close();
}

// Function to print all courses in alphanumeric order
void printCourseList(const map<string, Course>& courses) {
    vector<string> sortedCourseNumbers;
    for (const auto& pair : courses) {
        sortedCourseNumbers.push_back(pair.first);
    }
    sort(sortedCourseNumbers.begin(), sortedCourseNumbers.end());

    cout << "Here is a sample schedule:" << endl;
    for (const string& courseNumber : sortedCourseNumbers) {
        cout << courses.at(courseNumber).courseNumber << ", " << courses.at(courseNumber).name << endl;
    }
}

// Function to print course information
void printCourseInformation(const map<string, Course>& courses, const string& courseNumber) {
    auto it = courses.find(courseNumber);
    if (it == courses.end()) {
        cout << "Course not found: " << courseNumber << endl;
        return;
    }

    const Course& course = it->second;
    cout << course.courseNumber << ", " << course.name << endl;

    if (!course.prerequisites.empty()) {
        cout << "Prerequisites: ";
        for (const string& prereq : course.prerequisites) {
            auto prereqIt = courses.find(prereq);
            if (prereqIt != courses.end()) {
                cout << prereqIt->second.courseNumber << ", " << prereqIt->second.name << " ";
            }
        }
        cout << endl;
    }
}

// Main function to drive the program
int main() {
    map<string, Course> courses;
    int choice;

    cout << "Welcome to the ABCU Course Planner." << endl;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                string filename = "/Users/juanrodriguez/Documents/cs300DSA/ABCU Course Planner/src/CS 300 ABCU_Advising_Program_Input.csv";
                loadCoursesFromFile(filename, courses);
                break;
            }
            case 2:
                printCourseList(courses);
                break;
            case 3: {
                string courseNumber;
                cout << "What course do you want to know about? ";
                cin >> courseNumber;
                printCourseInformation(courses, courseNumber);
                break;
            }
            case 9:
                cout << "Thank you for using the ABCU Course Planner!" << endl;
                return 0;
            default:
                cout << choice << " is not a valid option." << endl;
                break;
        }
    }

    return 0;
}
