#pragma once
#include "Memory_Manager_Table.h"

class TableTest
{
	//Memory_Manager_Table* mem;
	Table* table;
public:
	TableTest(Table* t);
	void change_table(Table* t);
	void check_find();
	void check_remove();
	void check_clear();
	void check_insertByKey(size_t num_inserted_values);
	void check_removeByKey();
	void check_findByKey();
	~TableTest(){}
};

