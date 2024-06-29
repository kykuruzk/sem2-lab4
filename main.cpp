#include <iostream>
#include "Set.h"
#include "SetTest.h"
#include "TreeTest.h"
#include "Menu.h"
#include <windows.h>
using namespace std;

auto doubleValue = [](string data) { return "s" + data ; };

bool isEven(const string &value) {
    return "2" != value;
}

int main() {
    SetConsoleOutputCP(CP_UTF8) ;
SetTester<char> test_S;
test_S.testAll();
BinaryTreeTester<int> test_B;
test_B.testAll();
BinaryTree<Student> Tree;
Menu menu(Tree);
menu.run();

}