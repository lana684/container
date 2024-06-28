#pragma once
#include <fstream>
#include <iostream>
#include <string>

#include "Mem.h"
#include "Set.h"

class Test {
private:
    Set* set;

public:
    Test(Set* set) : set(set) {}
    ~Test() { }

    //test for inserting elements
    int testInsert(size_t testCount);

    //test for multiple insertion of identical objects
    int testMultiInsert(void* elem, size_t size);

    //test for searching for objects in a container
    int testFind(size_t testCount);

    //test for inserting identical elements with different types
    int testInsertByType(void* elem1, size_t size1, void* elem2, size_t size2);

    //test for searching for objects of a certain type
    int testFindByType(void* elem, size_t elemSize);

    //test for removing one element
    int testRemove(void* elem, size_t elemSize);

    //test for correctly deleting multiples of 2 and 3 at the same time
    int testСonditionalRemove(size_t testCount);

    //test for removing an element that is pointed to by various iterators
    int testDoubleRemove(void* elem, size_t elemSize);

    //test for empty() and clear()
    //если пустой вернет 0; если не пустой и почистилось 1; если не пустой и не почистилось или произошел сбой 2
    int testEmptyAndClear();

    //test of rehashing
    int testRehash();

    void printToFile(const char* path);


};