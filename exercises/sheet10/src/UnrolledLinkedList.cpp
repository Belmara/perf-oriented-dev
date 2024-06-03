#include "UnrolledLinkedList.hpp"

template<typename T>
UnrolledLinkedList<T>::UnrolledLinkedList() : head(new Node()), size(0) {}

template<typename T>
UnrolledLinkedList<T>::~UnrolledLinkedList() {
    Node *current = head;
    while (current) {
        Node *next = current->next;
        delete current;
        current = next;
    }
}

template<typename T>
void UnrolledLinkedList<T>::insert(size_t index, const T &value) {
    if (index > size) {
        throw std::out_of_range("Index out of range");
    }
    Node *current = head;
    size_t pos = index;
    while (pos >= current->elements.size()) {
        pos -= current->elements.size();
        current = current->next;
    }

    current->elements.insert(current->elements.begin() + pos, value);
    if (current->elements.size() > NODE_SIZE) {
        Node *new_node = new Node();
        new_node->elements.assign(current->elements.begin() + NODE_SIZE / 2, current->elements.end());
        current->elements.erase(current->elements.begin() + NODE_SIZE / 2, current->elements.end());
        new_node->next = current->next;
        current->next = new_node;
    }
    ++size;
}

template<typename T>
void UnrolledLinkedList<T>::remove(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    Node *current = head;
    size_t pos = index;
    while (pos >= current->elements.size()) {
        pos -= current->elements.size();
        current = current->next;
    }

    current->elements.erase(current->elements.begin() + pos);
    if (current->elements.empty() && current != head) {
        Node *prev = head;
        while (prev->next != current) {
            prev = prev->next;
        }
        prev->next = current->next;
        delete current;
    }
    --size;
}

template<typename T>
T& UnrolledLinkedList<T>::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    Node *current = head;
    size_t pos = index;
    while (pos >= current->elements.size()) {
        pos -= current->elements.size();
        current = current->next;
    }
    return current->elements[pos];
}

template<typename T>
size_t UnrolledLinkedList<T>::get_size() const {
    return size;
}

template<typename T>
typename UnrolledLinkedList<T>::Iterator UnrolledLinkedList<T>::begin() {
    return new Iterator(this, 0, 0);
}

template<typename T>
typename UnrolledLinkedList<T>::Iterator UnrolledLinkedList<T>::end() {
    return new Iterator(this, size, 0);
}

template<typename T>
UnrolledLinkedList<T>::Iterator::Iterator(UnrolledLinkedList *unrolledLinkedList, size_t nodeIndex, size_t elementIndex)
        : unrolledLinkedList(unrolledLinkedList), nodeIndex(nodeIndex), elementIndex(elementIndex) {}

template<typename T>
T &UnrolledLinkedList<T>::Iterator::read() const {
    if (nodeIndex >= unrolledLinkedList->size) {
        throw std::out_of_range("Iterator out of range");
    }
    return (*unrolledLinkedList)[nodeIndex];
}

template<typename T>
void UnrolledLinkedList<T>::Iterator::write(const T &value) {
    if (nodeIndex >= unrolledLinkedList->size) {
        throw std::out_of_range("Iterator out of range");
    }
    (*unrolledLinkedList)[nodeIndex] = value;
}

template<typename T>
void UnrolledLinkedList<T>::Iterator::insert(const T &value) {
    unrolledLinkedList->insert(nodeIndex, value);
    ++nodeIndex;
}

template<typename T>
void UnrolledLinkedList<T>::Iterator::remove() {
    unrolledLinkedList->remove(nodeIndex);
    if (nodeIndex >= unrolledLinkedList->size) {
        nodeIndex = unrolledLinkedList->size;
    }
}

template<typename T>
bool UnrolledLinkedList<T>::Iterator::is_end() const {
    return nodeIndex >= unrolledLinkedList->size;
}

template<typename T>
void UnrolledLinkedList<T>::Iterator::next() {
    ++nodeIndex;
}