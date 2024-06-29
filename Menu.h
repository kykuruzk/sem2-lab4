#pragma once
#include <iostream>
#include <limits>
#include <sstream>
#include "Set.h"
#include "student.h"
using namespace std;

class Menu {
private:
BinaryTree<Student>& tree;
Student student;
Student student2;
public:
explicit Menu(BinaryTree<Student>& tree) : tree(tree) {}

void run() {
    int choice;
    do {
        printMenu();
        choice = safeInputInteger("Выберите действие: ");

        processChoice(choice);
    } while (choice != 0);
}

private:
void printMenu() const {
    cout << "\n         МЕНЮ      \n";
    cout << "1. Добавить студента\n";
    cout << "2. Удалить студента\n";
    cout << "3. Проверить наличие студента\n";
    cout << "4. Вывести список студентов\n";
    cout << "5. Ввести нескольких студентов\n";
    cout << "6. Объединить с другим деревом\n";
    cout << "7. Удалить студентов из другого дерева\n";
    cout << "8. Сравнить с другим деревом\n";
    cout << "9. Проверить, является ли поддеревом\n";
    cout << "0. Выход\n";
}

void processChoice(int choice) {
    switch (choice) {
        case 1: addStudent(); break;
        case 2: deleteStudent(); break;
        case 3: checkStudent(); break;
        case 4: printStudents(); break;
        case 5: inputStudents(); break;
        case 6: mergeWithAnotherTree(); break;
        case 7: deleteStudentsFromAnotherTree(); break;
        case 8: compareWithAnotherTree(); break;
        case 9: checkIfSubtree(); break;
        case 0: cout << "Выход...\n"; break;
        default: cout << "Неверный выбор!\n";
    }
}

void addStudent() {

    cout << "Введите имя: ";
    cin >> student.name;
    cout << "Введите фамилию: ";
    cin >> student.surname;
    student.grade = safeInputInteger("Введите класс: ");
    cout << "Введите профиль: ";
    cin >> student.profile;
    tree.insert(student);
    cout << "Студент добавлен!\n";
}

void deleteStudent() {
    cout << "Введите имя: ";
    cin >> student.name;
    cout << "Введите фамилию: ";
    cin >> student.surname;
    tree.remove(student);
    cout << "Студент удален!\n";
}

void checkStudent() {
    cout << "Введите имя: ";
    cin >> student.name;
    cout << "Введите фамилию: ";
    cin >> student.surname;
    if (tree.contains(student)) {
        cout << "Студент найден!\n";
    } else cout << "Студент не найден!\n";

}

void printStudents() {
    cout << "Список студентов:\n";
    tree.print();
}

void inputStudents() {
    int numStudents;
    cout << "Введите количество студентов: ";
    cin >> numStudents;

    for (int i = 0; i < numStudents; ++i) {

        cout << "Введите имя: ";
        cin >> student.name;
        cout << "Введите фамилию: ";
        cin >> student.surname;
        student.grade = safeInputInteger("Введите класс: ");
        cout << "Введите профиль: ";
        cin >> student.profile;
        tree.insert(student);
    }
    cout << "Студенты добавлены!\n";
}

void mergeWithAnotherTree() {
    BinaryTree<Student> otherTree;
    cout << "Введите имя: ";
    cin >> student2.name;
    cout << "Введите фамилию: ";
    cin >> student2.surname;
    student2.grade = safeInputInteger("Введите класс: ");
    cout << "Введите профиль: ";
    cin >> student2.profile;
    otherTree.insert(student2);
    cout << "Студент добавлен!\n";

    tree = tree + otherTree;
    cout << "Деревья объединены!\n";
}

void deleteStudentsFromAnotherTree() {
    BinaryTree<Student> otherTree;
    cout << "Введите имя: ";
    cin >> student2.name;
    cout << "Введите фамилию: ";
    cin >> student2.surname;
    student2.grade = safeInputInteger("Введите класс: ");
    cout << "Введите профиль: ";
    cin >> student2.profile;
    tree.remove(student2);

    tree = tree - otherTree;
    cout << "Студент удален!\n";
}

void compareWithAnotherTree() {
    BinaryTree<Student> otherTree;
    cout << "Введите имя: ";
    cin >> student2.name;
    cout << "Введите фамилию: ";
    cin >> student2.surname;
    student2.grade = safeInputInteger("Введите класс: ");
    cout << "Введите профиль: ";
    cin >> student2.profile;
    otherTree.insert(student2);
    cout << "Студент добавлен!\n";

    if (tree == otherTree) {
        cout << "Деревья одинаковы\n";
    } else {
        cout << "Деревья различны.\n";
    }
}

void checkIfSubtree() {
    BinaryTree<Student> otherTree;
    cout << "Введите имя: ";
    cin >> student2.name;
    cout << "Введите фамилию: ";
    cin >> student2.surname;
    student2.grade = safeInputInteger("Введите класс: ");
    cout << "Введите профиль: ";
    cin >> student2.profile;
    otherTree.insert(student2);

    if (tree.isSubtree(otherTree)) {
        cout << "Другое дерево является поддеревом.\n";
    } else {
        cout << "Другое дерево не является поддеревом.\n";
    }
}


int safeInputInteger(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода! Введите целое число.\n";
        } else {
            return value;
        }
    }
}
};

