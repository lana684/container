#include "List.h"

//size_t mem_Size = -1;


List::List(MemoryManager& mem) : AbstractList(mem)
{
	head = nullptr;
	list_Size = 0;
}

List::~List()
{
	while (head != nullptr) pop_front();
}

//+ добавление элемента в начало списка 
int List::push_front(void* elem, size_t elemSize)
{
	//** - можно вынести в groupList

	//выделение памяти из memory оформить как метод list
	//можно в node, но тогда каждая нода должна знать memory manager

	void* wdst_elem = _memory.allocMem(elemSize);
	//провекрка с помощью maxBytes??


	memcpy(wdst_elem, elem, elemSize);			   //** копирование данных в выделенную нам область памяти

	Node* new_Node = new Node(wdst_elem, elemSize);
	if (new_Node != nullptr)                       //**
	{											   //**
		new_Node->next_Node = head;				   //**
		head = new_Node;						   //**
	}										       //**
												   //вынести заполнение ноды в груплист
	if (head == nullptr)                           //** Это также можно вынести в фукнцию. Пусть она будет возвращать 1 или 0. Тогда здесь достаточно прописать return и нашу функцию, в которуб мы направим наши данные
		return 1;                                  //**

	mem_Size_List += elemSize;
	list_Size++;								   //**
	return 0;									   //**
}

//+ удаление элемента из начала списка
void List::pop_front()
{
	if (head == nullptr) throw List::Error("Head is absent");
	Node* point_tmp = head;

	_memory.freeMem(point_tmp->data);

	mem_Size_List -= point_tmp->data_Size;
	head = head->next_Node;
	delete point_tmp;
	list_Size--;

}

//+ возврат указателя на первый элемент списка
void* List::front(size_t&) //+
{
	if (head == nullptr) throw List::Error("Head is absent");
	return head;
}

//+ вставка по итератору
int List::insert(Container::Iterator* iter, void* elem, size_t elemSize)
{
	void* wdst_elem = _memory.allocMem(elemSize);

	memcpy(wdst_elem, elem, elemSize); //~ копирование данных в выделенную нам область памяти

	Node* new_Node = new Node(wdst_elem, elemSize);
	if (new_Node != nullptr)
	{
		Node* current = head;
		Node* previous = nullptr;
		while (current->data != iter->getElement(elemSize) && current != nullptr)
		{
			previous = current;
			current = current->next_Node;
		}
		previous->next_Node = new_Node;
		new_Node->next_Node = current;

	}

	if (head == nullptr)
		return 1;

	mem_Size_List += elemSize;
	list_Size++;
	return 0;
}

//+ выводит количество элементов в списке
int List::size() //+
{
	return list_Size;
}

//+ возвращает максимально доступное количсетво памяти у менеджера памяти
size_t List::max_bytes()
{
	return  _memory.size();
}

//+ на выход приходит итератор указывающий на первый элемент в списке который содержит elem
Container::Iterator* List::find(void* elem, size_t size)
{
	List::Iterator* it = new List::Iterator(this);
	while (it->getElement(size) != elem && it->hasNext() == 1)
	{
		it->goToNext();
	}
	return it;
}

//+ создание новго итератора, который указывает изначально на head
Container::Iterator* List::newIterator() //+
{
	List::Iterator* it = new List::Iterator(this);
	return it;
}

//+ удаление элемента списка на который указывает итератор
void List::remove(Container::Iterator* iter) //+
{
	//Если мы удаляем все элементы в списке и хотим воспользоваться итератором, то мы должны просто отловить ошибку?
	if (head == nullptr) throw List::Error("Head is empty or iter point to nullptr");
	Node* current = head;
	Node* previous = head;
	while (current->data != iter->getElement(current->data_Size) && current != nullptr)
	{
		previous = current;
		current = current->next_Node;
	}
	if (current == nullptr) throw List::Error("No elem");
	if (iter->hasNext() == 0)
	{
		if (current == head)
			this->head = nullptr;
		else
			previous->next_Node = nullptr;
		iter->goToNext();
	}
	else
	{
		if (current == head)
			this->head = current->next_Node;
		else
			previous->next_Node = current->next_Node;
		iter->goToNext();
	}

	this->mem_Size_List -= current->data_Size;
	this->list_Size--;

	_memory.freeMem(current->data);

	delete(current);
}
//+ удаление всех элементов в списке
void List::clear() //+ вроде работает. Удаляет 
{
	while (head != nullptr) pop_front();
}
//+ проверка на наличие элементов в списке
bool List::empty() //+
{
	if (head != nullptr)
		return false;
	else
		return true;
}

//методы итератора
List::Iterator::Iterator(List* _lst) //+
{
	this->lst = _lst;
	this->address = _lst->head;
	this->first_elem = _lst->head;
	this->last_elem = _lst->head;
	while (last_elem->next_Node != nullptr)
		last_elem = last_elem->next_Node;
}
void* List::Iterator::getElement(size_t& size) //+
{
	return address->data;
}
bool List::Iterator::hasNext() //+
{
	if (address->next_Node == nullptr)
		return false;
	else
		return true;
}
void List::Iterator::goToNext() //+
{

	if (List::Iterator::hasNext()) //первый элемент долже нменяться так как меняется сама голова.
		address = address->next_Node;
	else
		address = lst->head;
}
bool List::Iterator::equals(Container::Iterator* right) //+
{
	if (address->data != right->getElement(address->data_Size))
		return false;
	else
		return true;
}


