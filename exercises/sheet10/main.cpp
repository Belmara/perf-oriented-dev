#include <iostream>
#include <chrono>
#include <cstdlib>
#include "src/UnrolledLinkedList.cpp"
#include "src/TieredArray.cpp"
#include "src/ArrayList.cpp"
#include "src/LinkedList.cpp"

constexpr int singleBenchmarkTimeInSeconds = 1;

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
    bool isInsertTurn = false;
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

void fillUnrolledLinkedList(UnrolledLinkedList<int> &linkedList, size_t numberOfElements) {
    for (int index = 0; index < numberOfElements; index++) {
        linkedList.insert(index);
    }
}


void fillTieredArray(TieredArray<int> &tieredArray, size_t numberOfElements) {
    for (int index = 0; index < numberOfElements; index++) {
        tieredArray.insert(index, index);
    }
}

void benchmarkArrayList(const int numberOfElements, const int percentageInsertDeletes) {
    auto arrayList = ArrayList<int>(numberOfElements + 1);
    fillArrayList(arrayList);

    auto iterator = arrayList.begin();
    auto opsPerSecond = performOperationsWithDistribution(iterator, percentageInsertDeletes);
    std::cout << "Operations per second for ArrayList: " << opsPerSecond << std::endl;
}

void benchmarkLinkedList(const int numberOfElements, const int percentageInsertDeletes) {
    auto linkedList = LinkedList<int>();
    fillLinkedList(linkedList, numberOfElements);

    auto iterator = linkedList.begin();
    auto opsPerSecond = performOperationsWithDistribution(iterator, percentageInsertDeletes);
    std::cout << "Operations per second for LinkedList: " << opsPerSecond << std::endl;
}

void benchmarkUnrolledLinkedList(const int numberOfElements, const int percentageInsertDeletes, const int chunkSize) {
    auto unrolledLinkedList = UnrolledLinkedList<int>(5);
    fillUnrolledLinkedList(unrolledLinkedList, numberOfElements);

    auto iterator = unrolledLinkedList.begin();
    auto opsPerSecond = performOperationsWithDistribution(iterator, percentageInsertDeletes);
    std::cout << "Operations per second for UnrolledLinkedList (chunk size " << chunkSize << "): " << opsPerSecond << std::endl;
}

void benchmarkTieredArray(const int numberOfElements, const int percentageInsertDeletes, const int chunkSize) {
    auto tieredArray = TieredArray<int>(numberOfElements, chunkSize);
    fillTieredArray(tieredArray, numberOfElements);

    auto iterator = tieredArray.begin();
    auto opsPerSecond = performOperationsWithDistribution(iterator, percentageInsertDeletes);
    std::cout << "Operations per second for TieredArray (chunk size " << chunkSize << "): " << opsPerSecond << std::endl;
}


int main(int argc, char *argv[]) {

    //TODO: use elementSize

    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <number_of_elements> <percentage_of_insert_deletes>"
                  << std::endl;
        return 1;
    }

    int numberOfElements = std::atoi(argv[1]);
    int percentageInsertDeletes = std::atoi(argv[2]);


    if (numberOfElements < 0 || percentageInsertDeletes < 0) {
        std::cerr << "All arguments need to be greater than 0" << std::endl;
        return 1;
    }

    if (percentageInsertDeletes > 100) {
        std::cerr << "Percentage of insert and deletes has to be a number between 0 and 100" << std::endl;
        return 1;
    }

    std::cout << std::fixed;

    std::cout << "Benchmark configuration: \nNumber of elements:" << numberOfElements  << "\nInsert/Deletes: " <<
    percentageInsertDeletes << "%\nReads/Writes: " << 100 - percentageInsertDeletes << "%\nTime for each benchmark: " << singleBenchmarkTimeInSeconds << " second/s\n" << std::endl;

    benchmarkArrayList(numberOfElements, percentageInsertDeletes);
    benchmarkLinkedList(numberOfElements, percentageInsertDeletes);

    for(int chunkSize = 2; chunkSize < numberOfElements; chunkSize*=2){
        benchmarkUnrolledLinkedList(numberOfElements, percentageInsertDeletes, chunkSize);
        benchmarkTieredArray(numberOfElements, percentageInsertDeletes, chunkSize);
    }

    return 0;
}
