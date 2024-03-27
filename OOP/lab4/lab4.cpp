#include <tuple>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <string>
#include <cmath>

template<class T>
struct Triangle {
    std::vector<std::pair<T, T>> points;
};

template<class T>
struct Hexagon {
    std::vector<std::pair<T, T>> points;
};

template<class T>
struct Octagon {
    std::vector<std::pair<T, T>> points;
};

template<class T> 
std::ostream &operator<<(std::ostream &os, const std::pair<T, T> &t) {
    os << " (" << t.first << ',' << t.second << ") ";
    return os;
}


template<size_t ind = 0, class T>
void print(const T &t) {
    if constexpr(ind < std::tuple_size<T>::value) {
        std::string s = typeid(std::get<ind>(t)).name();
        s.erase(0, 1);
        s.erase(s.length() - 3, 3);
        std::cout << s << ": ";
        for (int i = 0; i < std::get<ind>(t).points.size(); ++i){
            std::cout << std::get<ind>(t).points[i];
            if ((i + 1) % 4 == 0 && i != std::get<ind>(t).points.size() - 1) {
                std::cout << std::endl << "\t ";
            }
        }
        std::cout << std::endl << std::endl;
        print<ind + 1, T>(t);
    }
    return;
}

template<class T>
long double SQ(const std::vector<std::pair<T, T>> &fig, std::string nametype) {
    long double S = 0;
    long double side = sqrt(pow(fig[0].first - fig[1].first, 2) + pow(fig[0].second - fig[1].second, 2));
    if(nametype == "Triangle") {
        S = side * side * sqrt(3) / 4;
    }
    if(nametype == "Hexagon") {
        S = 3 * sqrt(3) * side * side / 2;
    }
    if(nametype == "Octagon") {
        S = 2 * side * side * (1 + sqrt(2));
    }
    return S;
}


template<size_t ind = 0, class T>
long double square(const T &t) {
    long double S = 0;
    if constexpr(ind < std::tuple_size<T>::value) {
        std::string name = typeid(std::get<ind>(t)).name();
        name.erase(0, 1);
        name.erase(name.length() - 3, 3);
        S = SQ(std::get<ind>(t).points, name);
        S += square<ind + 1, T>(t);
    } 
    return S;
}

int main() {
    using pair_double = std::pair<double, double>;
    Triangle<double> tr1 = {{pair_double(1.234,1.234), pair_double(-0.266,-1.36408), pair_double(2.734,-1.36408)}};
    Hexagon<double> hex1 = {{pair_double(0.567,0.567), pair_double(-0.299025,0.067), pair_double(1.43303,0.067), pair_double(-0.299025,-0.933), pair_double(1.43303,-0.933), pair_double(0.567,-1.433)}};
    Octagon<double> oct1 = {{pair_double(0.55,0.55), pair_double(5.1694,-1.36342), pair_double(-4.0694,-1.36342), pair_double(7.08281,-5.98281), pair_double(-5.98281,-5.98281), pair_double(5.1694,-8.6888), pair_double(4.0694,-8.6888), pair_double(0.55,-12.5156)}};
    using pair_int = std::pair<int, int>;
    Triangle<int> tr2 = {{pair_int(0,0), pair_int(6,0), pair_int(3,6)}};
    Hexagon<int> hex2 = {{pair_int(0,0), pair_int(5,0), pair_int(8,4), pair_int(-3,4), pair_int(0,8), pair_int(5,8)}};
    Octagon<int> oct2 = {{pair_int(0,0), pair_int(5,0), pair_int(8,4), pair_int(-3,4), pair_int(8,8), pair_int(-3,8), pair_int(0,11), pair_int(5,11)}};
    std::tuple<Triangle<double>, Hexagon<double>, Octagon<double>, Triangle<int>, Hexagon<int>, Octagon<int>> t1(tr1, hex1, oct1, tr2, hex2, oct2);
    print(t1);
    std:: cout << "Square: " << square(t1) << std::endl;;
}