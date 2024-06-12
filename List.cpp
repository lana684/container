#include "List.h"

List::List(MemoryManager& mem) : AbstractList(mem)
{
	head = nullptr;
	list_Size = 0;
}

List::~List()
{
	clear();
	
}


int List::push_front(void* elem, size_t elemSize) 
{
	//int n = filling_a_node(wdst_elem, elem, elemSize, this->head);

	void* wdst_elem = _memory.allocMem(elemSize);
	memcpy(wdst_elem, elem, elemSize);			   //** копирование данных в выделенную нам область памяти

	Node* new_Node = new Node(wdst_elem, elemSize);//**
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

void List::pop_front() 
{
	if (head == nullptr) return;
	
	Node* point_tmp = head;

	_memory.freeMem(point_tmp->data);

	mem_Size_List -= point_tmp->data_Size;
	head = head->next_Node;
	delete point_tmp;
	list_Size--;

}

void* List::front(size_t&)
{
	return head;
}

int List::insert(Container::Iterator* iter, void* elem, size_t elemSize) 
{

	void* wdst_elem = _memory.allocMem(elemSize);

	memcpy(wdst_elem, elem, elemSize); 

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

int List::size() 
{
	return list_Size;
}


size_t List::max_bytes()
{
	return  _memory.size();
}

Container::Iterator* List::find(void* elem, size_t size) 
{
	if (this->head != nullptr)
	{
		List::Iterator* it = (List::Iterator*)List::newIterator();
		if (!it)
			return nullptr;
		while (memcmp(it->getElement(size), elem, size) != 0)
		{
			if (it->hasNext() == 1)
				it->goToNext();
			else
			{
				delete it;
				return nullptr;
			}
		}

		return it;
	}
	else
		return nullptr;
}

Container::Iterator* List::newIterator() 
{
	if (this->head != nullptr)
	{
		Iterator* it = new Iterator();
		it->address = head;
		it->headInIter = head;
		return it;
	}
	else
		return nullptr;
}

void List::remove(Container::Iterator* iter)
{
	if (head == nullptr) throw List::Error("");
	List::Iterator* iterator = dynamic_cast<List::Iterator*>(iter);
	if (iterator)
	{
		if (iter->hasNext() == 0)
		{
			if (iterator->address == head)
				this->head = nullptr;
			else
				iterator->prev_elem->next_Node = nullptr;
		}
		else
		{
			if (iterator->address == head)
				this->head = iterator->address->next_Node;
			else
				iterator->prev_elem->next_Node = iterator->address->next_Node;
		}
		this->mem_Size_List -= iterator->address->data_Size;
		this->list_Size--;
		iter->goToNext();

		if (iterator->prev_elem != nullptr)
			_memory.freeMem(iterator->prev_elem->data);
		else
			_memory.freeMem(iterator->address->data);

		delete(iterator->prev_elem);
	}
	else
		return;
}

void List::clear() 
{
	while (head != nullptr) pop_front();
}

bool List::empty()
{
	if (head != nullptr)
		return false;
	else
		return true;
}


List::Iterator::Iterator()
{
	this->address = nullptr;
	this->prev_elem = nullptr;
	this->headInIter = nullptr;
}
void* List::Iterator::getElement(size_t& size)
{
	if (address != nullptr)
	{
		size = address->data_Size;
		return address->data;
	}
	else
		return nullptr;
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

	if (List::Iterator::hasNext())
	{
		prev_elem = address;
		address = address->next_Node;
	}
	else
	{
		prev_elem = nullptr;
		address = headInIter;
	}
}
bool List::Iterator::equals(Container::Iterator* right) 
{
	if (address->data != right->getElement(address->data_Size))
		return false;
	else
		return true;
}


