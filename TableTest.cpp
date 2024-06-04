#include "TableTest.h"

/*
TableTest::TableTest(size_t s=10000)
{
	Memory_Manager_Table m(s);
	mem = &m;
	Table t(m);
	table = &t;
}
*/

TableTest::TableTest(Table* t)
{
	table = t;
}

void TableTest::change_table(Table* t)
{
	table = t;
}

void TableTest::check_find()
{

	int r = 8;
	const char* k2 = "second8";
	table->insertByKey((void*)k2, sizeof(k2), (void*)&r, sizeof(r));
	Pair* pair_key_value = nullptr;
	size_t pair_size;
	Table::Iterator*  table_iter = (Table::Iterator*)table->find((void*)&r, sizeof(r));
	if (table_iter != nullptr)
	{
		pair_key_value = (Pair*)table_iter->current_list_iter->getElement(pair_size);
		printf("\n%s %d %s %d\n", (char*)pair_key_value->key, pair_key_value->keySize, (char*)pair_key_value->value, pair_key_value->valueSize);
	}

	
}

void TableTest::check_remove()
{

}

void TableTest::check_clear()
{

}

void TableTest::check_insertByKey(size_t num_inserted_values)
{
	const char* k = "k1"; const char* el = "3";
	Pair* pair_key_value = nullptr;
	size_t pair_size = 0;

	int j = 0;
	table->insertByKey((void*)k, strlen(k)+1, (void*)el, strlen(el)+1);
	//cout << *((char*)(*table)[k]->key)<<"  " <<* ((char*)(*table)[k]->value);

	if (table->findByKey((void*)k, strlen(k)) == nullptr)
	{
		cout << "Can't find inserted element";
	}
	
	for (int i = 1; i < 10; i++)
	{
		j = i + 7;		
		table->insertByKey((void*)&i, sizeof(i), (void*)&j, sizeof(j));
		cout << " " <<*(int*)(*table)[i]->key<<" "<< *(int*)(*table)[i]->value<<"\n";
		if (table->findByKey((void*)&i, sizeof(i)) == nullptr)
		{
			cout << "Can't find inserted element";
		}
	}
	for (int i = 1; i < 10; i++)
	{
		j = i + 7;
		//cout<< "\n" << "inserted (1-not,0-yes):" <<table->insertByKey((void*)&i, sizeof(i), (void*)&j, sizeof(j));
		//cout << " " << *(char*)(*table)[i]->key;// << " " << *(int*)(*table)[i]->value;
		printf("%d i=%d", *(char*)(*table)[i]->key, i);
		//if (table->findByKey((void*)&i, sizeof(i)) == nullptr)
		{
			//cout << "Can't find inserted element";
		}
	}

	table->last_list = table->keys_values[1];
	Table::Iterator* table_iter = (Table::Iterator*)this->table->newIterator();
	//table_iter->current_list_iter  = table_iter->
	for (int i = 1; i < table->max_number_of_lists - 1; i++)
	{
		if (table_iter != nullptr && table_iter->current_list_iter != nullptr)
		{
			//pair_key_value = (Pair*)table_iter->current_list_iter->getElement(pair_size);			
			//cout <<* (int*)pair_key_value->key << "  elem -" << i << "  " << *(int*)pair_key_value->value << "\n";
			//printf("\nelem %d:  %d %llu %d %llu ",i, *(int*)pair_key_value->key, pair_key_value->keySize, *(int*)pair_key_value->value, pair_key_value->valueSize);
			//table_iter->goToNext();
			if ((*table)[i] != nullptr)
			{
				printf("\nNo: key =%d value = %d   (i=%d)", *(char*)(*table)[i]->key, *(char*)(*table)[i]->value, i);
			}
			//pair_key_value = table_iter->current_elem;
			//printf("\nelem %d:  %d %llu %d %llu ", i, *(int*)pair_key_value->key, pair_key_value->keySize, *(int*)pair_key_value->value, pair_key_value->valueSize);
		}
		
	}

	table->insertByKey(&pair_key_value, pair_size, (void*)"pair1", sizeof("pair1"));
	if (table->findByKey((void*)"pair1", sizeof("pair1")) == nullptr)
	{
		cout << "Can't find inserted element";
	}
	double dkey = 2.3;
	if (table->findByKey(&dkey, sizeof(dkey)) != nullptr)
	{
		cout << "Find non-existent element";
	}

	table_iter = (Table::Iterator*)table->findByKey((void*)"k123", sizeof("k123"));
	if (table_iter != nullptr)
	{
		pair_key_value = (Pair*)table_iter->current_list_iter->getElement(pair_size);
	}
	else printf("\n(right).Element with this key wasn`t found");
	

	/*
	clock_t start, end;
	double time;
	start = clock();
	for (int i = 10; i < num_inserted_values + 10; i++)
	{
		j = i + 7;
		table->insertByKey((void*)&i, sizeof(i), (void*)&j, sizeof(j));
		//cout << " " << *(int*)(*table)[i]->key << " " << *(int*)(*table)[i]->value << "\n";
	}
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;


	std::cout << "\nMy:" << time;
	printf("\nMytime:%.32lf", time);
	*/
}

void TableTest::check_removeByKey()
{
	
}

void TableTest::check_findByKey()
{
	const char* k = "k1"; const char* el = "3";
	size_t pair_size = 0;
	Pair* pair_key_value = nullptr;
	Table::Iterator* table_iter = (Table::Iterator*)table->findByKey((void*)k, strlen(k));
	if (table_iter != nullptr)
	{
		pair_key_value = (Pair*)table_iter->current_list_iter->getElement(pair_size);
		printf("\n%s %d %s %d", (char*)pair_key_value->key, pair_key_value->keySize, (char*)pair_key_value->value, pair_key_value->valueSize);
	}

	
}











/*
if ((*table)[k] != nullptr)
{
	//printf("\n%s %llu %s %llu\n", (char*)((*table)[k]->key), (*table)[k]->keySize, (char*)((*table)[k]->value), (*table)[k]->valueSize);
}
*/