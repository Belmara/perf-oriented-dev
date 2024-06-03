#pragma once

#include <stdexcept>
#include "IteratorBase.hpp"
#include "Container.hpp"

template<typename T>
class ArrayList : public Container<T> {
private:
    T *data;
    size_t capacity;
    size_t size;

public:
    explicit ArrayList(size_t initial_capacity = 10);

    ~ArrayList();

    void insert(const size_t index, const T &value) override;

    void remove(const size_t index) override;

    T &operator[](const size_t index) override;

    size_t get_size() const override;

    size_t get_capacity() const;

    class Iterator : public Container<T>::Iterator {
    private:
        ArrayList *arrayList;
        size_t index;

    public:
        Iterator(ArrayList *arrayList, size_t index);

        T &read() const override;

        void write(const T &value) override;

        void insert(const T &value) override;

        void remove() override;

        bool is_end() const override;

        void next() override;
    };

    Iterator* begin() override;

    Iterator* end() override;
};
