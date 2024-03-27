#pragma once

const int Length = 2;

namespace NVector
{
    template<class T>
    class TVector {
        public:
            TVector() {
                size = 0;
                capacity = 2 * Length - 1;
                data = new T[2 * Length];
            }
            ~TVector() {
                delete[] data;
            }
            void PushBack(const T elem);
            T& operator[](const unsigned int ind);
            unsigned int Size();
        void Clear() {
                size = 0;
            }
        void PushBackSort(const T elem);
        bool Del(T elem);
        bool Find(T elem, int &index);
        private:
            unsigned int size;
            unsigned int capacity;
            T * data = nullptr;
    };

    template<class T>
    void TVector<T>::PushBack(const T elem) {
        if (size == capacity) {
            T * data1 = new T[capacity << 1];
            capacity <<= 1;
            for (int i = 0; i < size; ++i) {
                data1[i] = data[i];
            }
            delete[] data;
            data = data1;
            
        }
        data[size] = elem;
        ++size;
    }

    template<class T>
    void TVector<T>::PushBackSort(const T elem) {
        if (size == capacity) {
            T * data1 = new T[capacity << 1];
            capacity <<= 1;
            int temp = 0;
            for (int i = 0; i < size; ++i) {
                if (data[i] < elem) {
                    data1[i] = data[i];
                } else {
                    temp = i;
                    break;
                }
            }
            data1[temp] = elem;
            for (int i = temp; i < size; ++i) {
                data1[i+1] = data[i];
            }
            delete[] data;
            data = data1;
            
        } else {
            T temp = elem;
            for (int i = 0; i < size; ++i) {
                if (data[i] > temp) {
                    T temp2 = data[i];
                    data[i] = temp;
                    temp = temp2;
                }
            }
            data[size] = temp;
        }
        ++size;
    }
        
    template<class T>
    bool TVector<T>::Del(const T elem) {
        T temp = elem;
        bool f = false;
        for (int i = 0; i < size; ++i) {
            if (temp == data[i] && i != size) {
                temp = data[i+1];
                data[i] = data[i + 1];
                f = true;
            } else {
                if (data[i] > temp) {
                    f = false;
                    break;
                }
                if (temp == data[i] && i == size) {
                    f = true;
                }
            }
        }
        if (f) {
            --size;
            return true;
        }
        return false;
    }

    template<class T>
    bool TVector<T>::Find(T elem, int &index) {
        for (int i = 0; i < size ; ++i) {
            if (data[i] == elem) {
                index = i;
                return true;
            }
        }
        return false;
    }

    template<class T>
    T& TVector<T>::operator[](const unsigned int ind) {
        if (data != nullptr) {
            return data[ind];
        } else {
            throw std::bad_alloc();
        }
    }

    template<class T>
    unsigned int TVector<T>::Size() {
        return size;
    }

}
