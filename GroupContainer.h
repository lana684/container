
#pragma once
#include "Container.h"

// Базовый класс для некоторой группы абстрактных контейнеров
class GroupContainer : public Container
{
	double factor = 0.75;     
	size_t size_free_space = 0;  //сколько еще можно добавить элементов
	size_t max_size = 0;         //максимальный размер массива элементов
public:
	GroupContainer(MemoryManager& mem) : Container(mem) {}

	virtual size_t hash_function(void* key, size_t keySize)
	{
		int hash = 0;
		//char* k = new char[keySize];
		//memcpy((void*)k, key, keySize);
		char* k = (char*)key;
		for (int i = 0; i < keySize; i++)
		{
			hash = (hash << 5) - hash + k[i];
		}
		return hash;
	}

	bool checkMemory()
	{
		return (double)size_free_space / max_size >= factor; 
	}
};

//разрешается менять






/*
#pragma once
#include "Container.h"

// Базовый класс для некоторой группы абстрактных контейнеров
class GroupContainer: public Container
{
public:
	GroupContainer(MemoryManager &mem): Container(mem) {}

	virtual size_t hash_function(void* key, size_t keySize)
	{
		size_t hash = 0;
		//size_t k = reinterpret_cast<size_t>(key);
		size_t k = (size_t)key;
		for (int i = 0; i < keySize; i++)
		{
			hash = (hash << 5) - hash + k;
		}

		return hash;
	}
};
*/

//разрешается менять