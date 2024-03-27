#include <iostream>
#include <vector>
#include <chrono>

size_t count[4] = {0, 0, 0, 0};
char * a;

 bool operator<(std::vector<int> l, std::vector<int> r) {
    if (l[0] == r[0]) {
        return l[1] < r[1];
    }
    return l[0] < r[0];
 }
short Find(char find) {
    short num = find - '0';
    for (size_t i = count[num - 1]; i < count[num]; ++i) {
        if (a[i] == '1') return i;
    }
    num = (num - 1) % 2 + 2;
    for (size_t i = count[num - 1]; i < count[num]; ++i) {
        if (a[i] == '1') return i;
    }
    return -1;
}

int main() {
    // std::chrono::system_clock::time_point start;
    // std::chrono::system_clock::time_point end;
    // size_t n = 0;
    // size_t res = 0;
    // while(std::cin >> n) {
    //     count[1] = 0; count[2] = 0; count[3] = 0;

    //     a = (char *)malloc(n + 1);
    //     res = 0; 
    //     // std::cout << res << std::endl;
    //     char x;
    //     for (size_t i = 0; i < n; ++i) {
    //         std::cin >> x;
    //         a[i] = x;
    //     }
    //     start = std::chrono::system_clock::now();
    //     for (size_t i = 0; i < n; ++i) {
    //         ++count[a[i] - '0'];
    //     }
    //     count[2] += count[1];
    //     count[3] += count[2];
    //     for (size_t i = 0; i < count[1]; ++i) {
    //         if (a[i] != '1') {
    //             ++res;
    //             a[Find(a[i])] = a[i];
    //             a[i] = '1';
    //         }
    //     }
    //     for (size_t i = count[1]; i < count[2]; ++i) {
    //         if (a[i] != '2') ++res;
    //     }
    //     end = std::chrono::system_clock::now();
    //     // std::cout << res << std::endl;
    //     std::cout << n << " " << std::chrono::duration<double>(end - start).count() << std::endl;
    //     // std::cout << res << std::endl;
    //     free(a);
    //     // std::cout << res << std::endl;
    //     a = NULL;
    // }
    std::vector<int> l = {0, 2};
    std::vector<int> r = {1, 2};
    std::vector<int> l1 = {0, 1};
    bool a = l < r;
    std::vector<std::vector<int>> re = {r, l, l1};
    std::sort(re.begin(), re.end());
    for (int i = 0; i < 2; ++i) {
        std::cout << re[i][0] << " " << re[i][1] << std::endl;
    }
    if (1 < 3 &&
        8 > 2 ) std::cout << "lll" << std::endl;
    std::cout << a << std::endl;
}