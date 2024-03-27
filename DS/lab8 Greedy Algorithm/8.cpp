#include <iostream>

size_t count[4] = {0, 0, 0, 0};
char * a;

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
    size_t n;
    size_t res = 0; 
    std::cin >> n;
    a = new char[n];
    for (size_t i = 0; i < n; ++i) {
        std::cin >> a[i];
        ++count[a[i] - '0'];
    }
    count[2] += count[1];
    count[3] += count[2];
    for (size_t i = 0; i < count[1]; ++i) {
        if (a[i] != '1') {
            ++res;
            a[Find(a[i])] = a[i];
            a[i] = '1';
        }
    }
    for (size_t i = count[1]; i < count[2]; ++i) {
        if (a[i] != '2') ++res;
    }
    std::cout << res << std::endl;
    delete[] a;
}