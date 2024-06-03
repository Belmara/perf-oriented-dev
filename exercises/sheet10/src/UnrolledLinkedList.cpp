#pragma once
#include "../include/UnrolledLinkedList.hpp"

template<typename T>
UnrolledLinkedList<T>::Node::Node(int chunkSize) : elements(), next(nullptr) {
    elements.reserve(chunkSize);
}

template<typename T>
UnrolledLinkedList<T>::UnrolledLinkedList(int chunkSize) : head(nullptr), tail(nullptr), chunkSize(chunkSize), size(0) {}

template<typename T>
void UnrolledLinkedList<T>::insert(const T& value) {
    if (!head) {
        head = new Node(chunkSize);
        tail = head;
    }

    if (tail->elements.size() >= chunkSize) {
        Node* newNode = new Node(chunkSize);
        tail->next = newNode;
        tail = newNode;
    }

    tail->elements.push_back(value);
    size++;
}

template<typename T>
T UnrolledLinkedList<T>::get(int index) {
    if (index < 0 || index >= size) throw std::out_of_range("Index out of range");

    Node* current = head;
    while (current && index >= current->elements.size()) {
        index -= current->elements.size();
        current = current->next;
    }

    return current->elements[index];
}

template<typename T>
void UnrolledLinkedList<T>::remove(int index) {
    if (index < 0 || index >= size) throw std::out_of_range("Index out of range");

    Node* current = head;
    Node* prev = nullptr;

    while (current && index >= current->elements.size()) {
        index -= current->elements.size();
        prev = current;
        current = current->next;
    }

    current->elements.erase(current->elements.begin() + index);
    size--;

    // Maintain the structure
    while (current && current->next && current->elements.size() < chunkSize && current->next->elements.size() > 0) {
        current->elements.push_back(current->next->elements.front());
        current->next->elements.erase(current->next->elements.begin());

        if (current->next->elements.empty() && current->next->next) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }

        current = current->next;
    }

    if (head && head->elements.empty()) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

template<typename T>
UnrolledLinkedList<T>::~UnrolledLinkedList() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}
