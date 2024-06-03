#include "UnrolledLinkedList.hpp"

template<typename T>
UnrolledLinkedList<T>::UnrolledLinkedList(size_t capacity)
        : head(new Node(capacity)), tail(head), nodeCapacity(capacity), size(0) {}

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
    //TODO: algorithm not correct yet, last node looks really weird, seems like the splitting doesnt work correctly
    if (index > size) {
        throw std::out_of_range("Index out of range");
    }
    Node *current = head;
    size_t pos = index;
    while (pos >= this->nodeCapacity) {
        pos -= this->nodeCapacity;
        if (current->next == nullptr) {
            Node *new_node = new Node(nodeCapacity);
            new_node->elements.assign(current->elements.begin() + nodeCapacity / 2, current->elements.end());
            current->elements.erase(current->elements.begin() + nodeCapacity / 2, current->elements.end());
            new_node->next = current->next;
            current->next = new_node;
            if (current == tail) {
                this->tail = new_node;
            }
        }
        current = current->next;
    }
    current->elements.insert(current->elements.begin() + pos, value);
    ++size;

    /*
      if (index > size) {
        throw std::out_of_range("Index out of range");
    }
    Node* current = head;
    size_t pos = index;
    while (pos >= current->elements.size()) {
        pos -= current->elements.size();
        current = current->next;
    }

    current->elements.insert(current->elements.begin() + pos, value);
    if (current->elements.size() > nodeCapacity) {
        Node* new_node = new Node(nodeCapacity);
        new_node->elements.assign(current->elements.begin() + nodeCapacity / 2, current->elements.end());
        current->elements.erase(current->elements.begin() + nodeCapacity / 2, current->elements.end());
        new_node->next = current->next;
        current->next = new_node;
        if (current == tail) {
            tail = new_node;
        }
    }
    ++size;
     * */
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
        if (current == tail) {
            tail = prev;
        }
    }
    --size;
}

template<typename T>
T &UnrolledLinkedList<T>::operator[](size_t index) {
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
    return Iterator(this, head, 0);
}

template<typename T>
typename UnrolledLinkedList<T>::Iterator UnrolledLinkedList<T>::end() {
    return Iterator(this, nullptr, 0);
}

template<typename T>
UnrolledLinkedList<T>::Iterator::Iterator(UnrolledLinkedList *unrolledLinkedList, Node *currentNode,
                                          size_t elementIndex)
        : unrolledLinkedList(unrolledLinkedList), currentNode(currentNode), elementIndex(elementIndex) {}

template<typename T>
T &UnrolledLinkedList<T>::Iterator::read() const {
    if (currentNode == nullptr || elementIndex >= currentNode->elements.size()) {
        throw std::out_of_range("Iterator out of range");
    }
    return currentNode->elements[elementIndex];
}

template<typename T>
void UnrolledLinkedList<T>::Iterator::write(const T &value) {
    if (currentNode == nullptr || elementIndex >= currentNode->elements.size()) {
        throw std::out_of_range("Iterator out of range");
    }
    currentNode->elements[elementIndex] = value;
}

template<typename T>
void UnrolledLinkedList<T>::Iterator::insert(const T &value) {
    if (currentNode == nullptr) {
        throw std::out_of_range("Iterator out of range");
    }
    unrolledLinkedList->insert(elementIndex, value);
    if (currentNode->elements.size() > unrolledLinkedList->nodeCapacity) {
        next();
    }
}

template<typename T>
void UnrolledLinkedList<T>::Iterator::remove() {
    if (currentNode == nullptr || elementIndex >= currentNode->elements.size()) {
        throw std::out_of_range("Iterator out of range");
    }
    unrolledLinkedList->remove(elementIndex);
    if (currentNode->elements.empty() && currentNode != unrolledLinkedList->head) {
        currentNode = currentNode->next;
        elementIndex = 0;
    }
}

template<typename T>
bool UnrolledLinkedList<T>::Iterator::is_end() const {
    return currentNode == nullptr;
}

template<typename T>
void UnrolledLinkedList<T>::Iterator::next() {
    if (currentNode == nullptr) {
        return;
    }
    std::cout << "Current Node: " << currentNode << ", Element Index: " << elementIndex << std::endl;
    if (elementIndex + 1 < currentNode->elements.size()) {
        this->elementIndex += 1;
    } else if (currentNode->next != nullptr) {
        currentNode = currentNode->next;
        elementIndex = 0;
    } else {
        currentNode = unrolledLinkedList->head;
        elementIndex = 0;
    }
    std::cout << "After Next - Current Node: " << currentNode << ", Element Index: " << elementIndex << std::endl;
}
