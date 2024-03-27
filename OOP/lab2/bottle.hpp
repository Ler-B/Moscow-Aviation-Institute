//Будникова Валерия M8O-207Б-19
//Описание класса Bottle
#pragma once
#include <iostream>

namespace Bot
{
    class Bottle {
    private:
        double v;
        double fill;
    public:
        Bottle();
        Bottle(const double& a, const double& b);
        const Bottle operator+(const Bottle& b);
        const Bottle operator-(const Bottle& b);
        bool operator<(const Bottle& b);
        bool operator>(const Bottle& b);
        bool operator==(const Bottle& b);
        friend std::ostream& operator<<(std::ostream& os, const Bottle& b); cout << botle 
    };
    
} 

Bot::Bottle operator"" _bt(const char* str, size_t n);

