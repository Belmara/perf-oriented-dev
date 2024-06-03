#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>
#include "IteratorBase.hpp"

template<typename T>
class UnrolledLinkedList {
    struct Node {
        std::vector<T> elements;
        Node *next;

        Node(size_t capacity) : elements(), next(nullptr) {
            elements.reserve(capacity);
        }
    };

    Node *head;
    Node *tail;
    size_t nodeCapacity;
    size_t size;

public:
    UnrolledLinkedList(size_t capacity = 4);

    ~UnrolledLinkedList();

    void insert(size_t index, const T &value);

    void remove(size_t index);

    T &operator[](size_t index);

    size_t get_size() const;

    class Iterator : public IteratorBase<T> {
        UnrolledLinkedList *unrolledLinkedList;
        Node *currentNode;
        size_t elementIndex;

    public:
        Iterator(UnrolledLinkedList *unrolledLinkedList, Node *currentNode, size_t elementIndex);

        T &read() const override;

        void write(const T &value) override;

        void insert(const T &value) override;

        void remove() override;

        bool is_end() const override;

        void next() override;

        T &operator*() { return read(); }

        Iterator &operator++() {
            next();
            return *this;
        }

        bool operator!=(const Iterator &other) const {
            return !is_end() && (currentNode != other.currentNode || elementIndex != other.elementIndex);
        }
    };

    Iterator begin();

    Iterator end();
};

