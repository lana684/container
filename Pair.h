#pragma once
//#include "Memory_Manager_Table.h"
/*
#include <stdlib.h>
#include "List.h"

class Pair
{
    friend List;
public:
    void* key;
    size_t keySize;
    void* value;
    size_t valueSize;

    Pair(void* k, size_t kSize, void* val, size_t vSize);
    void operator = (const Pair&);     // присваивание
    Pair(const Pair&);                // инициализация
    ~Pair();
};
*/


/*
Pair(void* k, size_t kSize, void* val, size_t vSize)
{
    keySize = kSize; valueSize = vSize;
    void* key = new char[keySize];//_memory.allocMem(keySize);
    memcpy(key, k, keySize);
    void* value = new char[valueSize];  //_memory.allocMem(elemSize);
    memcpy(value, val, valueSize);
}
~Pair()
{
    delete key; delete value;
}
*/