#pragma once
#include <iostream>
#include "Tree.h"
#include "Errors.h"
using namespace std;
template<typename T>

class BinaryTreeTester {
public:
void testAll() {
    testInsert();
    testFindMin();
    testContains();
    testRemove();
    testOperators();
    testReadFromString();

    cout << "TREE WORK CORRECTLY\n";
}

private:
void testInsert() {
    BinaryTree<T> tree;
    tree.insert(5);
    tree.insert(10);
    tree.insert(3);
}

void testFindMin() {
    BinaryTree<T> tree;
    tree.insert(5);
    tree.insert(10);
    tree.insert(3);

    T min = tree.findMin();
    if (min != 3) throw logic_error("FIND MIN ERROR\n");
}

void testContains() {
    BinaryTree<T> tree;
    tree.insert(5);
    tree.insert(10);
    tree.insert(3);

    if (!(tree.contains(10) && tree.contains(5) && tree.contains(3)))
        throw length_error(CONTAINS_ERROR);
}

void testRemove() {
    BinaryTree<T> tree;
    tree.insert(5);
    tree.insert(10);
    tree.insert(3);

    tree.remove(10);

    if (tree.contains(10)) throw logic_error(INSERT_ERROR);
}

void testOperators() {
    BinaryTree<T> tree1;
    tree1.insert(5);
    tree1.insert(10);

    BinaryTree<T> tree2;
    tree2.insert(10);
    tree2.insert(15);

    BinaryTree<T> unionTree = tree1 + tree2;
}

void testReadFromString() {
    BinaryTree<T> tree;
    string input = "5 10 3 7 8";
    tree.readFromString(input);

    if (!(tree.contains(5) && tree.contains(10) &&
    tree.contains(3) && tree.contains(7) && tree.contains(8)))
    throw logic_error(STR_READ_ERROR);
}

};
