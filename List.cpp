#include "List.h"

List::List(MemoryManager& mem) : AbstractList(mem)
{
	head = nullptr;
	list_Size = 0;
	mm = &mem;
}

List::~List()
{
	while (head != nullptr) pop_front();
}

//+ ���������� �������� � ������ ������ 
int List::push_front(void* elem, size_t elemSize)
{

	Node* new_Node = new Node(elem, elemSize);
	if (new_Node != nullptr)
	{
		new_Node->next_Node = head;
		head = new_Node;
	}
	//�������� �������� ������ � ��������� ������

	//��� �������� ������ �������� �� �������� ������ ������ ������ �������, �����-�� ��������� ��������. ���? �������� ���. 
	//�� �������� ����� ������ ������� ������� ��� ����� �������. � ��� ���������� ����� ������ �� �������� ������. �������� ������ ���������� ������

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

//-? ���������� ����������� ��������� ���������� ������ � ��������� ������
size_t List::max_bytes()
{
	size_t size_memory_manager = size();
	return size_memory_manager;
}

//- �� ����� �������� �������� ����������� �� ������ ������� � ������ ������� �������� elem
Container::Iterator* List::find(void* elem, size_t size)
{
	Container::Iterator* it = nullptr;
	return it;
}

//- �������� ����� ���������, ������� ��������� ���������� �� head
Container::Iterator* List::newIterator()
{
	Container::Iterator* it /*= Iterator()*/;

	return it;
}

//- �������� �������� ������ �� ������� ��������� ��������
void List::remove(Container::Iterator* iter)
{

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
	return current->data;
}
bool List::Iterator::hasNext()
{
	if (current->next_Node == nullptr)
		return false;
	else
		return true;
}
void List::Iterator::goToNext()
{
	current = current->next_Node;
}
bool List::Iterator::equals(Container::Iterator* right)
{
	//����� ��� �����? ����� ������ ������... ������... ����� getelem �� ������ ��� ���������, ��� �������� ��� ����?
	//����� ����� ��� ��������� ������� ���������� � ��������
	/*if (current->data == right->getElement(???))*/ 
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