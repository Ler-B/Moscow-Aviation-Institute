#include <iostream>
#include "BTree.hpp"

//УДАЛЕНИЕ
void BTree::Del(const int &key, List * list) {
    elem el{key, 0};
    int index = 0;
    bool f = true;
    if (list->mas.Find(el, index)) {
        f = false;
    }
    if (list->ref.Size() == 0 && list->mas.Size() > Length - 1) {
        if (list->mas.Del(el)) {
            std::cout << "OK!   " << std::endl;
        } else {
            std::cout << "NO!   " << std::endl;
        }
        return;
    }
    if (list->ref.Size() != 0) {
        int ind = list->mas.Size();
        for (int i = 0; i < list->mas.Size(); ++i) {
            if (list->mas[i].key >= key) {
                ind = i;
                break;
            }
        }
//        std::cout << "ind:  " << ind << std::endl;
        if (ind != 0 && list->ref[ind - 1]->mas.Size() > Length - 1 && f) {
            std::cout << "1" << std::endl;
            elem temp = list->ref[ind-1]->mas[list->ref[ind - 1]->mas.Size() - 1];
            list->ref[ind - 1]->mas.Del(temp);
            list->ref[ind]->mas.PushBackSort(list->mas[ind]);
            List * tempr = list->ref[ind]->ref[0];
            list->ref[ind]->ref[0] = list->ref[ind-1]->ref[list->ref[ind - 1]->mas.Size()];
            for (int i = 1; i < list->ref[ind]->ref.Size(); ++i){
                List * tempr2 = list->ref[ind]->ref[i];
                list->ref[ind]->ref[i] = tempr;
                tempr = tempr2;
            }
            list->ref[ind]->ref.PushBack(tempr);
            list->ref[ind - 1]->ref.Del(list->ref[ind-1]->ref[list->ref[ind - 1]->mas.Size()]);
            list->mas[ind - 1] = temp;
        } else if (ind != list->mas.Size() && list->ref[ind + 1]->mas.Size() > Length - 1 && f) {
            std::cout << "2" << std::endl;
//            std::cout << "TREE: " << std::endl; Print(list, 0); std::cout << std::endl;
            elem temp = list->ref[ind + 1]->mas[0];
//            std::cout << "TREE: " << std::endl; Print(list->ref[ind + 1], 0); std::cout << std::endl;
            list->ref[ind + 1]->mas.Del(temp);
            list->ref[ind]->mas.PushBack(list->mas[ind]);
            if (list->ref[ind]->ref.Size() != 0) {
                list->ref[ind]->ref.PushBack(list->ref[ind+1]->ref[0]);
                list->ref[ind + 1]->ref.Del(list->ref[ind+1]->ref[0]);
            }
            list->mas[ind] = temp;
        } else if (ind != 0 && list->ref[ind - 1]->mas.Size() <= Length - 1 && f) {
            std::cout << "3" << std::endl;
            List * list1 = new List;
            for (int i = 0; i < list->ref[ind - 1]->mas.Size(); ++i) {
                list1->mas.PushBack(list->ref[ind - 1]->mas[i]);
                if (list->ref[ind]->ref.Size() != 0) {
                    list1->ref.PushBack(list->ref[ind - 1]->ref[i]);
                }
            }
            if (list->ref[ind]->ref.Size() != 0) {
                list1->ref.PushBack(list->ref[ind - 1]->ref[list->ref[ind - 1]->mas.Size()]);
            }
            list1->mas.PushBack(list->mas[ind - 1]);
            for (int i = 0; i < list->ref[ind]->mas.Size(); ++i) {
                list1->mas.PushBack(list->ref[ind]->mas[i]);
                if (list->ref[ind]->ref.Size() != 0) {
                    list1->ref.PushBack(list->ref[ind]->ref[i]);
                }
            }
            if (list->ref[ind]->ref.Size() != 0) {
                list1->ref.PushBack(list->ref[ind]->ref[list->ref[ind]->mas.Size()]);
            }
            list->mas.Del(list->mas[ind - 1]);
            list->ref.Del(list->ref[ind]);
            
            if (list == root && list->mas.Size() == 0) {
                root = list1;
            } else {
                list->ref[ind - 1] = list1;
            }
        } else if (ind != list->mas.Size() && list->ref[ind + 1]->mas.Size() <= Length - 1 && f) {
            std::cout << "4" << std::endl;
            List * list1 = new List;
            for (int i = 0; i < list->ref[ind]->mas.Size(); ++i) {
                list1->mas.PushBack(list->ref[ind]->mas[i]);
                if (list->ref[ind]->ref.Size() != 0) {
                    list1->ref.PushBack(list->ref[ind]->ref[i]);
                }
            }
            if (list->ref[ind]->ref.Size() != 0) {
                list1->ref.PushBack(list->ref[ind]->ref[list->ref[ind]->mas.Size()]);
            }
            list1->mas.PushBack(list->mas[ind]);
            for (int i = 0; i < list->ref[ind + 1]->mas.Size(); ++i) {
                list1->mas.PushBack(list->ref[ind + 1]->mas[i]);
                if (list->ref[ind]->ref.Size() != 0) {
                    list1->ref.PushBack(list->ref[ind + 1]->ref[i]);
                }
            }
            if (list->ref[ind]->ref.Size() != 0) {
                list1->ref.PushBack(list->ref[ind]->ref[list->ref[ind + 1]->mas.Size()]);
            }
            list->mas.Del(list->mas[ind]);
            list->ref.Del(list->ref[ind]);
            
            if (list == root && list->mas.Size() == 0) {
                root = list1;
            } else {
                list->ref[ind] = list1;
            }
        }
        if (list->mas.Find(el, index)){
            std::cout << "ind_List: " << ind << "key " << key <<  "  in list" << std::endl;
            List * min = list->ref[ind];
            std::cout << std::endl;
            while (min->ref.Size() != 0) {
                min = min->ref[0];
            }
            list->mas[index] = min->mas[0];
            Del(min->mas[0].key, list->ref[ind]);
            return;
        } else {
            Del(key, list->ref[ind]);
        }
    }
}

//УДАЛЕНИЕ
void BTree::Del(const int &key) {
    Del(key, root);
}

