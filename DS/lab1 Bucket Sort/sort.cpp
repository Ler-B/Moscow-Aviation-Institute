#include "stdio.h"
#include <vector>
#include <algorithm>

struct TPair {
    double key;
    unsigned long long value;
};

bool operator<(const TPair& l, const TPair& r) {
    return l.key < r.key;
}

int main() {
    std::vector<TPair> sort;
    TPair p;
    while (scanf("%lf %llu", &p.key, &p.value) > 0) {
            sort.push_back(p);
    }
    std::stable_sort(sort.begin(), sort.end());
    for(int i = 0; i < sort.size(); ++i) {
        printf("%f %llu\n", sort[i].key, sort[i].value );
    }
}