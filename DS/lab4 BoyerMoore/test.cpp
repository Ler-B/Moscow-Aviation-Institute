#include <iostream>
#include <string>
#include <ctime>  
#include <chrono>
#define size_t unsigned

size_t ToInt(size_t a) {
    return a - '0';
}

int main(){
    char a;
    size_t num = 0;
    std::string pattern;
    std::string text;
    bool fl = true;
    int count = 0;
    while ((a = getchar()) != '\n') {
        if (a == EOF) {
            return 0;
        }
        if (a >= '0' && a <= '9') {
            num = num * 10 + ToInt(a);
            fl = true;
            count++;
        } else if (a == ' ' || a == '\t') {
            fl = false;
        }
        if (!fl && count != 0) {
            std::string str = std::to_string(num);
            for (size_t i = 0; i < str.size(); ++i) {
                pattern.push_back(str[i]);
            }
            num = 0;
            count = 0;
            fl = true;
        }
    }
    if (count != 0) {
        std::string str = std::to_string(num);
        for (size_t i = 0; i < str.size(); ++i) {
            pattern.push_back(str[i]);
        }
        num = 0;
    }
    size_t str = 1;
    size_t pos = 1;
    fl = true;
    while ((a = getchar()) != EOF) {
        if (a == '\n') {
            if (!fl) {
                std::string str = std::to_string(num);
                for (size_t i = 0; i < str.size(); ++i) {
                    text.push_back(str[i]);
                }
                num = 0;
                fl = true;
            }
            ++str;
            pos = 1;
        } else if (a >= '0' && a <= '9') {
            num = num * 10 + ToInt(a);
            fl = false;
        } else if (!fl) {
            std::string str = std::to_string(num);
            for (size_t i = 0; i < str.size(); ++i) {
                text.push_back(str[i]);
            }
            fl = true;
            ++pos;
            num = 0;
        }
    }
    if (count != 0 && !fl) {
        std::string str = std::to_string(num);
        for (size_t i = 0; i < str.size(); ++i) {
            text.push_back(str[i]);
        }
    }
    std::string::size_type n = 0;
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    // for (n = text.find(pattern, n); n != std::string::npos; n = text.find(pattern, n + 1)){} 
    while (n != std::string::npos) {
        n = text.find(pattern, n + 1);    
        std::cout << n << std::endl;  
    }
    std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
    
    // std::cout << n << std::endl;
    // n = text.find(pattern);
    std::cout << "Time std::string - find: " << std::chrono::duration<double>(end - start).count() << " s " << std::endl;
    
}