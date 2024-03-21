#include "List.h"

List::List(MemoryManager& mem) : AbstractList(mem)
{
	head = nullptr;
	list_Size = 0;
	//mm = (Mem)mem;
}

List::~List()
{
	while (head != nullptr) pop_front();
}

//+ добавление элемента в начало списка 
int List::push_front(void* elem, size_t elemSize)
{

	//при создании нового элемента мы выделяем память внутри нашего массива, каким-то необычным способом. Как? Придумай сам. 
	//мы отделяем часть памяти которую требует наш новый элемент. В эту выделенную часть памяти мы копируем данные. Отнимаем нужное количество памяти

	//выделение памяти из memory оформить как метод list
	//можно в node, но тогда каждая нода должна знать memory manager

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// мы в начале копируем данные в наш memory manager, данные из конструктора node
	// после копирования данных мы Node указывавем нашу область памяти, в которой находятся наши данные
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



	Node* new_Node = new Node(elem, elemSize); //позже использовать memory manager 
	if (new_Node != nullptr)
	{
		new_Node->next_Node = head;
		head = new_Node;
	}
	//Добавить съедание памяти у менеджера памяти



	if (head == nullptr)
		return 1;

	list_Size++;
	return 0;
} 

//+ удаление элемента из начала списка
void List::pop_front()
{
	//добавить проверку на наличие элемента
	//добавить обработчик на данной ошибки
	Node* point_tmp = head;
	head = head->next_Node;
	delete point_tmp;
	list_Size--;
}

void* List::front(size_t&)
{
	//Стоит добавить проверку на наличие элемента в списке
	//Можно использовать обработчик о котором говорится в pop_front
	return head;
}

//- вставка по итератору
int List::insert(Container::Iterator* iter, void* elem, size_t elemSize)
{
	return 0;
}

//+? выводит количество элементов в списке
int List::size()
{
	return list_Size;
}

//+-? возвращает максимально доступное количсетво памяти у менеджера памяти
size_t List::max_bytes()
{
	size_t size_memory_manager = size();
	return size_memory_manager;
}

//+- на выход приходит итератор указывающий на первый элемент в списке который содержит elem
Container::Iterator* List::find(void* elem, size_t size)
{
	Node* tmp = (Node*)front(head->data_Size);
	if (tmp == nullptr)
		return nullptr;
	while (tmp->data != elem && tmp != nullptr)
	{
		tmp = tmp->next_Node;
	}
	List::Iterator* it = new List::Iterator(tmp);
	return it;
}

//- создание новго итератора, который указывает изначально на head
Container::Iterator* List::newIterator()
{
	List::Iterator* it = new List::Iterator(this->head);
	return it;	
}

//- удаление элемента списка на который указывает итератор
void List::remove(Container::Iterator* iter)
{
	Node* address = head;
	Node* bef_address = nullptr;
	while (address->data != iter->getElement(address->data_Size) && address != nullptr)
	{
		bef_address = address;
		address = address->next_Node;
	}
	//if (address == nullptr) //обработать ошибку с помощью обработчика
	bef_address->next_Node = address->next_Node;
	if (iter->hasNext() == 0)
	{
		
	}
	else
		iter->goToNext();
	delete(address);

}
//+ удаление всех элементов в списке
void List::clear()
{
	while (head != nullptr) pop_front();
}
//+ проверка на наличие элементов в списке
bool List::empty()
{
	if (head != nullptr)
		return false;
	else
		return false;
}

//методы итератора
void* List::Iterator::getElement(size_t& size)
{
	return address->data;
}
bool List::Iterator::hasNext()
{
	if (address->next_Node == nullptr)
		return false;
	else
		return true;
}
void List::Iterator::goToNext()
{
	address = address->next_Node;
}
bool List::Iterator::equals(Container::Iterator* right)
{
	if (address->data != right->getElement(address->data_Size))
		return false;
	else
		return true;
	return 0;
}

void* List::operator[](const int index)
{
	if (index < 0 || index >= list_Size) throw RangeError(index);
	Node* current = this->head;
	for (int i = 0; i < index; i++)
		current = current->next_Node;
	return current->data;
}