#pragma once

#include <vector>
#include <stdexcept>
#include "IteratorBase.hpp"

template<typename T>
class TieredArray {
public:
    TieredArray(size_t capacity);  // New constructor with capacity parameter

    ~TieredArray();

    void insert(size_t index, const T &value);

    void remove(size_t index);

    T &operator[](size_t index);

    size_t get_size() const;

    class Iterator : public IteratorBase<T> {
    public:
        Iterator(TieredArray *tieredArray, size_t chunkIndex = 0, size_t elementIndex = 0);

        T &read() const override;

        void write(const T &value) override;

        void insert(const T &value) override;

        void remove() override;

        bool is_end() const override;

        void next() override;

    private:
        TieredArray *tieredArray;
        size_t chunkIndex;
        size_t elementIndex;
    };

    Iterator begin();

    Iterator end();

private:
    std::vector<std::vector<T>> data;
    size_t size;
    size_t capacity;
    static const size_t CHUNK_SIZE = 10;
};