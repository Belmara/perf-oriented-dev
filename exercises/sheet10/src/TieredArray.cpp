#include "TieredArray.hpp"

template<typename T>
TieredArray<T>::TieredArray() : size(0) {}

template<typename T>
TieredArray<T>::~TieredArray() {
    data.clear();
}

template<typename T>
void TieredArray<T>::insert(size_t index, const T &value) {
    if (index > size) {
        throw std::out_of_range("Index out of range");
    }
    size_t chunkIndex = index / CHUNK_SIZE;
    size_t elementIndex = index % CHUNK_SIZE;

    if (chunkIndex >= data.size()) {
        data.resize(chunkIndex + 1);
    }

    if (data[chunkIndex].size() >= CHUNK_SIZE) {
        data.insert(data.begin() + chunkIndex + 1, std::vector<T>());
        data[chunkIndex + 1].push_back(data[chunkIndex].back());
        data[chunkIndex].pop_back();
    }

    data[chunkIndex].insert(data[chunkIndex].begin() + elementIndex, value);
    ++size;
}

template<typename T>
void TieredArray<T>::remove(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    size_t chunkIndex = index / CHUNK_SIZE;
    size_t elementIndex = index % CHUNK_SIZE;

    data[chunkIndex].erase(data[chunkIndex].begin() + elementIndex);
    if (data[chunkIndex].empty()) {
        data.erase(data.begin() + chunkIndex);
    }
    --size;
}

template<typename T>
T &TieredArray<T>::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    size_t chunkIndex = index / CHUNK_SIZE;
    size_t elementIndex = index % CHUNK_SIZE;
    return data[chunkIndex][elementIndex];
}

template<typename T>
size_t TieredArray<T>::get_size() const {
    return size;
}

template<typename T>
typename TieredArray<T>::Iterator TieredArray<T>::begin() {
    return Iterator(this, 0, 0);
}

template<typename T>
typename TieredArray<T>::Iterator TieredArray<T>::end() {
    return Iterator(this, data.size(), 0);
}

template<typename T>
TieredArray<T>::Iterator::Iterator(TieredArray *tieredArray, size_t chunkIndex, size_t elementIndex)
        : tieredArray(tieredArray), chunkIndex(chunkIndex), elementIndex(elementIndex) {}

template<typename T>
T &TieredArray<T>::Iterator::read() const {
    if (chunkIndex >= tieredArray->data.size() || elementIndex >= tieredArray->data[chunkIndex].size()) {
        throw std::out_of_range("Iterator out of range");
    }
    return tieredArray->data[chunkIndex][elementIndex];
}

template<typename T>
void TieredArray<T>::Iterator::write(const T &value) {
    if (chunkIndex >= tieredArray->data.size() || elementIndex >= tieredArray->data[chunkIndex].size()) {
        throw std::out_of_range("Iterator out of range");
    }
    tieredArray->data[chunkIndex][elementIndex] = value;
}

template<typename T>
void TieredArray<T>::Iterator::insert(const T &value) {
    tieredArray->insert(chunkIndex * TieredArray::CHUNK_SIZE + elementIndex, value);
    ++elementIndex;
    if (elementIndex >= TieredArray::CHUNK_SIZE) {
        elementIndex = 0;
        ++chunkIndex;
    }
}

template<typename T>
void TieredArray<T>::Iterator::remove() {
    tieredArray->remove(chunkIndex * TieredArray::CHUNK_SIZE + elementIndex);
    if (elementIndex >= tieredArray->data[chunkIndex].size()) {
        elementIndex = 0;
        ++chunkIndex;
    }
}

template<typename T>
bool TieredArray<T>::Iterator::is_end() const {
    return chunkIndex >= tieredArray->data.size();
}

template<typename T>
void TieredArray<T>::Iterator::next() {
    ++elementIndex;
    if (elementIndex >= tieredArray->data[chunkIndex].size()) {
        elementIndex = 0;
        ++chunkIndex;
    }
}