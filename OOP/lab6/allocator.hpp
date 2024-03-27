//Будниква Валерия 207
//Фигура - шестиугольник
//Динамический массив для коллекции фигур
//Стек для указателей на блоки памяти

#pragma once
#include <stack>
#include <iostream>

template<class T, std::size_t BLOCK_SIZE>
class Allocator {
    private:
        std::stack<T*> stack;
        T * buff;
    public:
    using allocator_type = Allocator;
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using const_reference = const T&;
	using size_type = std::size_t;

    Allocator(): buff(nullptr) {
        static_assert(BLOCK_SIZE > 0, "BLOCK_SIZE = 0!");
    }

    ~Allocator() {
        delete[] buff;
        //std::cout << "destr" << std::endl;
    }

    template<class U> 
    struct rebind {
        using other = Allocator<U, BLOCK_SIZE>;
    };

    T * allocate(std::size_t n) {
        //std::cout << "allocate" << std::endl;
        if (buff == nullptr) {
            buff = new T[BLOCK_SIZE];
            for (std::size_t i = 0; i < BLOCK_SIZE; ++i){
                stack.push(&buff[i]);
            }
        }
        if (stack.size() < n) {
            std::bad_alloc err;
            throw err;
        }
        for (std::size_t i = 0; i < n - 1; ++i) {
            stack.pop();
        }
        T * a = stack.top();
        stack.pop();
        return a;
    }

    void deallocate (T * , std::size_t ) {
        //-
    }

    void destroy(T * p) {
        p->~T();
    }

    template<typename U, typename... Args> 
    void construct(U * p, Args&&...args) {
        new (p) U(std::forward<Args>(args)...);
    }  
};