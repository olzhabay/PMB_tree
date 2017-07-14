#pragma once

#include <cstdint>

class PMBtree {
private:

public:
    PMBtree();
    void search(int64_t key);
    void insert(int64_t key, int32_t idx);
    void remove(const int64_t &key);
    int32_t getHeight();
};
