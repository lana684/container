#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include "Test.h"

using namespace std;

clock_t start, end_time;


int Test::testInsert(size_t testCount)
{
	cout << "Test Insert:" << endl << "Test value = " << testCount << endl;
	int x = 0, index = 0;
	Set::Iterator* iter = nullptr;
	start = clock();
	for (int i = 0; i < testCount; i++)
	{
		x = i;
		this->set->insert(&x, sizeof(x));
	}
	end_time = clock();
	printf("Work time %.4f second(s)\n", ((double)end_time - start) / ((double)CLOCKS_PER_SEC));
	//this->printToFile("SetPrint.txt");
	start = clock();
	for (int i = 0; i < testCount; i++)
	{
		x = i;
		iter = (Set::Iterator*)set->find(&x, sizeof(x));
		if (!iter)
		{
			cout << "Elem not found" << endl;
			delete iter;
			break;
		}
		delete iter;
	}
	end_time = clock();
	printf("Find time %.4f second(s)\n", ((double)end_time - start) / ((double)CLOCKS_PER_SEC));
	cout << endl << endl << "***" << endl;
	return 0;
}

int Test::testMultiInsert(void* elem, size_t size)
{
	cout << "Test multiple Insert of single elem:" << endl;
	cout << "Elem:" << *(int*)elem << "  Size = " << size << "  Number of inserts = 100" << endl;
	this->set->clear();
	cout << "Set size at the beginning: " << this->set->size() << endl;
	if (this->set->empty())
	{
		start = clock();
		for (int i = 0; i <= 100; i++)
		{
			this->set->insert(elem, size);
		}
		end_time = clock();
		printf("Work time %.4f second(s)\n", ((double)end_time - start) / ((double)CLOCKS_PER_SEC));
		//пройтись итератором или найти
		int count = 0;
		List::Iterator* iter = nullptr;
		start = clock();
		for (int i = 0; i < this->set->hash_size; i++)
		{
			iter = this->set->list_arr[i]->find(elem, size);
			if (iter)
				count++;
			delete iter;
		}
		end_time = clock();
		printf("Find time %.4f second(s)\n", ((double)end_time - start) / ((double)CLOCKS_PER_SEC));
		cout << "The number of elements equal to this element = " << count << endl;
		cout << "Set size at the end: " << this->set->size() << endl;
		cout << endl << endl << "***" << endl;
		if (this->set->size() == 1)
			return 0;
	}
	return 1;
}

int Test::testInsertByType(void* elem1, size_t size1, void* elem2, size_t size2)
{
	cout << "Check hash:" << endl;
	cout << "First elem hash num: " << this->set->hash_function(elem1, size1) << endl;
	cout << "Second elem hash num: " << this->set->hash_function(elem2, size2) << endl;
	// проверить разный хэш
	this->set->insert(elem1, size1);
	this->set->insert(elem2, size2);
	Set::Iterator* iter1 = (Set::Iterator*)this->set->find(elem1, size1);
	Set::Iterator* iter2 = (Set::Iterator*)this->set->find(elem2, size2);
	if (!iter1->equals(iter2))
	{
		delete iter1;
		delete iter2;
		cout << "The addresses of the elements are different\n";
		cout << endl << endl << "***" << endl;
		return 0;
	}
	delete iter1;
	delete iter2;
	cout << "The addresses of the elements are not different\n";
	return 1;
}

int Test::testFindByType(void* elem, size_t elemSize)
{
	cout << "Test Searching elem with different types:\n";
	cout << "Insert elem " << *(int*)elem << " size = " << elemSize << endl;
	size_t fakeSize = elemSize - 1;
	cout << "size2 = " << fakeSize << endl;
	this->set->insert(elem, elemSize);
	Set::Iterator* iter1 = (Set::Iterator*)this->set->find(elem, fakeSize);
	Set::Iterator* iter2 = (Set::Iterator*)this->set->find(elem, elemSize);
	if (iter1 == nullptr && iter2)
	{
		cout << "Elem with size = " << fakeSize << " not found\n";
		cout << endl << endl << "***" << endl;
		delete iter1; delete iter2;
		return 0;
	}
	delete iter1; delete iter2;
	return 1;
}

int Test::testRemove(void* elem, size_t elemSize)
{
	cout << "Simple Remove test:\n";
	cout << "Elem:" << *(int*)elem << "  Size = " << elemSize << endl;
	this->set->insert(elem, elemSize);
	Set::Iterator* iter = (Set::Iterator*)this->set->find(elem, elemSize);
	if (iter != nullptr)
		cout << " - the element is inserted\n";
	this->set->remove(iter);
	delete iter;
	iter = (Set::Iterator*)this->set->find(elem, elemSize);
	if (!iter)
	{
		cout << " - the element is removed\n";
		cout << endl << endl << "***" << endl;
		delete iter;
		return 0;
	}
	delete iter;
	return 1;

}

int Test::testСonditionalRemove(size_t testCount)
{
	cout << "Remove with a condition:\n" << "Test value = " << testCount << endl;
	cout << "Condition: remove all multiples of 2 and 3\n";
	Set::Iterator* iter = nullptr;
	size_t count = 0;
	start = clock();
	for (int i = 0; i < testCount; i++)
	{
		if ((i % 2 == 0) || (i % 3 == 0))
		{
			iter = (Set::Iterator*)this->set->find(&i, sizeof(int));
			this->set->remove(iter);
			delete iter;
		}
	}
	end_time = clock();
	int x = 0;
	for (int i = 0; i < testCount; i++)
	{
		x = i;
		if ((i % 2 == 0) || (i % 3 == 0))
		{
			iter = (Set::Iterator*)this->set->find(&x, sizeof(int));
			if (iter)
				cout << "Elem not removed\n";
			delete iter;
		}
	}
	printf("Work time %.4f second(s)\n", ((double)end_time - start) / ((double)CLOCKS_PER_SEC));
	cout << endl << endl << "***" << endl;
	//this->printToFile("SetPrint.txt");
	if (count == 0)
		return 0;
	return 1;
}

int Test::testTwiceRemove(void* elem, size_t elemSize)
{
	cout << "Test Double Remove:\n";
	cout << "Elem:" << *(int*)elem << "  Size = " << elemSize << endl;
	Set::Iterator* iter1 = nullptr, * iter2 = nullptr;
	size_t startSize = this->set->size(), finalSize = 0;
	iter1 = (Set::Iterator*)this->set->find(elem, elemSize);
	iter2 = (Set::Iterator*)this->set->find(elem, elemSize);
	this->set->remove(iter1);
	this->set->remove(iter2);
	if (!iter2)
		cout << "Elem\n";
	finalSize = this->set->size();
	cout << "Elem removed once\n";
	cout << endl << endl << "***" << endl;
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
	int max_list = 0, max_list_part = 0;
	int empty_lists = 0, empty_list_part = 0;
	int optimal_list = 0;
	int min_list = this->set->size(), min_list_part = 0;

	for (int i = 0; i < this->set->hash_size; i++)
	{
		if (max_list < this->set->list_arr[i]->size())
		{
			max_list = this->set->list_arr[i]->size();
		}
		if (this->set->list_arr[i]->empty())
		{
			empty_lists++;
		}
		if (min_list > this->set->list_arr[i]->size())
		{
			min_list = this->set->list_arr[i]->size();
		}
	}
	cout << "\nRehash \n Set size = " << this->set->size() << endl;
	cout << "Hash size = " << this->set->hash_size << endl;
	max_list_part = 100 / max_list;
	cout << max_list_part << "*\n";
	cout << "min " << min_list << endl;
	min_list_part = 100 / min_list;
	cout << min_list_part << "*\n";
	cout << "empty " << empty_lists<< endl;
	if(empty_lists != 0)
		empty_list_part = 100/empty_lists;
	cout << empty_list_part << "*" << endl << endl;
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