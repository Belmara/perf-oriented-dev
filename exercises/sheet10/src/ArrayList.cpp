#include "ArrayList.hpp"

template<typename T>
ArrayList<T>::ArrayList(size_t initial_capacity) : capacity(initial_capacity), size(0) {
    data = new T[capacity];
}

template<typename T>
ArrayList<T>::~ArrayList() {
    delete[] data;
}

template<typename T>
void ArrayList<T>::insert(size_t index, const T &value) {
    if (index > size) {
        throw std::out_of_range("Index out of range");
    } else if (index >= capacity) {
        throw std::length_error("Capacity exhausted, no resize implemented");
    }
    for (size_t i = size; i > index; --i) {
        data[i] = data[i - 1];
    }
    data[index] = value;
    ++size;
}

template<typename T>
void ArrayList<T>::remove(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    for (size_t i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    --size;
}

template<typename T>
T &ArrayList<T>::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template<typename T>
size_t ArrayList<T>::get_size() const {
    return size;
}

template<typename T>
size_t ArrayList<T>::get_capacity() const {
    return capacity;
}

template<typename T>
ArrayList<T>::Iterator ArrayList<T>::begin() {
    return Iterator(this, 0);
}

template<typename T>
ArrayList<T>::Iterator ArrayList<T>::end() { return Iterator(this, size); }

template<typename T>
ArrayList<T>::Iterator::Iterator(ArrayList *arrayList, size_t index) : arrayList(arrayList), index(index) {}

template<typename T>
T &ArrayList<T>::Iterator::read() const {
    if (index >= arrayList->size) {
        throw std::out_of_range("Iterator out of range");
    }
    return arrayList->data[index];
}

template<typename T>
void ArrayList<T>::Iterator::write(const T &value) {
    if (index >= arrayList->size) {
        throw std::out_of_range("Iterator out of range");
    }
    arrayList->data[index] = value;
}

template<typename T>
void ArrayList<T>::Iterator::insert(const T &value) {
    arrayList->insert(index, value);
}

template<typename T>
void ArrayList<T>::Iterator::remove() {
    arrayList->remove(index);
    if (index >= arrayList->size) { index = 0; }
}

template<typename T>
bool ArrayList<T>::Iterator::is_end() const {
    return index >= arrayList->size;
}

template<typename T>
void ArrayList<T>::Iterator::next() {
    if (index < arrayList->size - 1) {
        ++index;
    } else {
        index = 0;
    }
}
