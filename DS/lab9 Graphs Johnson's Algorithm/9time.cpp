#include <set>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>

typedef std::vector<std::pair<long long, bool>> VecPair;
typedef std::vector<std::vector<std::pair<long long, long long>>> Vertex;
typedef std::vector<std::vector<std::pair<long long, long long>>> VertexL;

bool BellmanFord(std::vector<long long> &bf, const Vertex &edges, const long long &n) {
    for (long long i = 0; i < n + 1; ++i) {
        for (long long j = 0; j < edges.size(); ++j) {
            for (std::pair<long long, long long> e : edges[j]) {                
                if (bf[e.first] > bf[j] + e.second) {
                    bf[e.first] = bf[j] + e.second;
                    if (i == n) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

std::vector<std::pair<long long,bool>> Dijkstra(long long curV, const VertexL &vertexes) {
    std::set<std::pair<long long, long long>> next;
    std::vector<std::pair<long long, bool>> d(vertexes.size(), {__LONG_LONG_MAX__, false});
    d[curV].first = 0;
    next.insert(std::make_pair(d[curV].first, curV));
    
    while (!next.empty()) {

        curV = next.begin()->second;
        next.erase(next.begin());

        for (long long i = 0; i < vertexes[curV].size(); ++i) {

            long long nextVertex = vertexes[curV][i].first;
            long long lenToVer = vertexes[curV][i].second;

            if (!d[nextVertex].second && d[curV].first + lenToVer < d[nextVertex].first) {
                next.erase(std::make_pair(d[nextVertex].first, nextVertex));
                d[nextVertex].first = d[curV].first + lenToVer;
                next.insert(std::make_pair(d[nextVertex].first, nextVertex));
            }
        }
        d[curV].second = true;
    }
    return d;
}

// void Prlong long(const long long &n) {
//     for (long long i = 0; i < n; ++i) {
//         for (long long j = 0; j < n; ++j) {
//             if (j == i) {
//                 std::cout << 0;
//             } else {
//                 std::cout << "inf";
//             }
//             if (j < n - 1) std::cout << " ";
//         }
//         std::cout << std::endl;
//     }
// }

std::ostream& operator<<(std::ostream &out, std::vector<std::pair<long long, long long>> a) {
    for(long long i = 0; i < a.size(); ++i) {
        out << a[i].first << " " << a[i].second << " ";
    }
    out << std::endl;
    return out;
}

std::ostream& operator<<(std::ostream &out, const std::vector<long long> &e) { 
    for(long long i = 0; i < e.size(); ++i) {
        out << e[i] << " ";
    }
    out << std::endl;
    return out;
}

std::ostream& operator<<(std::ostream &out, const Vertex &e) {
    for (long long i = 0; i < e.size(); ++i) {
        out << "from " << i + 1 << std::endl;
        for (long long j = 0; j < e[i].size(); ++j) {
            out << "to " << e[i][j].first + 1 << "   weight " << e[i][j].second << std::endl;
        }
        
    }
    return out;
}

int main() {
    long long n = 0, m = 0;
    long long num1, num2, w;
    while(std::cin >> n >> m) {
    std::chrono::system_clock::time_point start;
    std::chrono::system_clock::time_point end;
    std::ios::sync_with_stdio(false);
    

    if (m == 0 && n == 0) return 0;
    // if (m == 0) {
    //     // Prlong long(n);
    //     r;
    // }
    start = std::chrono::system_clock::now();
    Vertex edges(n);
    for (long long i = 0; i < m; ++i) {
        std::cin >> num1 >> num2 >> w;
        edges[num1 - 1].push_back({num2 - 1, w});
    }

    //BellmanFord
    std::vector<long long> bf(n, 0);
    if (!BellmanFord(bf, edges, n)) {
        // std::cout << "Negative cycle" << std::endl;
        continue;
    }

    VertexL vertexes(n);
    for(long long i = 0; i < edges.size(); ++i) {
        for (std::pair<long long, long long> e : edges[i]) {
            vertexes[i].push_back({e.first, e.second + bf[i] - bf[e.first]});
        }
    }

    //Dijkstra
    std::vector<std::pair<long long, bool>> d;
    for (long long i = 0; i < n; ++i) {
        d = Dijkstra(i, vertexes);
        for (long long j = 0; j < d.size(); ++j) {
            if (d[j].first == __LONG_LONG_MAX__) { 
                // std::cout << "inf";
            } else {
                if (i == j) {
                    // std::cout << 0;
                } else {
                    // std::cout << d[j].first + bf[j] - bf[i];
                }
            }
            if (j < d.size() - 1) {
                // std::cout << " ";
            }
        }
        // std::cout << std::endl;
    }
    end = std::chrono::system_clock::now();
    // std::cout << n << " " << std::chrono::duration<double>(end - start).count() << std::endl;
    std::cout << n << " " << (double)((n * n)/1000) << std::endl;
    }
    return 0;
}