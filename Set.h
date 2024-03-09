#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include "Mem.h"
#include "SetAbstract.h"

using namespace std;

class Set :public AbstractSet {
    int set_size;
    size_t bytes_size;
    int hash_size;
    list<int> list_arr[];
    public:
    Set(MemoryManager &mem) :AbstractSet(mem) {}

    class Iterator: public Container::Iterator
    {
        void* getElement(size_t& size);
        // Возвращает true, если есть следующий элемент, иначе false.
        bool hasNext();
        // Переход к следующему элементу.
        void goToNext();
        // проверка на равенство итераторов
        bool equals(Container::Iterator* right);
    };

    int size() override;
    size_t max_bytes() override;
    Container::Iterator* find(void *elem, size_t size) override;
    Container::Iterator* newIterator() override;
    void remove(Container::Iterator *iter) override;
    void clear() override;
    bool empty() override;

    int insert(void *elem, size_t size) override;

    // вынести в общий
    size_t hash_function(void* key, size_t keySize);

    int get_hash_size();
};