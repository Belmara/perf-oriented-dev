#include "TieredArray.hpp"

template<typename T>
TieredArray<T>::TieredArray(size_t capacity, size_t chunk_size) : size(0), capacity(capacity), chunkSize(chunk_size) {}

template<typename T>
TieredArray<T>::~TieredArray() = default;

template<typename T>
void TieredArray<T>::insert(size_t index, const T &value) {
    if (size >= capacity) {
        throw std::overflow_error("TieredArray is full");
    }
    if (index > size) {
        throw std::out_of_range("Index out of range");
    }

    size_t chunkIndex = index / chunkSize;
    size_t elementIndex = index % chunkSize;

    if (chunkIndex >= data.size()) {
        data.push_back(std::vector<T>());
    }

    data[chunkIndex].insert(data[chunkIndex].begin() + elementIndex, value);
    ++size;

    // Shift elements in subsequent chunks if necessary
    for (size_t i = chunkIndex; i < data.size() - 1; ++i) {
        if (data[i].size() > chunkSize) {
            T overflow = data[i].back();
            data[i].pop_back();
            data[i + 1].insert(data[i + 1].begin(), overflow);
        }
    }

    if (data.back().size() > chunkSize) {
        T overflow = data.back().back();
        data.back().pop_back();
        data.push_back(std::vector<T>({ overflow }));
    }
}

template<typename T>
void TieredArray<T>::remove(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }

    size_t chunkIndex = index / chunkSize;
    size_t elementIndex = index % chunkSize;

    data[chunkIndex].erase(data[chunkIndex].begin() + elementIndex);
    --size;

    // Shift elements in subsequent chunks if necessary
    for (size_t i = chunkIndex; i < data.size() - 1; ++i) {
        if (!data[i + 1].empty()) {
            T frontElement = data[i + 1].front();
            data[i + 1].erase(data[i + 1].begin());
            data[i].push_back(frontElement);
        }
    }

    if (data.back().empty()) {
        data.pop_back();
    }
}

template<typename T>
T &TieredArray<T>::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }

    size_t chunkIndex = index / chunkSize;
    size_t elementIndex = index % chunkSize;
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
    return tieredArray->data[chunkIndex][elementIndex];
}

template<typename T>
void TieredArray<T>::Iterator::write(const T &value) {
    tieredArray->data[chunkIndex][elementIndex] = value;
}

template<typename T>
void TieredArray<T>::Iterator::insert(const T &value) {
    tieredArray->insert(chunkIndex * tieredArray->chunkSize + elementIndex, value);
    next();
}

template<typename T>
void TieredArray<T>::Iterator::remove() {
    tieredArray->remove(chunkIndex * tieredArray->chunkSize + elementIndex);
    next();
}

template<typename T>
bool TieredArray<T>::Iterator::is_end() const {
    return chunkIndex >= tieredArray->data.size();
}

template<typename T>
void TieredArray<T>::Iterator::next() {
    if(elementIndex + 1 < tieredArray->chunkSize){
        elementIndex++;

    } else if((chunkIndex + 1) * tieredArray->chunkSize < tieredArray->capacity && elementIndex == tieredArray->chunkSize)
    {
        elementIndex = 0;
        chunkIndex ++;
    } else {
        elementIndex = 0;
        chunkIndex = 0;
    }

}