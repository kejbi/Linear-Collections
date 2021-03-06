#include <cstddef>
#include <cstdlib>
#include <string>
#include <list>
#include <iostream>
#include <chrono>

#include "Vector.h"
#include "LinkedList.h"
#include "timeperformance.h"

namespace {

    template<typename T>
    using LinearCollection = aisdi::LinkedList<T>;

    void perfomTest() {
        LinearCollection<std::string> collection;
        collection.append("TODO");
    }



} // namespace

int main(int argc, char **argv) {
    std::list<size_t> l;
    const std::size_t repeatCount = argc > 1 ? std::atoll(argv[1]) : 10000;
    for (std::size_t i = 0; i < repeatCount; ++i)
        perfomTest();
    timePerformanceOfAddingMlnElementsLinkedList();
    timePerformanceOfAddingMlnElementsVector();
    timePerformanceOfPrependToMlnElemLinkedList();
    timePerformanceOfPrependToMlnElementsVector();
    timePerformanceOfPlusOperatorLinkedList();
    timePerformanceOfPlusOperatorVector();
    timePerformanceOfErasingRangeMlnElemLinkedList();
    timePerformanceOfErasingRangeMlnElementsVector();
    timePerformanceOfPopFirstMlnElemLinkedList();
    timePerformanceOfPopFirstMlnElementsVector();

    return 0;
}
