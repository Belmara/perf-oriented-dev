#pragma once

#include "LinkedList.hpp"

template<typename T>
LinkedList<T>::LinkedList() : head(nullptr), size(0) {}

template<typename T>
LinkedList<T>::~LinkedList() {
    while (head) {
        Node *tmp = head;
        head = head->next;
        delete tmp;
    }
}

template<typename T>
void LinkedList<T>::insert(size_t index, const T &value) {
    if (index > size) {
        throw std::out_of_range("Index out of range");
    }
    Node *new_node = new Node(value);
    if (index == 0) {
        new_node->next = head;
        head = new_node;
    } else {
        Node *prev = head;
        for (size_t i = 0; i < index - 1; ++i) {
            prev = prev->next;
        }
        new_node->next = prev->next;
        prev->next = new_node;
    }
    ++size;
}

template<typename T>
void LinkedList<T>::remove(size_t index) {
    if (index >= size) throw std::out_of_range("Index out of range");
    Node *to_delete;
    if (index == 0) {
        to_delete = head;
        head = head->next;
    } else {
        Node *prev = head;
        for (size_t i = 0; i < index - 1; ++i) {
            prev = prev->next;
        }
        to_delete = prev->next;
        prev->next = to_delete->next;
    }
    delete to_delete;
    --size;
}

template<typename T>
T &LinkedList<T>::operator[](size_t index) {
    if (index >= size) throw std::out_of_range("Index out of range");
    Node *current = head;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->data;
}

template<typename T>
size_t LinkedList<T>::get_size() const {
    return size;
}

template<typename T>
LinkedList<T>::Iterator LinkedList<T>::begin() { return Iterator(this, head, nullptr); }

template<typename T>
LinkedList<T>::Iterator LinkedList<T>::end() { return Iterator(this, nullptr, nullptr); }

template<typename T>
LinkedList<T>::Iterator::Iterator(LinkedList *linkedList, Node *node, Node *prev) : linkedList(linkedList), node(node),
                                                                                    prev(prev) {}

template<typename T>
T &LinkedList<T>::Iterator::read() const {
    if (!node) {
        throw std::out_of_range("Iterator out of range");
    }
    return node->data;
}

template<typename T>
void LinkedList<T>::Iterator::write(const T &value) {
    if (!node) {
        throw std::out_of_range("Iterator out of range");
    }
    node->data = value;
}

template<typename T>
void LinkedList<T>::Iterator::insert(const T &value) {
    if (!prev) { // Insert at head
        linkedList->head = new Node(value);
        linkedList->head->next = node;
        prev = linkedList->head;
    } else {
        Node *new_node = new Node(value);
        new_node->next = node;
        prev->next = new_node;
        prev = new_node;
    }
    ++linkedList->size;
}

template<typename T>
void LinkedList<T>::Iterator::remove() {
    if (!node) {
        throw std::out_of_range("Iterator out of range");
    }
    Node *to_delete = node;
    if (!prev) { // Erase head
        linkedList->head = node->next;
    } else {
        prev->next = node->next;
    }
    node = node->next;
    delete to_delete;
    --linkedList->size;
}

template<typename T>
bool LinkedList<T>::Iterator::is_end() const {
    return node == nullptr;
}

template<typename T>
void LinkedList<T>::Iterator::next() {
    if (node) {
        prev = node;
        if (node->next) {
            node = node->next;
        } else {
            //wrap around
            node = linkedList->head;
        }

    }
}
