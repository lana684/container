#include "Table.h"

// Возврашает явно указатель на элемент, на который указывает итератор в данный момент.
// Неявно возвращает размер данных.
// Если итератор показывает за пределы контейнера (например, удален последний элемент), возвращает NULL.
void* Table::Iterator::getElement(size_t& size)
{
	void* ptr = NULL;
	return ptr;
}

// Возвращает true, если есть следующий элемент, иначе false.
bool Table::Iterator::hasNext()
{
	return true;
}

// Переход к следующему элементу.
void Table::Iterator::goToNext()
{

}

// проверка на равенство итераторов
bool Table::Iterator::equals(Container::Iterator* right)
{
	return 0;
}
 

// Функция возвращает значение, равное количеству элементов в контейнере.
int Table::size()
{
	return 0;
}

// Функция возвращает значение, равное максимальной вместимости контейнера в байтах.
size_t Table::max_bytes()
{
	return 0;
}

// Функция создает в динамической памяти итератор, указывающий на первый найденный
// в контейнере элемент. Если элемент не найден, возвращается пустой указатель.
// Удаление этого итератора должно делаться пользователем с помощью оператора delete.
Table::Iterator* Table::find(void* elem, size_t size)
{
	return (Iterator*)elem;
}

// Функция создает в динамической памяти итератор, указывающий на первый элемент
// контейнера. Если контейнер пустой, возвращается нулевой указатель.
// Удаление этого итератора должно делаться пользователем с помощью оператора delete.
Table::Iterator* Table::newIterator()
{
	void* elem = NULL;
	return (Iterator*)elem;
}

// Удаление элемента из позиции, на которую указывает итератор iter.
// После удаления итератор указывает на следующий за удаленным элемент.
void Table::remove(Container::Iterator* iter)
{

}

// Удаление всех элементов из контейнера.
void Table::clear()
{

}

// Если контейнер пуст возвращает true, иначе false
bool Table::empty()
{
	return true;
}

//Table::Table(MemoryManager& mem) : AbstractTable(mem) {}

// Добавление элемента в контейнер, с сответствующим ключом.
// Если такой ключ уже есть, функция ничего не делает и возвращает 1.
// В случае успешного добавления функция возвращает значение 0, в случае неудачи 1.
int Table::insertByKey(void* key, size_t keySize, void* elem, size_t elemSize)
{
	return 0; //успех
}

// Удаление элемента с сответствующим ключом из контейнера.
void Table::removeByKey(void* key, size_t keySize)
{

}

// Функция возвращает указатель на итератор, указывающий на найденный в контейнере элемент с сответствующим ключом.
// Если элемент не найден, возвращается нулевой указатель.
Table::Iterator* Table::findByKey(void* key, size_t keySize)
{
	return (Table::Iterator*)key;
}

// доступ к элементу с ключом key
void* Table::at(void* key, size_t keySize, size_t& valueSize)
{
	return key;
}

// хэш функция
size_t Table::hash_function(void* key, size_t keySize)
{
	return keySize;
}

//Table::~Table() {}
