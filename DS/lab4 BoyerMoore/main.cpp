#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <ctime>  
#include <algorithm>

#define size_t unsigned

struct TNum {
    size_t num;
    size_t str;
    size_t pos;
    const bool operator!=(size_t a) const {
        return num != a;
    }
};

size_t ToInt(size_t a) {
    return a - '0';
}

size_t BadSymbRule(const std::vector<size_t> &in, const size_t &j) {
    bool f = false;
    size_t pos = 0;
    for(size_t i = 0 ; i < in.size(); ++i) {
        if (in[i] < j) {
            f = true;
            pos = i;
        }
        if (in[i] > j) {
            break;
        }
    }
    return f ? in[pos] : in[0];
}
void GoogSuffRule(const std::vector<size_t> &nz, const std::vector<size_t> &pattern, std::vector<size_t> &l) {
    for (size_t i = 1; i < pattern.size() - 1; ++i) {
        if (nz[i] != 0) {
            if (pattern.size() - nz[i] + 1 < l.size() && pattern.size() - nz[i] + 1 >= 0) {
                l[pattern.size() - nz[i] + 1] = i;
            }
        }
    }
}

void BM(const std::vector<size_t> &pattern, const std::vector<TNum> &text, const std::map<size_t, std::vector<size_t>> &forBadSuff, const std::vector<size_t> &l) {
    for (size_t i = 0; i < text.size(); ) {
        size_t step = 1;
        bool flag = false;
        size_t pps = 0;
        for (size_t j = pattern.size() - 1; j >= 0; --j) {
            if (i + j >= text.size()) {
                return;
            }
            if (text[i + j] != pattern[j]) {
                pps = j;
                flag = true;
                break;
            }
            if (j == 0) {
                break;
            }
        }
        if (!flag) {
            std::cout << text[i].str << ", " << text[i].pos << std::endl;
            // return;
        }
        if (flag) {
            if (forBadSuff.find(text[i + pps].num) != forBadSuff.end()) {
                size_t bs = BadSymbRule(forBadSuff.find(text[i + pps].num)->second, pps);
                if (bs < pps) {
                    step = pps - bs;
                } else {
                    step = pattern.size();
                }
            }
            if (pps > 0 && l[pps - 1] != 0 && pattern.size() - pps > l[pps - 1] && pattern.size() > l[pps - 1] && (pattern.size() - l[pps - 1]) > step) {
                step = pattern.size() - l[pps - 1];
            }
        }
        if (step > 0) {
            i += step;
        } else {
            ++i;
        }
    }
}


int main() {
    char a;
    size_t num = 0;
    std::vector<size_t> pattern;
    std::vector<TNum> text;
    bool fl = true;
    int count = 0;
    while ((a = getchar()) != '\n') {
        if (a == EOF) {
            return 0;
        }
        if (a >= '0' && a <= '9') {
            num = num * 10 + ToInt(a);
            fl = true;
            count++;
        } else if (a == ' ' || a == '\t') {
            fl = false;
        }
        if (!fl && count != 0) {
            pattern.push_back(num);
            num = 0;
            count = 0;
            fl = true;
        }
    }
    if (count != 0) {
        pattern.push_back(num);
        num = 0;
    }
    size_t str = 1;
    size_t pos = 1;
    fl = true;
    while ((a = getchar()) != EOF) {
        if (a == '\n') {
            if (!fl) {
                text.push_back(TNum{num, str, pos});
                num = 0;
                fl = true;
            }
            ++str;
            pos = 1;
        } else if (a >= '0' && a <= '9') {
            num = num * 10 + ToInt(a);
            fl = false;
        } else if (!fl) {
            text.push_back(TNum{num, str, pos});
            fl = true;
            ++pos;
            num = 0;
        }
    }
    if (count != 0 && !fl) {
        text.push_back(TNum{num, str, pos});
    }
    if (pattern.size() == 0 || text.size() == 0 || pattern.size() > text.size()) {
        return 0;
    }
    std::map<size_t, std::vector<size_t>> forBadSuff;
    for(size_t i = 0; i < pattern.size(); ++i) {
        if (forBadSuff.find(pattern[i]) == forBadSuff.end()) {
            forBadSuff.insert(std::pair<size_t, std::vector<size_t>>{pattern[i], {i}});
        } else {
            forBadSuff.find(pattern[i])->second.push_back(i);
        }
    }
    std::reverse(pattern.begin(), pattern.end());
    std::vector<size_t> nz;
    size_t l = 0;
    size_t r = 0;
    for (size_t i = 0; i < pattern.size() ; ++i) {
        nz.push_back(0);
    }
    for (size_t i = 1; i < pattern.size(); ++i) {
        if (r > i) {
            if (r - i < nz[i - l] && r - i > 0) {
                nz[i] = r - i;
            } else if (r - i > nz[i - l] && nz[i - l] > 0) {
                nz[i] = nz[i - l];
            }
        } else {
            nz[i] = 0;
        }
        while (i + nz[i] < pattern.size() && pattern[nz[i]] == pattern[i + nz[i]]) {
            ++nz[i];
        }
        if (i + nz[i] > r) {
            l = i;
            r = i + nz[i];
        }
    }
    std::reverse(pattern.begin(), pattern.end());
    std::reverse(nz.begin(), nz.end());
    std::vector<size_t> lbs;
    for (size_t i = 0; i < pattern.size() ; ++i) {
        lbs.push_back(0);
    }
    GoogSuffRule(nz, pattern, lbs);
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    BM(pattern, text, forBadSuff, lbs);
    std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
    std::cout << "Time B-M: " << std::chrono::duration<double>(end - start).count() << " s " << std::endl;

    pattern.clear();
    text.clear();
    forBadSuff.clear();
    lbs.clear();
    nz.clear();
}
