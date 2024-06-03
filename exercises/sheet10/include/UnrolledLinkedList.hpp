#pragma once

#include "Container.hpp"
#include "IteratorBase.hpp"
#include <vector>
#include <stdexcept>

template<typename T>
class UnrolledLinkedList : public Container<T> {
public:
    UnrolledLinkedList();
    ~UnrolledLinkedList();

    void insert(size_t index, const T &value) override;
    void remove(size_t index) override;
    T& operator[](size_t index) override;
    size_t get_size() const override;

    class Iterator : public IteratorBase<T> {
    public:
        Iterator(UnrolledLinkedList *unrolledLinkedList, size_t chunkIndex, size_t elementIndex);
        T &read() const override;

        void write(const T &value) override;

        void insert(const T &value) override;

        void remove() override;

        bool is_end() const override;

        void next() override;
    private:
        UnrolledLinkedList *unrolledLinkedList;
        size_t nodeIndex;
        size_t elementIndex;
    };

    Iterator begin();
    Iterator end();

private:
    struct Node {
        std::vector<T> elements;
        Node *next;
        Node() : next(nullptr) {}
    };

    Node *head;
    size_t size;
    static const size_t NODE_SIZE = 10;
};
