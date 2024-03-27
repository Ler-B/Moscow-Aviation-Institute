#include <iostream>
#include "buddyalloc.hpp"
#include "buddyallocpro.hpp"
#include <time.h>

int main() {
    // long double time_begin1, time_end1;
    // long double time_begin2, time_end2;
    
    // for (int i = 0; i < 1000; ++i) {
    //     int t = 1;
    //     while(pow(2, t) < i) {
    //         ++t;
    //     }
    //     std::cout << pow(2, t) << " " << i << std::endl;
    // }
    
    
    int * c[10000];
    int k = 0;
    void * buffa = malloc(1024);
    BuddyMemoryPro::Memory a(buffa, 1024, 32);
    std::cout << "Размер страницы - 32" << std::endl;
        for (int i = 1; i < 5; ++i) {
            c[i] = (int *)a.allocate(sizeof(int) * i); 
            std::cout <<  "Выделилось " << 4 * i << " байт" <<std::endl;
            a.Print_condition();
        }
        for (int i = 1; i < 5; ++i) {
            a.destroy(c[i]); 
            std::cout <<  "Удалился " << i << " блок" <<std::endl;
            a.Print_condition();
        }
        
    free(buffa);
        
        
    //     k += 10;
    //     
    // }
    // while (k <= 5000) {
    //     void * buffb = malloc(1024 * 1000);
    //     BuddyMemoryPro::Memory b(buffb, 1024 * 1000, 1024);
    //     int count = 0;
    //     long double time = 0;
    //     time_begin1 = clock();
    //     for (int i = 0; i < k; ++i) {
    //         c[i] = (int *)b.allocate(sizeof(int)); 
    //         b.destroy(c[i]);
    //     }
    //     time_end1 = clock();
    //     std::cout << time_end1 - time_begin1 << " " << k << std::endl;
    //     // for (int i = 0; i < k; ++i) {
    //     //     if (i > 10 && i % 10 == 0) {
    //     //         time_begin1 = clock();
    //     //         b.destroy(c[i - 10]);
    //     //         time_end1 = clock();
    //     //         time += time_end1 - time_begin1;
    //     //         count++;
    //     //     }
    //     // }

    //     free(buffb);
    //     k += 10;
    // }

   
   
    

    
    
    return 0;
}