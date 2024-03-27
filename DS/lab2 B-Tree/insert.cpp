#include <iostream>
#include "BTree.hpp"

void BTree::Insertrec(const int &key, const unsigned long long &str, List * list) {
    if (list->mas.Size() < sizeroot && list->ref.Size() == 0) {
        list->mas.PushBackSort(elem{key, str});
        return;
    }
    
    if (list->mas.Size() == sizeroot && list->ref.Size() == 0) {
        List * list1 = new List;
        List * list2 = new List;
        elem temp = list->mas[sizeroot / 2];
        for (int i = 0; i < list->mas.Size(); ++i) {
            if (i < sizeroot / 2) {
                list1->mas.PushBack(list->mas[i]);
            }
            if (i > sizeroot / 2) {
                list2->mas.PushBack(list->mas[i]);
            }
        }
        list->mas.Clear();
        list->mas.PushBack(temp);
        list->ref.PushBack(list1);
        list->ref.PushBack(list2);
        Insertrec(key, str, list);
        return;
    }

    if (list->mas.Size() < sizeroot && list->ref.Size() != 0) {
        elem temp = {key,str};
        int ind = list->mas.Size();
        for (int i = 0; i < list->mas.Size(); ++i) {
            if (temp < list->mas[i]) {
                ind = i;
                break;
            }
        }
        if (list->ref[ind]->mas.Size() < sizeroot) {
            Insertrec(key, str, list->ref[ind]);
            return;
        } else {
            List * list1 = new List;
            List * list2 = new List;
            for (int i = 0; i < sizeroot; ++i){
                if (i < sizeroot / 2) {
                    list1->mas.PushBack(list->ref[ind]->mas[i]);
                }
                if (i > sizeroot / 2) {
                    list2->mas.PushBack(list->ref[ind]->mas[i]);
                }
            }
            if (list->ref[ind]->ref.Size() != 0) {
                for (int i = 0; i < sizeroot + 1; ++i){
                    if (i <= sizeroot / 2) {
                        list1->ref.PushBack(list->ref[ind]->ref[i]);
                    }
                    if (i > sizeroot / 2) {
                        list2->ref.PushBack(list->ref[ind]->ref[i]);
                    }
                }
            }
            list->mas.PushBackSort(list->ref[ind]->mas[sizeroot/2]);
            delete list->ref[ind];
            list->ref[ind] = list1;
            if (ind < list->mas.Size() - 1) {
                List * tempr = list->ref[ind + 1];
                list->ref[ind + 1] = list2;
                for (int i = ind + 2; i < list->mas.Size(); ++i) {
                    List * tempr1 = list->ref[i];
                    list->ref[i] = tempr;
                    tempr = tempr1;
                }
                list->ref.PushBack(tempr);
            } else {
                list->ref.PushBack(list2);
            }
        Insertrec(key, str, list->ref[ind + 1]);
        return;
        }
    }
    
    if (list->mas.Size() == sizeroot && list->ref.Size() != 0) {
        List * list1 = new List;
        List * list2 = new List;
        elem temp = list->mas[sizeroot / 2];
        for (int i = 0; i < sizeroot; ++i) {
            if (i < sizeroot / 2) {
                list1->mas.PushBack(list->mas[i]);
                list1->ref.PushBack(list->ref[i]);
            }
            if (i > sizeroot / 2) {
                list2->mas.PushBack(list->mas[i]);
                list2->ref.PushBack(list->ref[i]);
            }
        }
        list1->ref.PushBack(list->ref[sizeroot/2]);
        list2->ref.PushBack(list->ref[sizeroot]);
        list->mas.Clear();
        for (int i = 0; i < list->ref.Size(); ++i) {
            delete list->ref[i];
        }
        list->ref.Clear();
        list->mas.PushBack(temp);
        list->ref.PushBack(list1);
        list->ref.PushBack(list2);
        Insertrec(key, str, list);
        return;
    }
}

void BTree::Insert(const int &key, const unsigned long long &str) {
    Insertrec(key, str, root);
}
