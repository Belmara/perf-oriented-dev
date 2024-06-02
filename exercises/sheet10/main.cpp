#include <iostream>
#include <vector>
#include <chrono>
#include <list>
#include "src/UnrolledLinkedList.cpp"
#include "src/TieredArray.cpp"


void benchmark(int n, int chunkSize) {
    // Benchmark unrolled linked list
    UnrolledLinkedList<int> unrolledList(chunkSize);
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; ++i) {
        unrolledList.insert(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Unrolled Linked List (chunk size " << chunkSize << ") insert time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n / 2; ++i) {
        unrolledList.remove(i);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Unrolled Linked List (chunk size " << chunkSize << ") remove time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

    TieredArray<int> tieredArray(chunkSize);
    // Benchmark standard linked list
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < n; ++i) {
        tieredArray.insert(i);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Tiered Array insert time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < n / 2; ++i) {
        tieredArray.remove(i);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Tiered Array remove time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
    std::list<int> linkedList;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; ++i) {
        linkedList.push_back(i);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Standard Linked List insert time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n / 2; ++i) {
        auto it = std::next(linkedList.begin(), i);
        linkedList.erase(it);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Standard Linked List remove time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

    // Benchmark vector (dynamic array)
    std::vector<int> arrayList;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; ++i) {
        arrayList.push_back(i);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Vector insert time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n / 2; ++i) {
        arrayList.erase(arrayList.begin() + i);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Vector remove time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
}

int main() {
    int n = 10000;
    int chunkSizes[] = {4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192};

    for (int chunkSize : chunkSizes) {
        benchmark(n, chunkSize);
    }

    return 0;
}
