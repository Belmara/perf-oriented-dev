#pragma once
#include <stdexcept>
#include <vector>

template<typename T>
class UnrolledLinkedList {
private:
    struct Node {
        std::vector<T> elements;
        Node* next;

        Node(int chunkSize);
    };

    Node* head;
    Node* tail;
    int chunkSize;
    int size;

public:
    UnrolledLinkedList(int chunkSize);
    void insert(const T& value);
    T get(int index);
    void remove(int index);
    ~UnrolledLinkedList();
};

