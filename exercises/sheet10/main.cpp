#pragma once

#include <iostream>
#include <chrono>
#include <cstdlib>
#include "src/UnrolledLinkedList.cpp"
#include "src/TieredArray.cpp"
#include "src/ArrayList.cpp"
#include "src/LinkedList.cpp"

constexpr int singleBenchmarkTimeInSeconds = 10;

int greatestCommonDivisor(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

float performOperationsWithDistribution(IteratorBase<int> &iterator, const int percentageInsertDeletes) {
    int insDel = percentageInsertDeletes;
    int readWrite = 100 - insDel;
    int gcd = greatestCommonDivisor(insDel, readWrite);

    int rwPerInsDel = readWrite / gcd;
    int insDelPerRw = insDel / gcd;

    bool isReadTurn = true;
    bool isInsertTurn = true;
    int operations = 0;

    int currentInsertDeletes = 0;
    int currentReadWrites = 0;

    auto startTime = std::chrono::high_resolution_clock::now();

    //we use this element to accumulate read values and use it to insert and write, such that the actual data inside
    //the container changes and the compiler doesn't perform optimizations
    int runningElement = 0;

    while (true) {
        // insert/delete branch
        if (currentInsertDeletes < insDelPerRw || rwPerInsDel == 0) {
            if (isInsertTurn) {
                iterator.insert(runningElement);
            } else {
                iterator.remove();
            }
            isInsertTurn = !isInsertTurn;
            currentInsertDeletes++;
            if (currentInsertDeletes == insDelPerRw) {
                currentReadWrites = 0;
            }
        }

            // read/write branch
        else if (currentReadWrites < rwPerInsDel || insDelPerRw == 0) {
            if (isReadTurn) {
                runningElement += iterator.read();
            } else {
                iterator.write(runningElement);
            }
            isReadTurn = !isReadTurn;
            currentReadWrites++;
            if (currentReadWrites == rwPerInsDel) {
                currentInsertDeletes = 0;
            }
        }

        operations++;

        if (std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::high_resolution_clock::now() - startTime).count() >= singleBenchmarkTimeInSeconds) {
            break;
        }

        iterator.next();
    }

    return static_cast<float>(operations) / singleBenchmarkTimeInSeconds;
}

void fillArrayList(ArrayList<int> &arrayList) {
    int index = 0;
    //we need at least one more space for our operations
    while (arrayList.get_size() < arrayList.get_capacity() - 1) {
        arrayList.insert(index, index);
        index++;
    }
}

void fillLinkedList(LinkedList<int> &linkedList, size_t numberOfElements) {
    for (int index = 0; index < numberOfElements; index++) {
        linkedList.insert(index, index);
    }
}

void benchmark(const int numberOfElements, const int elementSize, const int percentageInsertDeletes) {

    //TODO: use elementSize
    //TODO: refactor to only do one container type at a time, such that not all containers must be initialized at the same time
    //TODO: find bug in destruction of the linkedList, since it takes forever...

    //initialize all datastructures
    auto arrayList = ArrayList<int>(numberOfElements + 1);
    fillArrayList(arrayList);


    /*auto linkedList = LinkedList<int>();
    fillLinkedList(linkedList, numberOfElements);*/

    auto arrayListIterator = arrayList.begin();
    //auto linkedListIterator = linkedList.begin();

    //benchmark all datastructures
    auto arrayListOpsPerSecond = performOperationsWithDistribution(arrayListIterator, percentageInsertDeletes);
    std::cout << "Operations per second for ArrayList: " << arrayListOpsPerSecond << std::endl;

    //benchmark all datastructures
    /*auto linkedListOpsPerSecond = performOperationsWithDistribution(linkedListIterator, percentageInsertDeletes);
    std::cout << "Operations per second for LinkedList: " << linkedListOpsPerSecond << std::endl;*/
}

int main(int argc, char *argv[]) {

    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <number_of_elements> <element_size> <percentage_of_insert_deletes>"
                  << std::endl;
        return 1;
    }

    int numberOfElements = std::atoi(argv[1]);
    int elementSize = std::atoi(argv[2]);
    int percentageInsertDeletes = std::atoi(argv[3]);


    if (numberOfElements < 0 || elementSize < 0 || percentageInsertDeletes < 0) {
        std::cerr << "All arguments need to be greater than 0" << std::endl;
        return 1;
    }

    if (percentageInsertDeletes > 100) {
        std::cerr << "Percentage of insert and deletes has to be a number between 0 and 100" << std::endl;
        return 1;
    }

    benchmark(numberOfElements, elementSize, percentageInsertDeletes);

    return 0;
}
