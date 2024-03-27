#include <iostream>
#include <string>
#include <unordered_map>

struct TNode {
    long l;
    long r;
    long number;
    long st;
    long ref = 0;
    std::unordered_map<char, long> next;
    TNode(long ll = -1, long rr = -1, long n = -1, long s = -1) : l(ll), r(rr), number(n), st(s) {}
    long Length(long a) {
        return std::min(r, a) - l;
    }
};

struct TIter {
    TNode * node;
    long index;
    long len;
    long inserts;
    char key;
    TIter(TNode * n, long ind, char k, long l, long ins): 
    node(n), index(ind), len(l), inserts(ins), key(k) {}

    void Connect(long ind) {
        node->next[key] = ind;
    }
    void Next(std::string &str) {
        ++index;
        if (index < str.length()) key = str[index];
        --len;
    }

    void OnRef(TNode * next) {
        node = next + node->ref;
    }

};


class SuffTree {
    public:
        long end = 0;
        std::string str;
        TNode * vertexes;
        long count = 1;

        SuffTree(std::string &s) : str(s) {
            long start = 1;
            vertexes = new TNode[2 * str.length()];

            vertexes[0] = TNode(-1, -1, 0);

            TIter it(&vertexes[0], -1, '*', 0, 0);

            for(long long i = 0; i < str.length(); ++i) {
                ++end;
                char ch = str[i];
                ++it.inserts;

                if (it.inserts == 1) {
                    it.index = i;
                    it.key = ch;
                    if (it.len < 0) it.len = 0;
                }

                long split = -1;

                while (it.inserts > 0) {
                    if (it.node->next.find(it.key) == it.node->next.end()) {
                        //insert
                        vertexes[count] = TNode(it.index, str.length(), count, start);
                        it.Connect(count);

                        if (split != -1) vertexes[split].ref = it.node->number;
                        split = count;

                        if (it.node->number == 0) {
                            it.Next(str);
                        } else {
                            it.OnRef(vertexes);
                        }
                    } else {
                        //split
                        TNode * splitNode = &vertexes[it.node->next[it.key]];
                        if (it.len >= splitNode->Length(end)) {
                            it.node = splitNode;
                            it.len -= it.node->Length(end);
                            it.index += it.node->Length(end);
                            it.key = str[it.index];
                            continue;
                        }

                        if (str[splitNode->l + it.len] == ch) {
                            ++it.len;
                            if (split != -1) vertexes[split].ref = it.node->number;
                            break;
                        }

                        vertexes[count] = TNode(splitNode->l, splitNode->l + it.len, count);
                        vertexes[count + 1] = TNode(i, str.length(), count + 1, start);
                        splitNode->l += it.len;
                        it.Connect(count);
                        

                        TNode * vert = &vertexes[count];
                        vert->next[ch] = count + 1;
                        vert->next[str[splitNode->l]] = splitNode->number;
                        if (split != -1) vertexes[split].ref = vert->number;
                        split = vert->number;

                        if (it.node->number == 0) {
                            it.Next(str);
                        } else {
                            it.OnRef(vertexes);
                        }
                        ++count;
                    }
                    ++start;
                    ++count;
                    --it.inserts;
                }
            }
        }

        ~SuffTree() {
            delete[] vertexes;
        }

        void Print() {
            Print(0, 0);
        }

        void Print(int k, long num) {
            for (std::unordered_map<char, long>::iterator it = vertexes[num].next.begin(); it != vertexes[num].next.end(); ++it) {
                Print(k+1, std::get<1>(*it));
            }
            for(long i = 0; i < k * 2; ++i) std::cout << " ";
            
            for(long i = vertexes[num].l; i < vertexes[num].r; ++i) {
                std::cout << str[i];
            }
            std::cout << std::endl;

        }

        void Task(long length) {
            long i = 0;
            long len;
            while (length > 0) {
                char min = 'z' + 1;
                long j = -1;
                for (std::unordered_map<char, long>::iterator it = vertexes[i].next.begin(); it != vertexes[i].next.end(); ++it) {
                    if (std::get<0>(*it) < min && std::get<0>(*it) != '$') {
                        min = std::get<0>(*it);
                        j = std::get<1>(*it);
                    }
                }
                i = j;
                len = vertexes[i].r - vertexes[i].l;
                if (len < length) {
                    std::cout << str.substr(vertexes[i].l, len);
                    length -= len;
                } else {
                    std::cout << str.substr(vertexes[i].l, length);
                    return;
                }
            }
        }
};

int main() {
    std::ios::sync_with_stdio(false);

    std::string str;
    std::cin >> str;
    if (str ==  "") {
        return 0;
    }
    long len = str.length();
    str = str + str;
    str.push_back('$');

    SuffTree Tree(str);
    Tree.Print();
    Tree.Task(len);
    std::cout << std::endl;

    return 0;
}