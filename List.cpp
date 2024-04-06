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

//добавление элемента в начало спискe
int List::push_front(void* elem, size_t elemSize) 
{
	//** - ìîæíî âûíåñòè â groupList

	//âûäåëåíèå ïàìÿòè èç memory îôîðìèòü êàê ìåòîä list
	//ìîæíî â node, íî òîãäà êàæäàÿ íîäà äîëæíà çíàòü memory manager

	void* wdst_elem = _memory.allocMem(elemSize);
	//ïðîâåêðêà ñ ïîìîùüþ maxBytes??


	memcpy(wdst_elem, elem, elemSize);			   //** êîïèðîâàíèå äàííûõ â âûäåëåííóþ íàì îáëàñòü ïàìÿòè

	Node* new_Node = new Node(wdst_elem, elemSize); 
	if (new_Node != nullptr)                       //**
	{											   //**
		new_Node->next_Node = head;				   //**
		head = new_Node;						   //**
	}										       //**
												   //âûíåñòè çàïîëíåíèå íîäû â ãðóïëèñò
	if (head == nullptr)                           //** Ýòî òàêæå ìîæíî âûíåñòè â ôóêíöèþ. Ïóñòü îíà áóäåò âîçâðàùàòü 1 èëè 0. Òîãäà çäåñü äîñòàòî÷íî ïðîïèñàòü return è íàøó ôóíêöèþ, â êîòîðóá ìû íàïðàâèì íàøè äàííûå
		return 1;                                  //**

	list_Size++;								   //**
	return 0;									   //**
} 

//+ óäàëåíèå ýëåìåíòà èç íà÷àëà ñïèñêà
void List::pop_front()
{
	if (head == nullptr) throw List::Error("Head is absent");
	Node* point_tmp = head;

	_memory.freeMem(point_tmp->data);

	head = head->next_Node;
	delete point_tmp;
	list_Size--;
}

//+ âîçâðàò óêàçàòåëÿ íà ïåðâûé ýëåìåíò ñïèñêà
void* List::front(size_t&)
{
	if (head == nullptr) throw List::Error("Head is absent");
	return head;
}

//+? âñòàâêà ïî èòåðàòîðó
int List::insert(Container::Iterator* iter, void* elem, size_t elemSize)
{
	void* wdst_elem = _memory.allocMem(elemSize);

	memcpy(wdst_elem, elem, elemSize); //~ êîïèðîâàíèå äàííûõ â âûäåëåííóþ íàì îáëàñòü ïàìÿòè

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

	list_Size++;
	return 0;
}

//+ âûâîäèò êîëè÷åñòâî ýëåìåíòîâ â ñïèñêå
int List::size()
{
	return list_Size;
}

//+ âîçâðàùàåò ìàêñèìàëüíî äîñòóïíîå êîëè÷ñåòâî ïàìÿòè ó ìåíåäæåðà ïàìÿòè
size_t List::max_bytes()
{
	return  _memory.size();
}

//+ íà âûõîä ïðèõîäèò èòåðàòîð óêàçûâàþùèé íà ïåðâûé ýëåìåíò â ñïèñêå êîòîðûé ñîäåðæèò elem
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

//+ ñîçäàíèå íîâãî èòåðàòîðà, êîòîðûé óêàçûâàåò èçíà÷àëüíî íà head
Container::Iterator* List::newIterator()
{
	List::Iterator* it = new List::Iterator(this->head);
	return it;	
}

//+ óäàëåíèå ýëåìåíòà ñïèñêà íà êîòîðûé óêàçûâàåò èòåðàòîð
void List::remove(Container::Iterator* iter)
{
	Node* current = head;
	Node* previous = nullptr;
	while (current->data != iter->getElement(current->data_Size) && current != nullptr)
	{
		previous = current;
		current = current->next_Node;
	}
	if (current == nullptr) throw List::Error("No elem");
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

	_memory.freeMem(current->data);

	delete(current);
}
//+ óäàëåíèå âñåõ ýëåìåíòîâ â ñïèñêå
void List::clear() //+ âðîäå ðàáîòàåò. Óäàëÿåò 
{
	while (head != nullptr) pop_front();
}
//+ ïðîâåðêà íà íàëè÷èå ýëåìåíòîâ â ñïèñêå
bool List::empty() //+
{
	if (head != nullptr)
		return false;
	else
		return true;
}

//ìåòîäû èòåðàòîðà
List::Iterator::Iterator(Node* _head) //+
{
	this->address = _head;
	this->first_elem = _head;
	this->last_elem = _head;
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
	if (List::Iterator::hasNext())
		address = address->next_Node;
	else
		address = first_elem;
}
bool List::Iterator::equals(Container::Iterator* right) //+
{
	if (address->data != right->getElement(address->data_Size))
		return false;
	else
		return true;
}

void* List::operator[](const int index)
{
	if (index < 0 || index >= list_Size) throw Error("Out of range");
	Node* current = this->head;
	for (int i = 0; i < index; i++)
		current = current->next_Node;
	return current->data;
}

