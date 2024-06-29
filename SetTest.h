#pragma once
#include <iostream>
#include "Set.h"
using namespace std;
template <typename T>

class SetTester {
public:
void testAll() {
    testInsert();
    testContains();
    testRemove();
    testOperators();

    cout <<"SET WORK CORRECTLY\n";
}
private:
void testInsert() {
    Set<T> set;
    set.insert(5);
    set.insert(10);
    set.insert(15);
}

void testContains() {
    Set<T> set;
    set.insert(5);
    set.insert(10);
    set.insert(15);

    if (set.contains(10) && set.contains(5) && set.contains(15)) return;
    else throw logic_error(CONTAINS_ERROR);
    }

void testRemove() {
    Set<T> set;
    set.insert(5);
    set.insert(10);
    set.insert(15);
    set.remove(10);
    set.remove(-100000);
    if (!set.contains(10)) return;
    else throw logic_error(REMOVE_ERROR);
    }

void testOperators() {
    Set<T> set1;
    set1.insert(5);
    set1.insert(10);

    Set<T> U_correct;
    U_correct.insert(5);
    U_correct.insert(10);
    U_correct.insert(15);

    Set<T> set2;
    set2.insert(10);
    set2.insert(15);

    Set<T> d_correct;
    d_correct.insert(15);
    Set<T> unionSet = set1 + set2;
    Set<T> diffSet = set1 - set2;
    if ( unionSet == U_correct && d_correct == d_correct ) return;
    else throw logic_error(OPERATORS_ERROR);
}
};
