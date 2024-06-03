#pragma once

#include <stdexcept>
#include "IteratorBase.hpp"

template<typename T>
class ArrayList {
private:
    T *data;
    size_t capacity;
    size_t size;

public:
    explicit ArrayList(size_t initial_capacity = 10);

    ~ArrayList();

    void insert(const size_t index, const T &value);

    void remove(const size_t index);

    T &operator[](const size_t index);

    size_t get_size() const;

    size_t get_capacity() const;

    class Iterator : public IteratorBase<T> {
    private:
        ArrayList *arrayList;
        size_t index;

    public:
        Iterator(ArrayList *arrayList, size_t index);

        T &read() const;

        void write(const T &value);

        void insert(const T &value);

        void remove();

        bool is_end() const;

        void next();
    };

    Iterator begin();

    Iterator end();
};
