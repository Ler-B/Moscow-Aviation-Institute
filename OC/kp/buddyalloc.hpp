#pragma once
#include <iostream>
#include <vector>
#include <math.h>

namespace BuddyMemory {
struct Block {
    char * adr;
    int size;
    bool free;
};

struct Page {
    std::vector<Block> block;
};


class Memory {
    private:
        std::vector<Page> memory;
        void * buff;
        int memory_size;
        int page_size;
    public:

    Memory(void * new_memory, int size, int pageSize): memory_size(size) {
        int mem = 1;
        while (pow(2, mem) < pageSize) {
            ++mem;
        }
        page_size = pow(2, mem);
        Block block1{(char *)new_memory, page_size, true};
        Page page {std::vector<Block>{block1}};
        memory.push_back(page);
    }

    ~Memory() {}
    char * allocate(const int &t) {
        int mem = 1;
        while (pow(2, mem) < t) {
            ++mem;
        }
        int mem_size = pow(2, mem);
        for (int i = 0; i < memory.size(); ++i) {
            int k = 0;
            while ((memory[i].block[k].size != mem_size || !memory[i].block[k].free) && k < memory[i].block.size()) {
                if (memory[i].block[k].size > mem_size && memory[i].block[k].free) {
                    memory[i].block[k].size /= 2;
                    Block block_new{(memory[i].block[k].adr + memory[i].block[k].size), memory[i].block[k].size, true};
                    memory[i].block.insert(memory[i].block.begin() + k, block_new);
                    --k;
                }
                ++k;
                if (k == memory[i].block.size()) {
                    break;
                }
            }
            if (k < memory[i].block.size()) {
                if (memory[i].block[k].free) {
                    memory[i].block[k].free = false;
                    return memory[i].block[k].adr;
                }
            } else if (i == memory.size() - 1) {
                if (memory.size() < memory_size / page_size) {
                    Block block1{memory[i].block[0].adr + page_size, page_size, true};
                    Page page {std::vector<Block>{block1}};
                    memory.push_back(page);
                } else {
                    // std::cout << "Не удалось выделить память" << std::endl;
                    std::bad_alloc err;
                    throw err;
                    return NULL;
                }
            }
        }
        return NULL;
    }
    void Print_condition() {
        for (int u = 0; u < memory.size(); ++u) {
            std::cout << "page: " << u << std::endl;
            for (int l = 0; l < memory[u].block.size(); ++l) {
                std::cout << "block" << l << ": " << memory[u].block[l].size << " b   "<< memory[u].block[l].free << std::endl;
            }
            std::cout << std::endl;
        }
    }
    void destroy(void * t) {
        int a = 0;
        bool fl = false;
        for (int i = 0; i < memory.size(); ++i) {
            for (int j = 0; j < memory[i].block.size(); ++j) {
                if (!memory[i].block[j].free && memory[i].block[j].adr == (char *)t) {
                    fl = true;
                    memory[i].block[j].free = true;
                    break;
                }
            }
            if (fl) {
                break;
            }
        }
        for (int i = 0; i < memory.size(); ++i) {
            int j = 0;
            while (j < memory[i].block.size()) {
                if (memory[i].block[j].size == page_size) {
                    break;
                }
                if (j == 0 && memory[i].block[j].free && memory[i].block[j + 1].free && memory[i].block[j].size == memory[i].block[j + 1].size) {
                    memory[i].block[j].size *= 2;
                    memory[i].block[j].free = true;
                    memory[i].block.erase(memory[i].block.begin() + 1);
                    j = 0;
                } else if (j == memory[i].block.size() - 1 && memory[i].block[j].free && memory[i].block[j - 1].free && memory[i].block[j].size == memory[i].block[j - 1].size) {
                    memory[i].block[j - 1].size *= 2;
                    memory[i].block.pop_back();
                    j = j - 1;
                } else if (j != memory[i].block.size() - 1 && memory[i].block[j].free && memory[i].block[j + 1].free && memory[i].block[j].size == memory[i].block[j + 1].size) {
                    memory[i].block[j].size *= 2;
                    memory[i].block[j].free = true;
                    memory[i].block.erase(memory[i].block.begin() + j + 1);
                } else  if (j != 0 && memory[i].block[j].free && memory[i].block[j - 1].free && memory[i].block[j].size == memory[i].block[j - 1].size) {
                    memory[i].block[j - 1].size *= 2;
                    memory[i].block.erase(memory[i].block.begin() + j);
                    j = j - 1;
                } else {
                    ++j;
                }
            }
        }
    }

};
}