#include "Table.h"
#include "Memory_Manager_Table.h"

//list1 - pair1, pair2...
//list2 - pair1, pair2
//list3 - nullptr
// 
//listn-1 - pair1
//listn - pair1, pair2...



// Возврашает явно указатель на элемент, на который указывает итератор в данный момент.
// Неявно возвращает размер данных.
// Если итератор показывает за пределы контейнера (например, удален последний элемент), возвращает NULL.
void* Table::Iterator::getElement(size_t& size)
{
	/*
	size = size_current_elem;
	return current_elem;     //типа Pair
	*/
	size = size_current_elem;
	return (void*)current_elem;     //типа Pair
	/*
	if (current_list_iter != nullptr)
		return current_list_iter->getElement(size);
	else return nullptr;
	*/
}



// Возвращает true, если есть следующий элемент, иначе false.
bool Table::Iterator::hasNext()
{ 
	if (current_list_iter != nullptr&&
		current_list_iter->hasNext() == true)
	{
		return true;
	}
	for (int i = index_current_list+1; i < table->max_number_of_lists; i++)
	{
		if (!table->keys_values[i]->empty())
		{
			return true;
		}
	}
	return false;
}

// Переход к следующему элементу.
void Table::Iterator::goToNext()
{
	size_t s = 0;

	//
	Pair* pair_key_value = nullptr;
	//

	if ( current_list_iter!=nullptr&&
		current_list_iter->hasNext() == true)
	{
		current_list_iter->goToNext();
		current_elem = (Pair*)current_list_iter->getElement(s);
		return;
	}
	for (int i = index_current_list + 1; i < table->max_number_of_lists; i++)
	{
		if (!table->keys_values[i]->empty())
		{
			current_list_iter = (List::Iterator*)table->keys_values[i]->newIterator();
			current_elem = (Pair*)current_list_iter->getElement(s);
			//
			pair_key_value = current_elem;
			//
			//printf("\nelem %d:  %d %llu %d %llu ", i, *(int*)pair_key_value->key, pair_key_value->keySize, *(int*)pair_key_value->value, pair_key_value->valueSize);
			return;
		}
	}

	current_list_iter = nullptr;   //если дошли до конца таблицы 
}

// проверка на равенство итераторов
bool Table::Iterator::equals(Container::Iterator* right)
//переопределить Container::Iterator* на Table::Iterator*
{
	//current_elem типа Pair - главное отличие итераторов
	if (this->current_elem == (((Table::Iterator*)right)->current_elem))
	{
		return true;
	}
	return false;
	
	/*
	Table::Iterator* comparing_iter = (Table::Iterator*)right;
	Table::Iterator* newIter = (Table::Iterator*)comparing_iter->table->newIterator();
	for (int i = 0; i < comparing_iter->table->max_number_of_lists; i++)
	{
		if (newIter->current_list_iter != comparing_iter->current_list_iter)
		{

		}
	}
	return false;
	*/
}
 

// Функция возвращает значение, равное количеству элементов в контейнере.
int Table::size()
{
	return current_number_of_elements;
}

// Функция возвращает значение, равное максимальной вместимости контейнера в байтах.
size_t Table::max_bytes()
{
	return max_number_of_lists*keys_values[0]->max_bytes();
}

// Функция создает в динамической памяти итератор, указывающий на первый найденный
// в контейнере элемент. Если элемент не найден, возвращается пустой указатель.
// Удаление этого итератора должно делаться пользователем с помощью оператора delete.
Container::Iterator* Table::find(void* elem, size_t size)
{
	Table::Iterator* iter = (Table::Iterator*)newIterator(); size_t s = 0;
	Pair* tmp_pair = (Pair*)iter->getElement(s);

	do
	{
		if (size == tmp_pair->valueSize && memcmp(elem, tmp_pair->value, size)==0)
		{
			return (Container::Iterator*)iter;
		}
		if (iter->hasNext())
		{
			iter->goToNext();
			tmp_pair = (Pair*)iter->getElement(s);
		}
		else
		{
			return nullptr;
		}

	} while (1);


}

// Функция создает в динамической памяти итератор, указывающий на первый элемент
// контейнера. Если контейнер пустой, возвращается нулевой указатель.
// Удаление этого итератора должно делаться пользователем с помощью оператора delete.
Container::Iterator* Table::newIterator()
{
	if (empty()==true)
		return nullptr;

	Table::Iterator* iter = new Iterator();
	iter->table = this;
	iter->index_current_list = 0;
	
	iter->current_list_iter = (List::Iterator*)this->last_list->newIterator();
	//iter->current_list_iter = (List::Iterator*)this->keys_values[0]->newIterator();
	if (iter->current_list_iter == nullptr)
	{
		return nullptr;
	}
	iter->size_table = max_number_of_lists;
	if (iter->current_list_iter !=nullptr)
	{
		iter->current_elem = (Pair*)iter->current_list_iter->getElement(iter->size_current_elem);
	}
	else
	{
		iter->current_elem = nullptr;
	}
	return (Container::Iterator*)iter;
}

// Удаление элемента из позиции, на которую указывает итератор iter.
// После удаления итератор указывает на следующий за удаленным элемент.
void Table::remove(Container::Iterator* iter)
//переопределить Container::Iterator* на Table::Iterator
{
	try 
	{
		keys_values[((Table::Iterator*)iter)->index_current_list]->remove(((Table::Iterator*)iter)->current_list_iter);
		((Table::Iterator*)iter)->goToNext();
		current_number_of_elements -= 1;
	}
	catch (List::Error er) 
	{
		cout << "Element is not deleted\n";
		return;
	}
	
}

// Удаление всех элементов из контейнера.
void Table::clear()
{
	for (int i = 0; i < max_number_of_lists; i++)
	{
		keys_values[i]->clear(); //чистим списки
	}
	current_number_of_elements = 0;
}

// Если контейнер пуст возвращает true, иначе false
bool Table::empty()
{
	if (current_number_of_elements == 0)
		return true;
	else  
		return false; 
}

//много утечек но работает:
/*
// Добавление элемента в контейнер, с сответствующим ключом.
// Если такой ключ уже есть, функция ничего не делает и возвращает 1.
// В случае успешного добавления функция возвращает значение 0, в случае неудачи 1.
int Table::insertByKey(void* key, size_t keySize, void* elem, size_t elemSize)
{
	
	void* k = _memory.allocMem(keySize); //new char[keySize];
	memcpy(k, key, keySize);
	void* el = _memory.allocMem(elemSize);
	memcpy(el, elem, elemSize);
	Pair pair_key_value = { k, keySize, el, elemSize };
	//Pair pair_key_value = { key, keySize, elem, elemSize };
	//Pair* pair_key_value = new Pair();
	//pair_key_value->key = key; pair_key_value->keySize = keySize; pair_key_value->value = elem; pair_key_value->valueSize = elemSize;

	//cout << *((char*)pair_key_value.key);
	size_t size_pair = sizeof(keySize) + sizeof(elemSize) + sizeof(k) + sizeof(el);
	//size_t size_pair = sizeof(keySize) + sizeof(elemSize) + sizeof(key) + sizeof(elem);
	//void* pair = (void*)pair_key_value;
	void* pair = &pair_key_value;
	if (findByKey(key, keySize) != nullptr)
		return 1;
	size_t hash = hash_function(key, keySize);
	
	if (keys_values[hash]->push_front(pair, size_pair)==0)
	//if (keys_values[hash]->push_front((void*)& pair_key_value, size_pair) == 0)
	{
		current_number_of_elements++; 
		this->last_list = keys_values[hash];
		return 0; //успех
	}   
	else
	{
		return 1;
		free(k); free(el);
	}
	
}
*/

// Добавление элемента в контейнер, с сответствующим ключом.
// Если такой ключ уже есть, функция ничего не делает и возвращает 1.
// В случае успешного добавления функция возвращает значение 0, в случае неудачи 1.
int Table::insertByKey(void* key, size_t keySize, void* elem, size_t elemSize)
{
	/*
	void* k = _memory.allocMem(keySize); //new char[keySize];
	memcpy(k, key, keySize);
	void* el = _memory.allocMem(elemSize);
	memcpy(el, elem, elemSize);
	Pair pair_key_value = { k, keySize, el, elemSize };
	*/
	Pair* pair_key_value = new Pair(key, keySize, elem, elemSize); 
	
	//Pair* pair_key_value = new Pair();
	//pair_key_value->key = key; pair_key_value->keySize = keySize; pair_key_value->value = elem; pair_key_value->valueSize = elemSize;

	//cout << *((char*)pair_key_value.key);
	//size_t size_pair = sizeof(keySize) + sizeof(elemSize) + sizeof(k) + sizeof(el);
	size_t size_pair = sizeof(keySize) + sizeof(elemSize) + sizeof(key) + sizeof(elem);
	//void* pair = (void*)pair_key_value;
	void* pair = pair_key_value;
	if (findByKey(key, keySize) != nullptr)
		return 1;
	size_t hash = hash_function(key, keySize);

	if (keys_values[hash]->push_front(pair, size_pair) == 0)
		//if (keys_values[hash]->push_front((void*)& pair_key_value, size_pair) == 0)
	{
		current_number_of_elements++;
		this->last_list = keys_values[hash];
		return 0; //успех
	}
	else
	{
		return 1;
		//free(k); free(el);
	}

}

// Удаление элемента с сответствующим ключом из контейнера.
void Table::removeByKey(void* key, size_t keySize)
{

	Table::Iterator* table_iter = (Table::Iterator*)findByKey(key, keySize);
	this->keys_values[table_iter->index_current_list]->remove(table_iter->current_list_iter);
}

// Функция возвращает указатель на итератор, указывающий на найденный в контейнере элемент с сответствующим ключом.
// Если элемент не найден, возвращается нулевой указатель.
Container::Iterator* Table::findByKey(void* key, size_t keySize)
{	
	size_t hash = hash_function(key, keySize);
	size_t size = 0; // размер пары key_value и указателей на пару

	if (keys_values[hash]->empty() == true)
	{
		return nullptr;
	}
	Pair* pair_key_value; 
	//iter->current_elem = (List::Iterator*)keys_values[hash].find(key, keySize); 
	// find списка не сработает так как он хранит структуру
	//перебирать все элементы с помощью итератора списка, извлекать ключ и сравнивать
	this->last_list = keys_values[hash];
	Table::Iterator* table_iter = (Table::Iterator *)newIterator();
	if (table_iter == nullptr)
	{
		return nullptr;
	}
	table_iter->current_list_iter= (List::Iterator*)keys_values[hash]->newIterator();

	pair_key_value = (Pair*)table_iter->current_list_iter->getElement(size);
	//printf("\nFind:%s %d %s %d\n", (int*)pair_key_value->key, pair_key_value->keySize, (int*)pair_key_value->value, pair_key_value->valueSize);
	//printf("\Key:%s %d \n", (char*)key, keySize);
    // printf("\nFind:%d %d %d %d\n", *(char*)pair_key_value->key, pair_key_value->keySize, *(char*)pair_key_value->value, pair_key_value->valueSize);
	//printf("\Key:%d %d \n", *(char*)key, keySize);
	if (memcmp(pair_key_value->key, key, keySize) == 0)
	{
		return table_iter;
	}
	while (table_iter->current_list_iter->hasNext() )
	{
		if (memcmp(pair_key_value->key, key, keySize) == 0)
		{
			return table_iter;
		}
		table_iter->goToNext();
		pair_key_value = (Pair*)table_iter->current_list_iter->getElement(size);
	}
	
	return nullptr;
}

// доступ к элементу с ключом key
void* Table::at(void* key, size_t keySize, size_t& valueSize)
{
	Table::Iterator* iter = (Table::Iterator*)findByKey(key, keySize);
	if (iter != nullptr)
	{
		//Pair* p = (Pair*)iter->current_list_iter->getElement(valueSize);
		//return p->value;             //возвращается из структуры Pair value
		return iter->current_list_iter->getElement(valueSize);     
		//возвращается структура Pair key-value -- лучше, так как есть и ключ, и значение
	}
	return nullptr;
}

// хэш функция
size_t Table::hash_function(void* key, size_t keySize)
{
	return GroupContainer::hash_function(key,keySize) % max_number_of_lists;
}

Table::Table(MemoryManager& mem) : AbstractTable(mem) //, pairs_key_value(MMT.pairs_key_value)
{
	Memory_Manager_Table& MMT = (Memory_Manager_Table&)mem;
	max_number_of_lists = MMT.max_size;
	keys_values = MMT.pairs_key_value;
	current_number_of_elements = 0;
}

Pair* Table::operator[](const char* key)
{
	size_t s = 0;											
	Table::Iterator* iter = (Table::Iterator*)findByKey((void*)key, strlen(key));
	if (iter != nullptr)
	{
		return (Pair*)iter->getElement(s);
	}
}

Pair* Table::operator[](int key)
{
	size_t s = 0;
	Table::Iterator* iter = (Table::Iterator*)findByKey((void*)&key, sizeof(key));
	if (iter != nullptr)
	{
		return (Pair*)iter->getElement(s);
	}
	
}

Table::~Table()
{
	clear();
}


