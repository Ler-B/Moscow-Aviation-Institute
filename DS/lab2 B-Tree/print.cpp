#include <iostream>
#include "BTree.hpp"

//ПЕЧАТЬ
void BTree::Print(List * list, const int &p) {
    for (int i = 0; i < list->mas.Size() + 1; ++i) {
        if (list->ref.Size() != 0) {
            Print(list->ref[i], p + 2);
        }
        if (i < list->mas.Size()) {
            for (int j = 0; j < p * 2; ++j) {
                std::cout << "  ";
            }
            std::cout << list->mas[i].key;
            if (list->ref.Size() != 0) {
                std::cout << "--|";
            }
            std::cout << std:: endl;
        }
    }
}

void BTree::Print() {
    Print(root, 0);
}
