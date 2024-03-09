#include "List.h"

List::List(MemoryManager& mem) : AbstractList(mem)
{
	head = nullptr;
	list_Size = 0;
	//mm = &mem;
}

List::~List()
{
	while (head != nullptr) pop_front();
}

//+ äîáàâëåíèå ýëåìåíòà â íà÷àëî ñïèñêà 
int List::push_front(void* elem, size_t elemSize)
{

	Node* new_Node = new Node(elem, elemSize);
	if (new_Node != nullptr)
	{
		new_Node->next_Node = head;
		head = new_Node;
	}
	//Äîáàâèòü ñúåäàíèå ïàìÿòè ó ìåíåäæåðà ïàìÿòè

	//ïðè ñîçäàíèè íîâîãî ýëåìåíòà ìû âûäåëÿåì ïàìÿòü âíóòðè íàøåãî ìàññèâà, êàêèì-òî íåîáû÷íûì ñïîñîáîì. Êàê? Ïðèäóìàé ñàì. 
	//ìû îòäåëÿåì ÷àñòü ïàìÿòè êîòîðóþ òðåáóåò íàø íîâûé ýëåìåíò. Â ýòó âûäåëåííóþ ÷àñòü ïàìÿòè ìû êîïèðóåì äàííûå. Îòíèìàåì íóæíîå êîëè÷åñòâî ïàìÿòè

	if (head == nullptr)
		return 1;

	list_Size++;
	return 0;
} 

//+ óäàëåíèå ýëåìåíòà èç íà÷àëà ñïèñêà
void List::pop_front()
{
	//äîáàâèòü ïðîâåðêó íà íàëè÷èå ýëåìåíòà
	//äîáàâèòü îáðàáîò÷èê íà äàííîé îøèáêè
	Node* point_tmp = head;
	head = head->next_Node;
	delete point_tmp;
	list_Size--;
}

void* List::front(size_t&)
{
	//Ñòîèò äîáàâèòü ïðîâåðêó íà íàëè÷èå ýëåìåíòà â ñïèñêå
	//Ìîæíî èñïîëüçîâàòü îáðàáîò÷èê î êîòîðîì ãîâîðèòñÿ â pop_front
	return head;
}

//- âñòàâêà ïî èòåðàòîðó
int List::insert(Container::Iterator* iter, void* elem, size_t elemSize)
{
	return 0;
}

//+? âûâîäèò êîëè÷åñòâî ýëåìåíòîâ â ñïèñêå
int List::size()
{
	return list_Size;
}

//-? âîçâðàùàåò ìàêñèìàëüíî äîñòóïíîå êîëè÷ñåòâî ïàìÿòè ó ìåíåäæåðà ïàìÿòè
size_t List::max_bytes()
{
	size_t size_memory_manager = size();
	return size_memory_manager;
}

//- íà âûõîä ïðèõîäèò èòåðàòîð óêàçûâàþùèé íà ïåðâûé ýëåìåíò â ñïèñêå êîòîðûé ñîäåðæèò elem
Container::Iterator* List::find(void* elem, size_t size)
{
	Container::Iterator* it = nullptr;
	return it;
}

//- ñîçäàíèå íîâãî èòåðàòîðà, êîòîðûé óêàçûâàåò èçíà÷àëüíî íà head
Container::Iterator* List::newIterator()
{
	Container::Iterator* it /*= Iterator()*/;

	return it;
}

//- óäàëåíèå ýëåìåíòà ñïèñêà íà êîòîðûé óêàçûâàåò èòåðàòîð
void List::remove(Container::Iterator* iter)
{

}
//+ óäàëåíèå âñåõ ýëåìåíòîâ â ñïèñêå
void List::clear()
{
	while (head != nullptr) pop_front();
}
//+ ïðîâåðêà íà íàëè÷èå ýëåìåíòîâ â ñïèñêå
bool List::empty()
{
	if (head != nullptr)
		return false;
	else
		return false;
}

//ìåòîäû èòåðàòîðà
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
	//íóæåí äîï ìåòîä? ìàòîä âûäà÷è ññûëêè... ïîãîäè... ðàçâå getelem íå âûäàåò íàì óêàçàòåëü, ÷òî óíèêàëåí äëÿ âñåõ?
	//íóýåí ìåòîä äëÿ ïîëó÷åíèÿ ðàçìåðà èíôîðìàöèè â ýëåìåíòå
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