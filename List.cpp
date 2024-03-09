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

//+ добавление элемента в начало списка 
int List::push_front(void* elem, size_t elemSize)
{

	Node* new_Node = new Node(elem, elemSize);
	if (new_Node != nullptr)
	{
		new_Node->next_Node = head;
		head = new_Node;
	}
	//Добавить съедание памяти у менеджера памяти

	//при создании нового элемента мы выделяем память внутри нашего массива, каким-то необычным способом. Как? Придумай сам. 
	//мы отделяем часть памяти которую требует наш новый элемент. В эту выделенную часть памяти мы копируем данные. Отнимаем нужное количество памяти

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

//-? возвращает максимально доступное количсетво памяти у менеджера памяти
size_t List::max_bytes()
{
	size_t size_memory_manager = size();
	return size_memory_manager;
}

//- на выход приходит итератор указывающий на первый элемент в списке который содержит elem
Container::Iterator* List::find(void* elem, size_t size)
{
	Container::Iterator* it = nullptr;
	return it;
}

//- создание новго итератора, который указывает изначально на head
Container::Iterator* List::newIterator()
{
	Container::Iterator* it /*= Iterator()*/;

	return it;
}

//- удаление элемента списка на который указывает итератор
void List::remove(Container::Iterator* iter)
{

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
	//нужен доп метод? матод выдачи ссылки... погоди... разве getelem не выдает нам указатель, что уникален для всех?
	//нуэен метод для получения размера информации в элементе
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