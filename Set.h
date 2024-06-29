#pragma once
#include "Tree.h"
#include <iostream>
#include <string>
using namespace std;

template <typename T>
class Set {
private:
BinaryTree<T> tree;
public:
Set(): tree() {};

~Set() = default;

Set(const Set<T>& other) : tree(other.tree) {}

bool operator==(const Set& other) const {
    if ( this->tree == other.tree) return true;
    else return false;
}

Set<T> operator + (const Set<T>& other) {
    Set<T> res;
    res.tree = this->tree + other.tree;
    return res;
}

Set<T> operator - (const Set<T>& other){
    Set<T> res;
    res.tree = this->tree - other.tree;
    return res;
}

void insert(const T& value) {
    if(!tree.contains(value)) tree.insert(value);
}

void print(){
    tree.print();
}

void remove(const T& value){
    tree.remove(value);
}

bool contains(const T& value){
    return tree.contains(value);
}

Set<T> where(bool (*pred) (const T&)){
    Set<T> res;
    res.tree = this->tree.where(pred);
    return res;
}

template <typename F>
Set<T> map(F func) const {
    Set<T> result;
    result = this->tree.map(func);
    return result;
}

void readFromStr(const string & str){
    stringstream ss(str);
    T value;
    while (ss >> value) {

        insert(value);}
}

bool isIncluded(const Set<T>& other){
    return (tree.isSubtree(other));
}

};

