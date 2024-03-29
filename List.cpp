#include "List.h"

void* wdst_Global = nullptr;
size_t mem_Size = -1;


List::List(MemoryManager& mem) : AbstractList(mem)
{
	head = nullptr;
	list_Size = 0;
	mm = &mem;
	if (mem_Size < 0)
		mem_Size = mm->size();
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

	if (mem_Size - elemSize < 0) throw List::Empty("Net bolshe pamaty");
	mem_Size -= elemSize;
	void* wdst_elem = mm->allocMem(elemSize);

	memcpy(wdst_elem, elem, elemSize); //~ копирование данных в выделенную нам область памяти

	Node* new_Node = new Node(elem, elemSize); 
	if (new_Node != nullptr)
	{
		new_Node->next_Node = head;
		head = new_Node;
		new_Node->wdst_Node = wdst_elem; //~ Узел смотрит туда, где находиться его информация в нашей памяти
	}

	if (head == nullptr)
		return 1;

	list_Size++;
	return 0;
} 

//+ удаление элемента из начала списка
void List::pop_front()
{
	if (head == nullptr) throw List::Empty("Head is absent");
	Node* point_tmp = head;

	mm->freeMem(point_tmp->wdst_Node);
	mem_Size += point_tmp->data_Size;

	head = head->next_Node;
	delete point_tmp;
	list_Size--;
}

//+ возврат указателя на первый элемент списка
void* List::front(size_t&)
{
	if (head == nullptr) throw List::Empty("Head is absent");
	return head;
}

//+? вставка по итератору
int List::insert(Container::Iterator* iter, void* elem, size_t elemSize)
{
	if (mem_Size - elemSize < 0) throw List::Empty("Net bolshe pamaty");
	mem_Size -= elemSize;
	void* wdst_elem = mm->allocMem(elemSize);

	memcpy(wdst_elem, elem, elemSize); //~ копирование данных в выделенную нам область памяти

	Node* new_Node = new Node(elem, elemSize);
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

		new_Node->wdst_Node = wdst_elem; //~ Узел смотрит туда, где находиться его информация в нашей памяти
	}

	if (head == nullptr)
		return 1;

	list_Size++;
	return 0;
	return 0;
}

//+ выводит количество элементов в списке
int List::size()
{
	return list_Size;
}

//+ возвращает максимально доступное количсетво памяти у менеджера памяти
size_t List::max_bytes()
{
	return  mm->size();
}

//+ на выход приходит итератор указывающий на первый элемент в списке который содержит elem
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

//+ создание новго итератора, который указывает изначально на head
Container::Iterator* List::newIterator()
{
	List::Iterator* it = new List::Iterator(this->head);
	return it;	
}

//+ удаление элемента списка на который указывает итератор
void List::remove(Container::Iterator* iter)
{
	Node* current = head;
	Node* previous = nullptr;
	while (current->data != iter->getElement(current->data_Size) && current != nullptr)
	{
		previous = current;
		current = current->next_Node;
	}
	if (current == nullptr) throw List::Empty("No elem");
	if (iter->hasNext() == 0)
	{
		previous->next_Node = nullptr;
		iter->goToNext();
	}
	else
	{
		previous->next_Node = current->next_Node;
		iter->goToNext();
	}

	mm->freeMem(current->wdst_Node);
	mem_Size += current->data_Size;

	delete(current);
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
List::Iterator::Iterator(Node* _head)
{
	this->address = _head;
	this->first_elem = _head;
	this->last_elem = _head;
	while (last_elem->next_Node != nullptr)
		last_elem = last_elem->next_Node;
}
void* List::Iterator::getElement(size_t& size)
{
	return address->data;
}
bool List::Iterator::hasNext()
{
	if (address->next_Node == nullptr)
	{
		in_the_end = 1;
		return false;
	}
	else
	{
		if (address != first_elem)
			in_the_end = 0;
		return true;
	}
}
void List::Iterator::goToNext()
{
	if (hasNext)
		address = address->next_Node;
	else
		address = first_elem;
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