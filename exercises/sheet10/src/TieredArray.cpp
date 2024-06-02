#pragma once
#include "TieredArray.hpp"

template <typename T>
TieredArray<T>::TieredArray(size_t tier_size)
        : tier_size(tier_size), current_size(0) {
    add_tier();
}

template <typename T>
TieredArray<T>::~TieredArray() {
    for (auto tier : tiers) {
        delete[] tier;
    }
}

template <typename T>
void TieredArray<T>::insert(const T& value) {
    if (current_size == tiers.size() * tier_size) {
        add_tier();
    }
    size_t tier_index = current_size / tier_size;
    size_t index_in_tier = current_size % tier_size;
    tiers[tier_index][index_in_tier] = value;
    current_size++;
}

template <typename T>
void TieredArray<T>::remove(size_t index) {
    if (index >= current_size) {
        throw std::out_of_range("Index out of range");
    }
    size_t tier_index = index / tier_size;
    size_t index_in_tier = index % tier_size;
    for (size_t i = index; i < current_size - 1; ++i) {
        size_t next_tier_index = (i + 1) / tier_size;
        size_t next_index_in_tier = (i + 1) % tier_size;
        tiers[tier_index][index_in_tier] = tiers[next_tier_index][next_index_in_tier];
        tier_index = next_tier_index;
        index_in_tier = next_index_in_tier;
    }
    current_size--;
}

template <typename T>
T TieredArray<T>::get(size_t index) const {
    if (index >= current_size) {
        throw std::out_of_range("Index out of range");
    }
    size_t tier_index = index / tier_size;
    size_t index_in_tier = index % tier_size;
    return tiers[tier_index][index_in_tier];
}

template <typename T>
size_t TieredArray<T>::size() const {
    return current_size;
}

template <typename T>
void TieredArray<T>::add_tier() {
    tiers.push_back(new T[tier_size]);
}