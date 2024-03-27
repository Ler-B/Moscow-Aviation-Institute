#pragma once

#include <iostream>
#include <vector>
#include <string>

namespace NLongArithmetic {

class TLongArithmetic {
    static const int BASE = 10000;
    static const int RADIX = 4;
    public:
        TLongArithmetic() = default;
        TLongArithmetic(std::vector<int> vect);
        
        void Clear();
        bool IsOk() const;
        void DeleteZeros();
        void Init(const std::string &str);
        bool operator<(const TLongArithmetic &rhs) const;
        bool operator>(const TLongArithmetic &rhs) const;
        bool operator==(const TLongArithmetic &rhs) const;
        
        TLongArithmetic operator^(TLongArithmetic &rhs) const;
        TLongArithmetic operator+(const TLongArithmetic &rhs) const;
        TLongArithmetic operator-(const TLongArithmetic &rhs) const;
        TLongArithmetic operator*(const TLongArithmetic &rhs) const;
        TLongArithmetic operator/(const TLongArithmetic &rhs) const;

        friend std::istream& operator>>(std::istream & in, TLongArithmetic &rhs);
        friend std::ostream& operator<<(std::ostream & out, const TLongArithmetic &rhs);
        
    private:
        std::vector<int> data;
};

} //namespace LongArithmetic