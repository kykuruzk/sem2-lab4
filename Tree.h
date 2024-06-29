#pragma once
#include <iostream>
#include "Errors.h"
#include <algorithm>
#include <iomanip>
using namespace std;



template<typename T>
class BinaryTree {
    class Node {
    public:
        T m_data;
        Node* left;
        Node* right;
        int height;

        explicit Node(const T& data) : m_data(data), left(nullptr), right(nullptr), height(1) {}
    };
    private:
    Node *root;

    public:
    BinaryTree() : root(nullptr) {};

    explicit BinaryTree(Node *new_root) : root(new_root) {}

    ~BinaryTree() {
        clear(root);
    }
    // НЕ глубокое копирование
    BinaryTree(const BinaryTree<T>& other) {
    //root = copyTree(other.root);
    root - other.root;
    }

    BinaryTree<T>& operator=(const BinaryTree<T> &other) {
        if (this == &other) return *this;
        clear(root);
        root = copyTree(other.root);
        return *this;
    }

    bool operator==(const BinaryTree &other) const {
        uint64_t thisSize = this->getSize();
        uint64_t otherSize = other.getSize();

        if (thisSize != otherSize) return false;

        T* thisElems = new T[thisSize];
        this->saveToArr(thisElems);

        T* otherElems = new T[otherSize];
        other.saveToArr(otherElems);

        for (int i = 0; i < thisSize; ++i)
            if (thisElems[i] != otherElems[i]) return false;
        delete[] thisElems;
        delete[] otherElems;

        return true;
    }

    BinaryTree<T> operator+(const BinaryTree<T>& other) {
        BinaryTree<T> result;
        result.root = copyTree(this->root);
        this->AddTreePrivate(result.root, other.root);
        return result;
    }

    BinaryTree<T> operator - (const BinaryTree<T>& other){
        BinaryTree<T> res;
        res = *this;

        uint64_t other_size = other.getSize();
        T* other_arr = new T[other_size];
        other.saveToArr(other_arr);

        for(uint64_t i = 0; i < other_size; i++){
            if( res.contains(other_arr[i]) ) res.remove(other_arr[i]);
        }

        delete [] other_arr;
        return res;
    }

    void print() const {
        printTree(root);
        cout << endl;
    }

    void readFromString(const string& input) {
        stringstream ss(input);
        T value;
        while (ss >> value) {
            insert(value);
        }
    }

    void readFromStream(const istream stream) {
        T value;
        while (stream >> value) {
            insert(value);
        }
    }

    void insert(const T& value) {
        root = insertPrivate(root, value);
    }

    T& findMin() const {
        if (root == nullptr) throw runtime_error(EMPTY_ERROR);
        return findMinPrivate(root)->m_data;
    }

    bool contains(const T& value) const {
        return containsPrivate(root, value);
    }

    void remove(const T& value) {
        root = removePrivate(root, value);
    }

    void saveToArr(T* arr) const {
        SaveToArrPrivate(root, arr, 0);
    }

    void printTree() const {
        printTreeView(root, 0);
    }

    [[nodiscard]] uint64_t getSize() const {
        return GetSizePrivate(root);
    }

    BinaryTree<T> extractSubtree(const T& value) {
        Node *newRoot = FindNodePrivate(root, value);
        if (newRoot == nullptr) throw runtime_error(NO_VALUE_ERROR);

        BinaryTree<T> sub;
        sub.root = newRoot;
        removeSubtreePrivate(root, newRoot);
        return sub;
    }

    BinaryTree<T> extractCopySubtree(const T& value) const {
        Node *newRoot = FindNodePrivate(value);
        if (newRoot == nullptr) throw runtime_error(NO_VALUE_ERROR);

        BinaryTree<T> sub;
        sub.root = copyTree(newRoot);
        return sub;
    }

    template <typename F>
    BinaryTree<T> map(F func) const {
        BinaryTree<T> result;
        MapRecursive(root, result, func);
        return result;
    }

    BinaryTree<T> where(bool (*pred)(const T&)) {
        BinaryTree<T> newTree;
        WherePrivate(root, newTree, pred);
        return newTree;
    }

    bool isSubtree(const BinaryTree<T>& other) {
        uint64_t other_size = other.getSize();
        if (other_size == 0) return true;

        T* other_arr = new T[other_size];
        other.saveToArr(other_arr);

        bool is_subtree = true;
        for (uint64_t i = 0; i < other_size; ++i) {
            if (!this->contains(other_arr[i])) {
                is_subtree = false;
                break;
            }
        }

        delete[] other_arr;
        return is_subtree;
    }

    private:
    int height(Node* node) const {
        return node ? node->height : 0;
    }

    int balanceFactor(Node* node) const {
        return height(node->left) - height(node->right);
    }

    void updHeight(Node* node) const {
        node->height = 1 + max(height(node->left), height(node->right));
    }

    Node* rotateRight(Node* node) const {
        Node* new_root = node->left;
        node->left = new_root->right;
        new_root->right = node;
        updHeight(node);
        updHeight(new_root);
        return new_root;
    }

    Node* rotateLeft(Node* node) const {
        Node* new_root = node->right;
        node->right = new_root->left;
        new_root->left = node;
        updHeight(node);
        updHeight(new_root);
        return new_root;
    }

    Node* balance(Node* node) const {
        if (balanceFactor(node) > 1) {
            if (balanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        } else if (balanceFactor(node) < -1) {
            if (balanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }
        return node;
    }

    void printTree(Node* node) const {
        if (node == nullptr) return;
        printTree(node->left);
        cout << node->m_data << " ";
        printTree(node->right);
    }

    Node* findMinPrivate(Node* node) const {
        if (node->left == nullptr) return node;
        return findMinPrivate(node->left);
    }

    bool containsPrivate(Node* node, const T& value) const {
        if (node == nullptr) return false;
        if (value == node->m_data) return true;
        else if (value < node->m_data) return containsPrivate(node->left, value);
        else if (value > node->m_data) return containsPrivate(node->right, value);
    }

    Node* removePrivate(Node* node, const T& value) {
        if (node == nullptr) return nullptr;

        if (value < node->m_data) node->left = removePrivate(node->left, value);
        else if (value > node->m_data) node->right = removePrivate(node->right, value);

        else {
            if ((node->left == nullptr) && (node->right == nullptr)) return nullptr;
            if (node->left == nullptr) return node->right;
            else if (node->right == nullptr) return node->left;

            Node *new_node = findMinPrivate(node->right);
            node->m_data = new_node->m_data;
            node->right = removePrivate(node->right, new_node->m_data);
        }

        return balance(node);
    }

    Node* insertPrivate(Node* node, const T& value) {
        if (node == nullptr) {
            return new Node(value);
        }

        if (value < node->m_data) {
            node->left = insertPrivate(node->left, value);
        } else if (value > node->m_data) {
            node->right = insertPrivate(node->right, value);
        }
        updHeight(node);
        return balance(node);
    }

    void clear(Node* node) const {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    //глубокое копирование
    Node* copyTree(Node* node) const {
        if (node == nullptr) {
            return nullptr;
        }
        Node* new_node = new Node(node->m_data);
        new_node->left = copyTree(node->left);
        new_node->right = copyTree(node->right);
        return new_node;
    }


    void removeSubtreePrivate(Node *cur, Node *target) {
        if (cur == nullptr) return;

        if (cur == target) cur = nullptr;// Удаляем поддерево
        else {
            removeSubtreePrivate(cur->left, target);
            removeSubtreePrivate(cur->right, target);
        }
    }

    uint64_t SaveToArrPrivate(Node *node, T *arr, uint64_t index) const {
        if (node == nullptr) return index;
        index = SaveToArrPrivate(node->left, arr, index);
        arr[index++] = node->m_data;
        index = SaveToArrPrivate(node->right, arr, index);
        return index;
    }

    uint64_t GetSizePrivate(Node *node) const {
        if (node == nullptr) return 0;
        //1 каждый раз суммируется после вызова
        return 1 + GetSizePrivate(node->left) + GetSizePrivate(node->right);
    }

    Node* FindNodePrivate(Node *node, const T &value) const {
        if (node == nullptr) return nullptr;
        if (value == node->m_data) return node;
        else if (value < node->m_data) return FindNodePrivate(node->left, value);
        else if (value > node->m_data) return FindNodePrivate(node->right, value);
    }

    void AddTreePrivate(Node*& target, Node* source) {
        if (source != nullptr) {
            target = insertPrivate(target, source->m_data);
            AddTreePrivate(target, source->left);
            AddTreePrivate(target, source->right);
        }
    }

    void WherePrivate(Node* currentNode, BinaryTree<T> &newTree, bool (*pred)(const T &)) {
        if (currentNode != nullptr) {
            WherePrivate(currentNode->left, newTree, pred);
            if (pred(currentNode->m_data)) {
                newTree.insert(currentNode->m_data);
            }
            WherePrivate(currentNode->right, newTree, pred);
        }
    }

    template <typename F>
    void MapRecursive(Node* node, BinaryTree<T>& result, F func) const {
        if (node != nullptr) {

            result.insert(func(node->m_data));
            MapRecursive(node->left, result, func);
            MapRecursive(node->right, result, func);
        }
    }

};
