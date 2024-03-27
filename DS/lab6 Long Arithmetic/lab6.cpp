#include "long_a.hpp"

using long_type = NLongArithmetic::TLongArithmetic;

int main() {
    long_type a, b, c;
    char action;
    while (std::cin >> a >> b >> action){
        c.Clear();
        switch (action) {
        case '+':
            c = a + b;
            std::cout << c << std::endl;
            break;
        
        case '-':
            try {
                c = a - b;
            } catch (const char * er) {
                std::cout << er << std::endl;
            }
            if (c.IsOk()) {
                std::cout << c << std::endl;
            }
            break;

        case '*':
            try {
                c = a * b;
            } catch (const char * er) {
                std::cout << er << std::endl;
            }
            if (c.IsOk()) {
                std::cout << c << std::endl;
            }
            break;

        case '^':
            try {
                c = a ^ b;
            } catch (const char * er) {
                std::cout << er << std::endl;
            }
            if (c.IsOk()) {
                std::cout << c << std::endl;
            }
            break;

        case '/':
            try {
                c = a / b;
            } catch (const char * er) {
                std::cout << er << std::endl;
            }
            if (c.IsOk()) {
                std::cout << c << std::endl;
            }
            break;

        case '<':
            if (a < b) {
                std::cout << "true" << std::endl;
            } else {
                std::cout << "false" << std::endl;
            }
            
            break;
            
        case '>':
            if (a > b) {
                std::cout << "true" << std::endl;
            } else {
                std::cout << "false" << std::endl;
            }
            break;

        case '=':
            if (a == b) {
                std::cout << "true" << std::endl;
            } else {
                std::cout << "false" << std::endl;
            }
            break;
        
        default:
            break;
        }
    }
    
}