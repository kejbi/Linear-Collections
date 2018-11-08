//
// Created by kejbi on 08.11.18.
//

#ifndef LINEAR_TIMEPERFORMANCE_H
#define LINEAR_TIMEPERFORMANCE_H

#include <chrono>
#include <iostream>
#include "LinkedList.h"
#include "Vector.h"
aisdi::LinkedList<int> makeMillionElementsList(){
    aisdi::LinkedList<int> l;
    for(int i=0;i<1000000;i++){
        l.append(i);
    }
    return l;
}
aisdi::Vector<int> makeMillionElementsVector(){
    aisdi::Vector<int> l;
    for(int i=0;i<1000000;i++){
        l.append(i);
    }
    return l;
}
void timePerformanceOfAddingMlnElementsLinkedList(){

    auto start = std::chrono::system_clock::now();
    aisdi::LinkedList<int> l = makeMillionElementsList();
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout<<"Adding million elements to linked list with time: "<<elapsed_seconds.count()<<std::endl;
}
void timePerformanceOfAddingMlnElementsVector(){
    auto start = std::chrono::system_clock::now();
    aisdi::Vector<int> l = makeMillionElementsVector();
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout<<"Adding million elements to vector with time: "<<elapsed_seconds.count()<<std::endl;
}
void timePerformanceOfPrependToMlnElemLinkedList(){
    aisdi::LinkedList<int> l = makeMillionElementsList();
    auto start = std::chrono::system_clock::now();
    l.prepend(1);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout<<"Prepending to million elements linked list with time: "<<elapsed_seconds.count()<<std::endl;
}
void timePerformanceOfPrependToMlnElementsVector(){
    aisdi::Vector<int> l = makeMillionElementsVector();
    auto start = std::chrono::system_clock::now();
    l.prepend(1);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout<<"Prepending to million elements vector with time: "<<elapsed_seconds.count()<<std::endl;
}
void timePerformanceOfPlusOperatorLinkedList(){
    aisdi::LinkedList<int> l = makeMillionElementsList();
    auto it = l.cbegin();
    auto start = std::chrono::system_clock::now();
    it+546758;
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout<<"Plus operation on Iterator million elements linked list with time: "<<elapsed_seconds.count()<<std::endl;
}
void timePerformanceOfPlusOperatorVector(){
    aisdi::Vector<int> l = makeMillionElementsVector();
    auto it = l.cbegin();
    auto start = std::chrono::system_clock::now();
    it+546758;
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout<<"Plus operator on iterator million elements vector with time: "<<elapsed_seconds.count()<<std::endl;
}
void timePerformanceOfErasingRangeMlnElemLinkedList(){
    aisdi::LinkedList<int> l = makeMillionElementsList();
    auto it = l.cbegin()+12765;
    auto itend = l.cbegin()+575900;
    auto start = std::chrono::system_clock::now();
    l.erase(it,itend);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout<<"Erasing a few elements of million elements linked list with time: "<<elapsed_seconds.count()<<std::endl;
}
void timePerformanceOfErasingRangeMlnElementsVector(){
    aisdi::Vector<int> l = makeMillionElementsVector();
    auto it = l.cbegin()+12765;
    auto itend = l.cbegin()+575900;
    auto start = std::chrono::system_clock::now();
    l.erase(it,itend);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout<<"Erasing a few elements of million elements vector with time: "<<elapsed_seconds.count()<<std::endl;
}
void timePerformanceOfPopFirstMlnElemLinkedList(){
    aisdi::LinkedList<int> l = makeMillionElementsList();
    auto start = std::chrono::system_clock::now();
    l.popFirst();
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout<<"Pop first of million elements linked list with time: "<<elapsed_seconds.count()<<std::endl;
}
void timePerformanceOfPopFirstMlnElementsVector() {
    aisdi::Vector<int> l = makeMillionElementsVector();
    auto start = std::chrono::system_clock::now();
    l.popFirst();
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Pop first of million elements vector with time: " << elapsed_seconds.count() << std::endl;
}


#endif //LINEAR_TIMEPERFORMANCE_H
