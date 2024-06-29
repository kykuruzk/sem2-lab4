#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
using namespace std;

class Student {
public:
    string name;
    string surname;
    int grade;
    string profile;

    Student() : name(""), surname(""), grade(0), profile("") {}

    Student(const string& name, const string& surname, int grade, const string& profile)
            : name(name), surname(surname), grade(grade), profile(profile) {}

    friend ostream& operator<<(ostream& os, const Student& student) {
        os << "Name: " << student.name << ", Surname: " << student.surname
           << ", Grade: " << student.grade << ", Profile: " << student.profile << endl;
        return os;
    }

    bool operator==(const Student& other) const {
        return name == other.name && surname == other.surname && grade == other.grade && profile == other.profile;
    }

    bool operator!=(const Student& other) const {
        return !(*this == other);
    }


    bool operator<(const Student& other) const {

        if (surname < other.surname) return true;
        if (surname > other.surname) return false;


        if (name < other.name) return true;
        if (name > other.name) return false;


        if (profile < other.profile) return true;
        if (profile > other.profile) return false;

        return grade < other.grade;
    }

    bool operator>(const Student& other) const {
        return !(*this < other) && !(*this == other);
    }
};
