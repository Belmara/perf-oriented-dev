#pragma once
#include <vector>
#include <stdexcept>

template <typename T>
class TieredArray {
public:
    TieredArray(size_t tier_size);

    ~TieredArray();

    void insert(const T &value);

    T get(size_t index) const;

    size_t size() const;
    void remove(size_t index);

private:
    size_t tier_size;
    size_t current_size;
    std::vector<T *> tiers;

    void add_tier();

};