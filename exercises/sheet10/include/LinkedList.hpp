#pragma once

#include <stdexcept>
#include "IteratorBase.hpp"

template<typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node *next;

        explicit Node(const T &data) {}
    };

    Node *head;
    size_t size;

public:
    LinkedList();

    ~LinkedList();

    void insert(size_t index, const T &value);

    void remove(size_t index);

    T &operator[](size_t index);

    size_t get_size() const;

    // Iterator class
    class Iterator : public IteratorBase<T> {
    private:
        LinkedList *linkedList;
        Node *node;
        Node *prev;
    public:
        Iterator(LinkedList *linkedList, Node *node, Node *prev);

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
