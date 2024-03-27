#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include "stdio.h"

namespace NVector
{
    template<class T>
    class TVector {
        public:
            TVector() {
                size = 0;
                capacity = 0;
                data = 0;
            }
            ~TVector() {
                delete[] data;
            }
            TVector(unsigned int max) {
                data = new T[max];
                size = 0;
                capacity = max;
            }
            void PushBack(const T elem);
            T &operator[](unsigned int ind);
            unsigned int SizeVect();
        private:
            unsigned int size;
            unsigned int capacity;
            T * data;
    };

    template<class T>
    void TVector<T>::PushBack(const T elem) {
        if (capacity == 0){
            data = new T[4];
            capacity = 4;
        } else {
            if (size == capacity) {
                T * data1 = new T[capacity << 1];
                capacity <<= 1;
                for (int i = 0; i < size; ++i) {
                    data1[i] = data[i];
                }
                
                delete[] data;
                data = data1;
                
            }    
        }
        data[size] = elem;
        size ++;
    }

    template<class T>
    T &TVector<T>::operator[](unsigned int ind) {
        return data[ind];
    }

    template<class T>
    unsigned int TVector<T>::SizeVect() {
        return size;
    }

}

struct TPair {
    double key;
    unsigned long long value;
};

bool operator<(const TPair& l, const TPair& r) {
    return l.key < r.key;
}


int main() {
    std::vector<TPair> sort;
    NVector::TVector<TPair> elems;
    TPair p;
    while (scanf("%lf %llu", &p.key, &p.value) > 0) {
        elems.PushBack(p);
        sort.push_back(p);
    }

    if (elems.SizeVect() == 0) {
        return 0;
    }
    
    double tempsize = 200 / (double)elems.SizeVect();
    NVector::TVector<NVector::TVector<TPair>> bucket(elems.SizeVect() + 1);

    for (unsigned int i = 0; i < elems.SizeVect(); ++i) {
        bucket[(int)((elems[i].key + 100) / tempsize)].PushBack(elems[i]);
    }

    std::chrono::system_clock::time_point start1 = std::chrono::system_clock::now();
    TPair temp;
    for (unsigned int i = 0; i < elems.SizeVect() + 1; ++i) {
        if (bucket[i].SizeVect() >= 2) {
            for (unsigned int j = 1; j < bucket[i].SizeVect(); ++j) {
                double key = bucket[i][j].key;
                temp = bucket[i][j];
                int k = j - 1;
                while (k >= 0 && bucket[i][k].key > key) {
                    bucket[i][k + 1] = bucket[i][k];
                    k--;
                }
                bucket[i][k + 1] = temp;
            }
        }
    }
    

    for (unsigned int i = 0; i < elems.SizeVect(); ++i) {
        if (bucket[i].SizeVect() != 0) {
            for (unsigned int j = 0; j < bucket[i].SizeVect(); ++j) {
                //printf("%f %llu\n", bucket[i][j].key, bucket[i][j].value );
            }
        }
    }
    std::chrono::system_clock::time_point end1 = std::chrono::system_clock::now();
   
    std::chrono::system_clock::time_point start2 = std::chrono::system_clock::now();
    std::stable_sort(sort.begin(), sort.end());
    std::chrono::system_clock::time_point end2 = std::chrono::system_clock::now();

    // for(int i = 0; i < sort.size(); ++i) {
    //     printf("%f %llu\n", sort[i].key, sort[i].value );
    // }

    std::cout << "Карманная:\t" << std::chrono::duration<double>(end1 - start1).count() << std::endl;
    std::cout << "Стабильная из std:\t" << std::chrono::duration<double>(end2 - start2).count() << std::endl;
    return 0;
}