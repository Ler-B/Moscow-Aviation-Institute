#include <iostream>
#include <vector>
#include <chrono>

std::pair<long long, short> * Comp(std::pair<long long, short> * v1, std::pair<long long, short> * v2) {
    return v1->first <= v2->first ? v1 : v2;
}

std::pair<long long, short> * Min(std::vector<std::pair<long long, short>> &v) {
    std::pair<long long, short> * min = &(*v.begin());
    for (std::vector<std::pair<long long, short>>::iterator i = v.begin(); i != v.end(); ++i) {
        if ((*i).first < (*min).first) min = &(*i);
    }
    return min;
}

int main() {
    std::chrono::system_clock::time_point start;
    std::chrono::system_clock::time_point end;

    short n, m;
    std::cin >> n >> m;

    std::vector<std::vector<std::pair<long long,short>>> vec(n);
    std::vector<std::pair<long long, short>> str(m);
    std::pair<long long, short> * elem;
    std::vector<long long> res(n);

    for (short i = 0; i < n; ++i) {
        for (short j = 0; j < m; ++j) {
            std::cin >> str[j].first;
        }
        vec[i] = str;
    }
    start = std::chrono::system_clock::now();
    for (short i = 1; i < n; ++i) {
        for (short j = 0; j < m; ++j) {
            elem = Comp(&vec[i - 1][std::max(0, j - 1)], &vec[i - 1][j]);
            elem = Comp(elem, &vec[i - 1][std::min(j + 1, m - 1)]);
            vec[i][j].second = elem - &vec[i - 1][0];
            vec[i][j].first = elem->first + vec[i][j].first;
        }
    }
    elem = Min(vec[n - 1]);
    end = std::chrono::system_clock::now();
    std::cout << "time_my_lab: " << std::chrono::duration<double>(end - start).count()к << " s " << std::endl;
//     res[n - 1] = elem - &vec[n - 1][0];
//     res[n - 2] = elem->second;
//     n--;
//     while (n != 1) {
//         elem->second = vec[n - 1][elem->second].second;
//         --n;
//         res[n - 1] = elem->second;
//     }
//     std::cout << elem->first << std::endl; 
//     for (short i = 0; i < res.size(); ++i) {
//         std::cout << '(' << i + 1 << "," << res[i] + 1 << ')' << " ";
//     }
//     std::cout << std::endl;
}


