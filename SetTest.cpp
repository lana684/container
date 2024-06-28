#pragma once
#include <fstream>
#include <iostream>
#include <string>

#include "Test.h"

using namespace std;



int Test::testInsert(size_t testCount)
{
	cout << "Test Insert:" << endl;
	int x = 0, index = 0;
	for (int i = 0; i < testCount; i++)
	{
		x = i;
		this->set->insert(&x, sizeof(x));
	}
	this->printToFile("SetPrint.txt");
	return 0;
}

int Test::testMultiInsert(void* elem, size_t size)
{
	this->set->clear();
	if (this->set->empty())
	{
		for (int i = 0; i <= 100; i++)
		{
			this->set->insert(elem, size);
		}
		//пройтись итератором или найти
		if (this->set->size() == 1)
			return 0;
	}
	return 1;
}

int Test::testInsertByType(void* elem1, size_t size1, void* elem2, size_t size2)
{
	// проверить разный хэш
	this->set->insert(elem1, size1);
	this->set->insert(elem2, size2);
	Container::Iterator* iter1 = this->set->find(elem1, size1);
	Container::Iterator* iter2 = this->set->find(elem2, size2);
	if (!iter1->equals(iter2))
		return 0;
	return 1;
}

int Test::testFind(size_t testCount)
{
	size_t count = 0;
	for (int i = 0; i < testCount; i++)
	{
		if (this->set->find(&i, sizeof(i)))
		{
			count++;
			std::cout << i << ' ';
		}
	}
	if (count == testCount)
		return 0;
	return 1;
}//нафиг

int Test::testFindByType(void* elem, size_t elemSize)
{
	size_t fakeSize = elemSize - 1;
	this->set->insert(elem, elemSize);
	Container::Iterator* iter1 = this->set->find(elem, fakeSize);
	Container::Iterator* iter2 = this->set->find(elem, elemSize);
	if(iter1 == nullptr && iter2)
		return 0;
	return 1;
}

int Test::testRemove(void* elem, size_t elemSize)
{
	this->set->insert(elem, elemSize);
	Container::Iterator* iter = this->set->find(elem, elemSize);
	this->set->remove(iter);
	iter = this->set->find(elem, elemSize);
	if (!iter)
		return 0;
	return 1;

}

int Test::testСonditionalRemove(size_t testCount)
{
	Container::Iterator* iter = nullptr;
	size_t count = 0;
	for (int i = 0; i < testCount; i++)
	{
		if ((i % 2 == 0) || (i % 3 == 0))
		{
			iter = this->set->find(&i, sizeof(i));
			count++;
			this->set->remove(iter);
			if (!this->set->find(&i, sizeof(i)))
				count--;
		}
	}
	if (count == 0)
		return 0;
	return 1;
}

int Test::testDoubleRemove(void* elem, size_t elemSize)
{
	Container::Iterator* iter1 = nullptr, * iter2 = nullptr;
	size_t startSize = this->set->size(), finalSize = 0;
	iter1 = this->set->find(elem, elemSize);
	iter2 = this->set->find(elem, elemSize);
	this->set->remove(iter1);
	this->set->remove(iter2);
	finalSize = this->set->size();
	if(startSize - finalSize == 1)
		return 0;
	return 1;
}

int Test::testEmptyAndClear()
{
	if (this->set->empty())
		return 0;
	else
	{
		this->set->clear();
		if (this->set->empty())
			return 1;
	}
	return 2;
}

int Test::testRehash()
{
	return 0;
}

void Test::printToFile(const char* path)
{
	ofstream fout;
	fout.open(path);
	Set::Iterator* iter = (Set::Iterator*)this->set->newIterator();
	int* elem = nullptr;
	size_t size = 0;
	while (iter)
	{
		elem = (int*)iter->getElement(size);
		fout << *elem << " ";
		if (iter->hasNext())
			iter->goToNext();
		else
		{
			delete iter;
			iter = nullptr;
		}
	}
	fout.close();

}