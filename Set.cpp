#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include "MemoryManager.h"
#include "Mem.h"
#include "Set.h"

    void* Set::Iterator::getElement (size_t &size)
    {

        return NULL;
    }
    // Возвращает true, если есть следующий элемент, иначе false.
    bool Set::Iterator::hasNext()
    {
        return true;
    }
    // Переход к следующему элементу.
    void Set::Iterator::goToNext()
    {}
    // проверка на равенство итераторов
    bool Set::Iterator::equals(Container::Iterator* right)
    {
        return true;
    }

    int Set::size(){
        return this->set_size;
    }
    size_t Set::max_bytes(){
        return this->bytes_size;
    }
    Container::Iterator* Set::find(void *elem, size_t size)
    {
        return 0;
    }
    Container::Iterator* Set::newIterator()
    {
        return 0;
    }
    void Set::remove(Container::Iterator *iter)
    {

    }
    //приведение типов
    void Set::clear()
    {
    }
    bool Set::empty()
    {
        if (this->bytes_size == 0 && this->set_size == 0)
        {
            return true;
        }
        else {
            return false;
        }
    }

    int Set::insert(void *elem, size_t size)
    {
        return 0;
    }

    size_t Set::hash_function(void* key, size_t keySize)
    {
        size_t h = 0;
        return h;
    }

    int Set::get_hash_size() {
        return 0;
    }


