#include <iostream>
#include <vector>
#include <chrono>
long long n, m;

long long Min(std::vector<std::vector<std::pair<long long,short>>> &vec, int i, int j, long long &r) {
    // long long r = 0;
    if (i != n - 1) {
        if (j == 0) {
            long long m1 = Min(vec, i + 1, j, r);
            long long m2 = Min(vec, i + 1, j + 1, r);
            r += std::min(m1, m2);
        } else if (j == m - 1) {
            r += std::min(Min(vec, i + 1, j - 1, r), Min(vec, i + 1, j, r));
        } else {
            // std::cout << "+" << std::endl;
            long long t1 = std::min(Min(vec, i + 1, j, r), Min(vec, i + 1, j + 1, r));
            // std::cout << std::min(Min(vec, i + 1, j - 1), t1) << std::endl;
            r += std::min(Min(vec, i + 1, j - 1, r), t1);
        }
    } else {
        r = vec[i][j].first;
    }
    return r;
}

int main() {
    std::chrono::system_clock::time_point start;
    std::chrono::system_clock::time_point end;
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<long long,short>>> vec(n);
    std::vector<std::pair<long long, short>> str(m);
    std::vector<long long> res(m);

    for (short i = 0; i < n; ++i) {
        for (short j = 0; j < m; ++j) {
            std::cin >> str[j].first;
        }
        vec[i] = str;
    }

    start = std::chrono::system_clock::now();
    for (int i = 0; i < m; ++i) {
        long long r = 0;
        res[i] = Min(vec, 0, i, r);
    }
    
    long long min = res[0];
    for (int i = 0; i < m; ++i) {
        // std::cout << res[i] << " ";
        if (min < res[i]) min = res[i]; 
    }
    end = std::chrono::system_clock::now();
    std::cout << "time_naive: " << std::chrono::duration<double>(end - start).count() << " s " << std::endl;
}