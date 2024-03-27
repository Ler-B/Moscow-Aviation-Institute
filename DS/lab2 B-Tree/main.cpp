#include <iostream>
#include "BTree.hpp"

int main(int argc, const char * argv[]) {
    BTree tree;
    for (int i = 0; i <= 5; ++i) {
        tree.Insert(i, i + 1);
        //std::cout << "9_TREE: " << std::endl; tree.Print(); std::cout << std::endl; std::cout << std::endl;
    }

    std::cout << "TREE: " << std::endl; tree.Print(); std::cout << std::endl;
    
    
    //tree.Del(2);
//    int del = 8;
//    tree.Del(del);
//    std::cout << "TREE_AFTER_DEL " << del << " :" << std::endl; tree.Print(); std::cout << std::endl;
    
//    NVector::TVector<int> Vect;
//    Vect.PushBackSort(1);
//    Vect.PushBackSort(3);
//    Vect.PushBackSort(4);
//    Vect.PushBackSort(6);
//    Vect.PushBackSort(5);
//    Vect.PushBackSort(7);
//    for (int i = 0 ; i < Vect.Size(); ++i) {
//        std::cout << Vect[i];
//    }
//    std::cout << std::endl;
//    Vect.Del(6);
//    for (int i = 0 ; i < Vect.Size(); ++i) {
//        std::cout << Vect[i];
//    }
    return 0;
}
