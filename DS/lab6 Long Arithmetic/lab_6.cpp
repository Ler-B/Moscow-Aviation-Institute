#include <iostream>
#include <vector>
#include <string>

namespace NLongArithmetic 
{
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
} //namespace NLongArithmetic

namespace NLongArithmetic {

    TLongArithmetic::TLongArithmetic(std::vector<int> vect) {
        data = vect;
    }

    void TLongArithmetic::Init(const std::string &str) {
        data.clear();
        for(long i = str.size() - 1; i >= 0; i -= TLongArithmetic::RADIX) {
            int num = 0;
            for (int j = TLongArithmetic::RADIX - 1; j >= 0; --j) {
                if (i - j >= 0) {
                    num = num * 10 + static_cast<int>(str[i - j] - '0');
                }
            }
            data.push_back(num);
        }
        this->DeleteZeros();
    }

    bool TLongArithmetic::operator<(const TLongArithmetic &rhs) const {
        if (data.size() != rhs.data.size()) {
            return data.size() < rhs.data.size();
        }
        for (long i = data.size() - 1; i >= 0; --i) {
            if (data[i] != rhs.data[i]) {
                return data[i] < rhs.data[i];
            }
        }
        return false;
    }

    bool TLongArithmetic::operator>(const TLongArithmetic &rhs) const {
        if (data.size() != rhs.data.size()) {
            return data.size() > rhs.data.size();
        }
        for (long i = data.size() - 1; i >= 0; --i) {
            if (data[i] != rhs.data[i]) {
                return data[i] > rhs.data[i];
            }
        }
        return false;
    }

    bool TLongArithmetic::operator==(const TLongArithmetic &rhs) const{
        if (data.size() != rhs.data.size()) {
            return false;
        }
        for (unsigned long i = 0; i < data.size(); ++i) {
            if (data[i] != rhs.data[i]) {
                return false;
            }
        }
        return true;
    }

    TLongArithmetic TLongArithmetic::operator+(const TLongArithmetic &rhs) const {
        TLongArithmetic res;
        int carry = 0;
        unsigned long size = std::max(data.size(), rhs.data.size());
        res.data.resize(size + 1);
        for (unsigned long i = 0; i < size + 1; ++i) {
            int sum = carry;
            if (i < data.size()) {
                sum += data[i];
            }
            if (i < rhs.data.size()) {
                sum += rhs.data[i];
            }
            carry = sum / BASE;
            res.data[i] = sum % BASE;
        }
        res.DeleteZeros();
        return res;
    }

    TLongArithmetic TLongArithmetic::operator-(const TLongArithmetic &rhs) const {
        TLongArithmetic res;
        int carry = 0;
        unsigned long size = std::max(data.size(), rhs.data.size());
        res.data.resize(size);
        if (*this < rhs) {
            throw "Error";
        } else {    
           for (unsigned long i = 0; i < size; ++i) {
               int diff = data[i] - carry;
               if (i < rhs.data.size()) {
                   diff -= rhs.data[i];
               }
               if (diff < 0) {
                   carry = 1;
                   diff += TLongArithmetic::BASE;
               } else {
                   carry = 0;
               }
               res.data[i] = diff;
           }
        }
        res.DeleteZeros();
        return res;
    }

    TLongArithmetic TLongArithmetic::operator*(const TLongArithmetic &rhs) const {
        TLongArithmetic res;
        res.data.resize(std::max(data.size(), rhs.data.size()) * 2);
            if (rhs.data.size() < data.size()) {
                for (unsigned long j = 0; j < rhs.data.size(); ++j) {
                    for (unsigned long i = 0; i < data.size(); ++i) {
                        int multi = rhs.data[j] * data[i] + res.data[i + j];
                        res.data[i + j] = multi % TLongArithmetic::BASE;
                        res.data[i + j + 1] += multi / TLongArithmetic::BASE;
                    }
                }
            } else {
                for (unsigned long j = 0; j < data.size(); ++j) {
                    for (unsigned long i = 0; i < rhs.data.size(); ++i) {
                        int multi = data[j] * rhs.data[i] + res.data[i + j];
                        res.data[i + j] = multi % TLongArithmetic::BASE;
                        res.data[i + j + 1] += multi / TLongArithmetic::BASE;
                    }
                }
            }
        res.DeleteZeros();
        return res;
    }

    TLongArithmetic TLongArithmetic::operator^(TLongArithmetic &rhs) const {
        TLongArithmetic x, two, res, zero, pow, temp;
        if (rhs.data.size() == 1 && rhs.data[0] == 0 && data.size() == 1 && data[0] == 0) {
            throw "Error";
        } else {
            if (rhs.data.size() == 1 && rhs.data[0] == 0) {
                rhs.data[0] = 1;
                return rhs;
            }
            if (data.size() == 1 && data[0] == 0) {
                return *this;
            } 
            two.data.push_back(2);
            zero.data.push_back(0);
            res.data.push_back(1);
            x = *this;
            pow = rhs;
            while (pow > zero) {
                temp = pow / two;
                if (!(pow - temp * two == zero)){
                    res = res * x;
                }
                x = x * x;
                pow = temp;
            }
        }
        res.DeleteZeros();
        return res;
    }

    TLongArithmetic TLongArithmetic::operator/(const TLongArithmetic &rhs) const { 
        TLongArithmetic res;
        if (rhs.data.size() == 1 && rhs.data[0] == 0) {
            throw "Error";
        } else {
            if (*this < rhs) {
                res.data.resize(1);
                return res; 
            }
            TLongArithmetic temp, part;
            for (long i = data.size() - 1; i >= 0; --i) {
                part.data.insert(part.data.begin(), data[i]);
                part.DeleteZeros();
                if (!(part < rhs)) {
                    TLongArithmetic x;
                    int left = 1;
                    int right = TLongArithmetic::BASE - 1;
                    int factor = -1;
                    while (left < right && left + 1 < right) {
                        int mid = (left + right) / 2;
                        temp.Init(std::to_string(mid));
                        x = temp * rhs;
                        if (x == part) {
                            factor = mid;
                            break;
                        } 
                        if (x < part) {
                            left = mid;
                        } else {
                            right = mid;
                        }
                    }
                    if (factor != -1) {
                        res.data.insert(res.data.begin(), factor);
                        temp.Init(std::to_string(factor));
                        part = part - temp * rhs;
                    } else {
                        temp.Init(std::to_string(right));
                        if (temp * rhs < part || temp * rhs == part) {
                            res.data.insert(res.data.begin(), right);
                            part = part - temp * rhs;
                        } else {
                            res.data.insert(res.data.begin(), left);
                            temp.Init(std::to_string(left));
                            part = part - temp * rhs;
                        }
                    }
                } else {
                    res.data.insert(res.data.begin(), 0);
                }
            }
            res.DeleteZeros();
        }
        return res;
    }

    void TLongArithmetic::Clear() {
        data.clear();
    }

    bool TLongArithmetic::IsOk() const {
        return data.size() != 0;
    }

    void TLongArithmetic::DeleteZeros() {
        while (data.size() > 1 && data.back() == 0) {
            data.pop_back();
        }
    }

    std::istream& operator>>(std::istream & in, TLongArithmetic &rhs) {
        std::string str;
        in >> str;
        rhs.Init(str);
        return in;
    }

    std::ostream& operator<<(std::ostream & out, const TLongArithmetic &rhs) {
        if (rhs.data.size() == 0) {
            out << "0";
        } else {
            for (long i = rhs.data.size() - 1; i >= 0; --i) { 
                if (i != long(rhs.data.size() - 1) && rhs.data[i] < TLongArithmetic::BASE / 10) {
                    for (int j = TLongArithmetic::BASE / 10; j > 0; j /= 10) {
                        if (rhs.data[i] < j) {
                            out << '0';
                        } else {
                            break;
                        }
                    }
                } 
                if (rhs.data[i] != 0 || i == long(rhs.data.size() - 1)) out << rhs.data[i];
            }
        }
        return out;
    }
}

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