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

//+ ���������� �������� � ������ ������ 
int List::push_front(void* elem, size_t elemSize)
{

	//��� �������� ������ �������� �� �������� ������ ������ ������ �������, �����-�� ��������� ��������. ���? �������� ���. 
	//�� �������� ����� ������ ������� ������� ��� ����� �������. � ��� ���������� ����� ������ �� �������� ������. �������� ������ ���������� ������

	//��������� ������ �� memory �������� ��� ����� list
	//����� � node, �� ����� ������ ���� ������ ����� memory manager

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// �� � ������ �������� ������ � ��� memory manager, ������ �� ������������ node
	// ����� ����������� ������ �� Node ���������� ���� ������� ������, � ������� ��������� ���� ������
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



	Node* new_Node = new Node(elem, elemSize); //����� ������������ memory manager 
	if (new_Node != nullptr)
	{
		new_Node->next_Node = head;
		head = new_Node;
	}
	//�������� �������� ������ � ��������� ������



	if (head == nullptr)
		return 1;

	list_Size++;
	return 0;
} 

//+ �������� �������� �� ������ ������
void List::pop_front()
{
	//�������� �������� �� ������� ��������
	//�������� ���������� �� ������ ������
	Node* point_tmp = head;
	head = head->next_Node;
	delete point_tmp;
	list_Size--;
}

void* List::front(size_t&)
{
	//����� �������� �������� �� ������� �������� � ������
	//����� ������������ ���������� � ������� ��������� � pop_front
	return head;
}

//- ������� �� ���������
int List::insert(Container::Iterator* iter, void* elem, size_t elemSize)
{
	return 0;
}

//+? ������� ���������� ��������� � ������
int List::size()
{
	return list_Size;
}

//+-? ���������� ����������� ��������� ���������� ������ � ��������� ������
size_t List::max_bytes()
{
	size_t size_memory_manager = size();
	return size_memory_manager;
}

//+- �� ����� �������� �������� ����������� �� ������ ������� � ������ ������� �������� elem
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

//- �������� ����� ���������, ������� ��������� ���������� �� head
Container::Iterator* List::newIterator()
{
	List::Iterator* it = new List::Iterator(this->head);
	return it;	
}

//- �������� �������� ������ �� ������� ��������� ��������
void List::remove(Container::Iterator* iter)
{
	Node* address = head;
	Node* bef_address = nullptr;
	while (address->data != iter->getElement(address->data_Size) && address != nullptr)
	{
		bef_address = address;
		address = address->next_Node;
	}
	//if (address == nullptr) //���������� ������ � ������� �����������
	bef_address->next_Node = address->next_Node;
	if (iter->hasNext() == 0)
	{
		
	}
	else
		iter->goToNext();
	delete(address);

}
//+ �������� ���� ��������� � ������
void List::clear()
{
	while (head != nullptr) pop_front();
}
//+ �������� �� ������� ��������� � ������
bool List::empty()
{
	if (head != nullptr)
		return false;
	else
		return false;
}

//������ ���������
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