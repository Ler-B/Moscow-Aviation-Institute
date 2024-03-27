#pragma once
#include <iostream>
#include "vector.hpp"

struct elem {
    int key;
    unsigned long long str;
    bool operator<(const elem &elem) {
        if (key < elem.key) {
            return true;
        }
        return false;
    }
    bool operator>(elem &elem) {
        return (elem < *this);
    }
    bool operator==(elem &elem) {
        return elem.key == key;
    }
};

struct List {
    NVector::TVector<elem> mas;
    NVector::TVector<List *> ref;
    List(){
        for (int i = 0; i < ref.Size(); ++i) {
            ref[i] = nullptr;
        }
    }
};


class BTree {
    public:
        friend void DeleteTree(List * list);
        BTree(){
            sizeroot = 2 * Length - 1;
            root = new List;
        }
        ~BTree() {
            DeleteTree(root);
        }
        void Insert(const int &key, const unsigned long long &str);
        bool Search(const int &key, bool print);
        void Del(const int &key);
        void Print();
    private:
        List * root;
        int sizeroot;
        bool Search(const int &key, List * list, bool print);
        void Insertrec(const int &key, const unsigned long long &str, List * list);
        void Del(const int &key, List * list);
        void Print(List * list, const int &p);
        void DeleteTree(List * list);
};


