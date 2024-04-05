#pragma once
#include "Container.h"

// Базовый класс для некоторой группы абстрактных контейнеров
class GroupContainer: public Container
{
public:
    GroupContainer(MemoryManager &mem): Container(mem) {}

	virtual size_t hash_function(void* key, size_t keySize)
	{
		int hash = 0;
		char* k = (char*)key;
		for (int i = 0; i < keySize; i++)
		{
			hash = (hash << 5) - hash + k[i];
		}
		return hash;
	}
};

//разрешается менять