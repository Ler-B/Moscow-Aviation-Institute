// Будникова Валерия М8О-207Б-19
// Карманная сортировка
// Требуется разработать программу, осуществляющую ввод пар «ключ-значение», 
// их упорядочивание по возрастанию ключа указанным алгоритмом сортировки за линейное время и вывод отсортированной последовательности.
// Вариант задания определяется типом ключа (и соответствующим ему методом сортировки) и типом значения:
// Карманная сортировка.
// Тип ключа: вещественные числа в промежутке [-100, 100].
// Тип значения: числа от 0 до 264 - 1.
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
            TVector(unsigned long max) {
                data = new T[max];
                size = 0;
                capacity = max;
            }
            void PushBack(const T elem);
            T& operator[](unsigned int ind);
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
    T& TVector<T>::operator[](unsigned int ind) {
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


int main() {
    NVector::TVector<TPair> elems;
    TPair p;
    while (scanf("%lf %llu", &p.key, &p.value) > 0) {
        elems.PushBack(p);
    }

    if (elems.SizeVect() == 0) {
        return 0;
    }
    
    NVector::TVector<NVector::TVector<TPair>> bucket(elems.SizeVect() + 1);
    double tempsize = 200 / (double)elems.SizeVect();
    for (unsigned int i = 0; i < elems.SizeVect(); ++i) {
        bucket[(int)((elems[i].key + 100) / tempsize)].PushBack(elems[i]);
    }

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

    for (unsigned int i = 0; i < elems.SizeVect() + 1; ++i) {
        if (bucket[i].SizeVect() != 0) {
            for (unsigned int j = 0; j < bucket[i].SizeVect(); ++j) {
                printf("%f %llu\n", bucket[i][j].key, bucket[i][j].value );
            }
        }
    }

    return 0;
}