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

//+ ���������� �������� � ������ ������ 
int List::push_front(void* elem, size_t elemSize)
{
	//** - ����� ������� � groupList

	//��������� ������ �� memory �������� ��� ����� list
	//����� � node, �� ����� ������ ���� ������ ����� memory manager

	void* wdst_elem = _memory.allocMem(elemSize);
	//��������� � ������� maxBytes??


	memcpy(wdst_elem, elem, elemSize);			   //** ����������� ������ � ���������� ��� ������� ������

	Node* new_Node = new Node(wdst_elem, elemSize);
	if (new_Node != nullptr)                       //**
	{											   //**
		new_Node->next_Node = head;				   //**
		head = new_Node;						   //**
	}										       //**
												   //������� ���������� ���� � ��������
	if (head == nullptr)                           //** ��� ����� ����� ������� � �������. ����� ��� ����� ���������� 1 ��� 0. ����� ����� ���������� ��������� return � ���� �������, � ������� �� �������� ���� ������
		return 1;                                  //**

	mem_Size_List += elemSize;
	list_Size++;								   //**
	return 0;									   //**
}

//+ �������� �������� �� ������ ������
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

//+ ������� ��������� �� ������ ������� ������
void* List::front(size_t&) //+
{
	if (head == nullptr) throw List::Error("Head is absent");
	return head;
}

//+ ������� �� ���������
int List::insert(Container::Iterator* iter, void* elem, size_t elemSize)
{
	void* wdst_elem = _memory.allocMem(elemSize);

	memcpy(wdst_elem, elem, elemSize); //~ ����������� ������ � ���������� ��� ������� ������

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

//+ ������� ���������� ��������� � ������
int List::size() //+
{
	return list_Size;
}

//+ ���������� ����������� ��������� ���������� ������ � ��������� ������
size_t List::max_bytes()
{
	return  _memory.size();
}

//+ �� ����� �������� �������� ����������� �� ������ ������� � ������ ������� �������� elem
Container::Iterator* List::find(void* elem, size_t size)
{
	List::Iterator* it = new List::Iterator(this);
	while (it->getElement(size) != elem && it->hasNext() == 1)
	{
		it->goToNext();
	}
	return it;
}

//+ �������� ����� ���������, ������� ��������� ���������� �� head
Container::Iterator* List::newIterator() //+
{
	List::Iterator* it = new List::Iterator(this);
	return it;
}

//+ �������� �������� ������ �� ������� ��������� ��������
void List::remove(Container::Iterator* iter) //+
{
	//���� �� ������� ��� �������� � ������ � ����� ��������������� ����������, �� �� ������ ������ �������� ������?
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
//+ �������� ���� ��������� � ������
void List::clear() //+ ����� ��������. ������� 
{
	while (head != nullptr) pop_front();
}
//+ �������� �� ������� ��������� � ������
bool List::empty() //+
{
	if (head != nullptr)
		return false;
	else
		return true;
}

//������ ���������
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

	if (List::Iterator::hasNext()) //������ ������� ����� ��������� ��� ��� �������� ���� ������.
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


