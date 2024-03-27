#include <iostream>
#include "BTree.hpp"

//ПОИСК ключа в массиве
bool FindKey(NVector::TVector<elem> mas, int &key){
    for (int i = 0; i < mas.Size(); ++i) {
        if (mas[i].key == key){
            return true;
        }
    }
    return false;
}

//ПОИСК РЕКУРСИВНО
bool BTree::Search(const int &key, List * list, bool print) {
    for (int i = 0; i < list->mas.Size(); ++i) {
        if (list->mas[i].key == key) {
            if (print) {
                std::cout << "KEY:" << list->mas[i].key << std::endl;
                return true;
            }
            return true;
        }
        if (key < list->mas[i].key) {
            if (list->ref[i] != nullptr) {
                return Search(key, list->ref[i], print);
            }
            break;
        }
    }
    if (list->ref[0] != nullptr) {
        return Search(key, list->ref[list->mas.Size()], print);
    }
    
    if (print) {
        std::cout << "NO KEY" << std::endl;
    }
    return false;
}

//ПОИСК
bool BTree::Search(const int &key, bool print) {
    return Search(key, root, print);
}

//УДАЛЕНИ
void BTree::DeleteTree(List * list) {
    if (list) {
        for (int i = 0; i <= list->mas.Size(); ++i) {
            if (list->ref.Size() != 0) {
                DeleteTree(list->ref[i]);
            }
        }
        delete list;
    }
}


