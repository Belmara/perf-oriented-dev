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
void UnrolledLinkedList<T>::insert(const T &value) {

    Node *current = tail;
    if (current->elements.size() + 1 < nodeCapacity) {
        current->elements.push_back(value);
    } else {
        Node *new_node = new Node(nodeCapacity);
        int j = 0;
        for (int i = current->elements.size() / 2 + 1; i <= current->elements.size(); i++) {
            new_node->elements.insert(new_node->elements.begin() + j, current->elements[i]);
            current->elements.erase(current->elements.begin() + i);
            j++;
        }
        new_node->elements.push_back(value);
        current->next = new_node;
        new_node->prev = current;
        this->tail = new_node;
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
        current->prev->next = current->next;
        current->next->prev = current->prev;
        if (current == tail) {
            tail = current->prev;
        }
        if (current == head) {
            head = current->next;
        }
    }
    delete current;
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
    return this->size;
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
        : unrolledLinkedList(unrolledLinkedList), current(currentNode), elementIndex(elementIndex) {}

template<typename T>
T &UnrolledLinkedList<T>::Iterator::read() const {
    if (current == nullptr || this->elementIndex >= current->elements.size()) {
        throw std::out_of_range("Iterator out of range");
    }
    return current->elements[this->elementIndex];
}

template<typename T>
void UnrolledLinkedList<T>::Iterator::write(const T &value) {
    if (current == nullptr || this->elementIndex >= current->elements.size()) {
        throw std::out_of_range("Iterator out of range (write)");
    }
    this->current->elements[this->elementIndex] = value;
}

template<typename T>
void UnrolledLinkedList<T>::Iterator::insert(const T &value) {
    if (current == nullptr) {
        throw std::out_of_range("Iterator out of range");
    }
    if (current->elements.size() + 1 < this->unrolledLinkedList->nodeCapacity) {
        current->elements.insert(current->elements.begin() + this->elementIndex, value);
    } else {
        Node *new_node = new Node(this->unrolledLinkedList->nodeCapacity);
        int j = 0;

        // move half the values of the current node into the newly created one
        for (int i = current->elements.size() / 2 + 1; i <= current->elements.size(); i++) {
            new_node->elements.insert(new_node->elements.begin() + j, current->elements[i]);
            current->elements.erase(current->elements.begin() + i);
            j++;
        }

        //emplace value
        if (this->elementIndex < current->elements.size()) {
            current->elements.insert(current->elements.begin() + this->elementIndex, value);
        } else {
            auto new_index = this->elementIndex - current->elements.size();
            new_node->elements.insert(new_node->elements.begin() + new_index, value);
            this->elementIndex = new_index;
        }

        // correctly place new node BEFORE current node
        new_node->next = current;
        if (current == this->unrolledLinkedList->head) {
            this->unrolledLinkedList->head = new_node;
            current->prev = new_node;

        } else {
            new_node->next = current;
            new_node->prev = current->prev;
            current->prev = new_node;
            new_node->prev->next = new_node;
        }

    }
    this->unrolledLinkedList->size++;
}

template<typename T>
void UnrolledLinkedList<T>::Iterator::remove() {
    if (current == nullptr || this->elementIndex >= current->elements.size()) {
        throw std::out_of_range("Iterator out of range (remove)");
    }

    current->elements.erase(current->elements.begin() + this->elementIndex);

    if (this->current->elements.empty()) {
        auto to_delete = this->current;
        if (to_delete == this->unrolledLinkedList->head) {
            this->unrolledLinkedList->head = to_delete->next;
            this->unrolledLinkedList->head->prev = NULL;

        } else if (to_delete == this->unrolledLinkedList->tail) {
            this->unrolledLinkedList->tail = to_delete->prev;
            this->unrolledLinkedList->tail->next = NULL;
        } else {
            to_delete->prev->next = to_delete->next;
            to_delete->next->prev = to_delete->prev;
        }
        next();
        delete to_delete;
    }

    this->unrolledLinkedList->size--;
}

template<typename T>
bool UnrolledLinkedList<T>::Iterator::is_end() const {
    return current == nullptr;
}

template<typename T>
void UnrolledLinkedList<T>::Iterator::next() {
    if (current == nullptr) {
        std::cout << "current null\n";
        return;
    }
    if (this->elementIndex + 1 < current->elements.size()) {
        this->elementIndex += 1;
    } else if (current != this->unrolledLinkedList->tail) {
        current = current->next;
        this->elementIndex = 0;
    } else {
        current = unrolledLinkedList->head;
        this->elementIndex = 0;
    }
}
