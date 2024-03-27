#pragma once
#include <iostream>
#include <vector>
#include <math.h>

namespace BuddyMemoryPro {
struct Block {
    char * adr;
    int size;
    bool free;
};

struct Page {
    std::vector<Block> block;
    int l;
    int g;
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
        Page page {std::vector<Block>{block1}, 1, 0};
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
            bool flag = false;
            while ((memory[i].block[k].size != mem_size || !memory[i].block[k].free) && k < memory[i].block.size()) {
                if (memory[i].block[k].size > mem_size && memory[i].block[k].free) {
                    if (memory[i].block[k].size == page_size || !flag) {
                        ++memory[i].g;
                        ++memory[i].g;
                        --memory[i].l;
                    } else {
                        ++memory[i].l;
                    }
                    flag = true;
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
                    
                    if (k == 0 && memory[i].block[k].free && memory[i].block[k + 1].free && memory[i].block[k].size == memory[i].block[k + 1].size) {
                        --memory[i].g;
                        --memory[i].g;
                        ++memory[i].l;
                    } else if (k == memory[i].block.size() - 1 && memory[i].block[k].free && memory[i].block[k - 1].free && memory[i].block[k].size == memory[i].block[k - 1].size) {
                        --memory[i].g;
                        --memory[i].g;
                        ++memory[i].l;
                    } else if (k != memory[i].block.size() - 1 && memory[i].block[k].free && memory[i].block[k + 1].free && memory[i].block[k].size == memory[i].block[k + 1].size) {
                        --memory[i].g;
                        --memory[i].g;
                        ++memory[i].l;
                    } else  if (k != 0 && memory[i].block[k].free && memory[i].block[k - 1].free && memory[i].block[k].size == memory[i].block[k - 1].size) {
                        --memory[i].g;
                        --memory[i].g;
                        ++memory[i].l;
                    } else {
                        --memory[i].l;
                    }
                    memory[i].block[k].free = false;
                    if (memory[i].block[k].size == page_size) {
                        memory[i].g = 0;
                        memory[i].l = 0;
                    }
                    return memory[i].block[k].adr;
                }
            } else if (i == memory.size() - 1) {
                if (memory.size() < memory_size / page_size) {
                    Block block1{memory[i].block[0].adr + page_size, page_size, true};
                    Page page {std::vector<Block>{block1}, 1, 0};
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
        int page = 0;
        bool fl = false;
        for (int i = 0; i < memory.size(); ++i) {
            for (int j = 0; j < memory[i].block.size(); ++j) {
                if (!memory[i].block[j].free && memory[i].block[j].adr == (char *)t) {
                    fl = true;
                    page = i;
                    memory[i].block[j].free = true;
                    if  ((j == 0 && memory[i].block[j].size == memory[i].block[j + 1].size && !memory[i].block[j + 1].free) ||
                        (j == memory[i].block.size() - 1 && memory[i].block[j].size == memory[i].block[j - 1].size && !memory[i].block[j - 1].free)) {
                        ++memory[i].l;
                        break;
                    } else 
                    if ((j != 0 && memory[i].block[j].size == memory[i].block[j - 1].size && memory[i].block[j - 1].free) ||
                        (j != memory[i].block.size() - 1 && memory[i].block[j].size == memory[i].block[j + 1].size && memory[i].block[j + 1].free)) {

                        int count = 0;
                        int count2 = 0;
                        memory[i].l = 0;
                        memory[i].g = 0;
                        for (int l = 0; l < memory[i].block.size() - 2; ++l) {
                            if (memory[i].block[l].size == memory[i].block[l + 1].size && memory[i].block[l].free && memory[i].block[l + 1].free) {
                                ++memory[i].g;
                                ++memory[i].g;
                                count += memory[i].block[l].size * 2;
                                count2 = memory[i].block[l].size * 2;
                                ++l;
                            } else if (memory[i].block[l].free && (memory[i].block[l].size == count || memory[i].block[l].size == count2)) {
                                count += memory[i].block[l].size;
                                count2 += memory[i].block[l].size;
                                ++memory[i].g;
                            } else if (memory[i].block[l].free) {
                                count = 0;
                                count2 = 0;
                                ++memory[i].l;
                            } else {
                                count2 = 0;
                                count = 0;
                            }
                        }
                        if (memory[i].block[memory[i].block.size() - 2].free && (memory[i].block[memory[i].block.size() - 2].size == count || memory[i].block[memory[i].block.size() - 2].size == count2)) {
                            count += memory[i].block[memory[i].block.size() - 2].size;
                            count2 += memory[i].block[memory[i].block.size() - 2].size;
                            ++memory[i].g;
                            if (memory[i].block[memory[i].block.size() - 1].free && (memory[i].block[memory[i].block.size() - 1].size == count || memory[i].block[memory[i].block.size() - 1].size == count2)) {
                                count += memory[i].block[memory[i].block.size() - 1].size;
                                ++memory[i].g;
                            } else {
                                ++memory[i].l;
                            }
                        } else if (memory[i].block[memory[i].block.size() - 1].free && memory[i].block[memory[i].block.size() - 1].free && memory[i].block[memory[i].block.size() - 1].size != memory[i].block[memory[i].block.size() - 2].size) {
                            ++memory[i].l;
                            ++memory[i].l;
                        }
                    } else {
                        ++memory[i].l;
                    }
                    break;
                }
                if (fl) break;
            }
            if (fl) break;
        }
        if (fl) {
            if ((memory[page].block.size() - 2 * memory[page].l - memory[page].g) < 2 ) {
                int j = 0;
                while (j < memory[page].block.size()) {
                    if (memory[page].block[j].size == page_size) {
                        break;
                    }
                    if (j == 0 && memory[page].block[j].free && memory[page].block[j + 1].free && memory[page].block[j].size == memory[page].block[j + 1].size) {
                        memory[page].block[j].size *= 2;
                        memory[page].block[j].free = true;
                        memory[page].block.erase(memory[page].block.begin() + 1);
                        j = 0;
                    } else if (j == memory[page].block.size() - 1 && memory[page].block[j].free && memory[page].block[j - 1].free && memory[page].block[j].size == memory[page].block[j - 1].size) {
                        memory[page].block[j - 1].size *= 2;
                        memory[page].block.pop_back();
                        j = j - 1;
                    } else if (j != memory[page].block.size() - 1 && memory[page].block[j].free && memory[page].block[j + 1].free && memory[page].block[j].size == memory[page].block[j + 1].size) {
                        memory[page].block[j].size *= 2;
                        memory[page].block[j].free = true;
                        memory[page].block.erase(memory[page].block.begin() + j + 1);
                    } else  if (j != 0 && memory[page].block[j].free && memory[page].block[j - 1].free && memory[page].block[j].size == memory[page].block[j - 1].size) {
                        memory[page].block[j - 1].size *= 2;
                        memory[page].block.erase(memory[page].block.begin() + j);
                        j = j - 1;
                    } else {
                        ++j;
                    }
                }
            }
        }
    }

};
}