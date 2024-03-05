#pragma once
#include "Container.h"

// Базовый класс для некоторой группы абстрактных контейнеров
class GroupContainer: public Container
{
public:
    GroupContainer(MemoryManager &mem): Container(mem) {}

    virtual size_t hash_function(void* key, size_t keySize)
    {
        return 0;
    }
};

//разрешается менять

// message