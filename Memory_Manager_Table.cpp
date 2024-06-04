#include "Memory_Manager_Table.h"

Memory_Manager_Table::Memory_Manager_Table(int size) :Mem(size)
{
	max_size = size;
	size_free_space = size;

	//pairs_key_value = (List**)malloc(sizeof(List*) * max_size); //быстрое создание массива списков! //пока неправильно
	//

	pairs_key_value = new List * [max_size];
	Mem* m = new Mem(10000000);  //максимум  коллизий ?
	for (int i = 0; i < max_size; i++)
	{
		pairs_key_value[i] = new List(*m);
	}
	last_added_pair = pairs_key_value[0];
}



Memory_Manager_Table::~Memory_Manager_Table()
{
	delete[] pairs_key_value;
}

void Memory_Manager_Table::rehash()
{

}
















/*
void* Memory_Manager_Table::alloc(size_t hash)
{

	//last_added_pair = pairs_key_value + hash;//*sizeof(List); //??
	last_added_pair = pairs_key_value[hash];
	size_free_space--;
	return last_added_pair;
}

void Memory_Manager_Table::free(void* ptr)
{
	delete[] ptr; //????
}
*/