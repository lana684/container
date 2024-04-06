#include "ListAbstract.h"
#include "Mem.h"

class Node 
{
	friend class List;

	Node* next_Node;
	void* data;
	size_t data_Size;

	
protected:
	Node(void* _data, size_t _data_Size, Node* _next_Node = nullptr)
	{

		data = _data;
		data_Size = _data_Size;
		next_Node = _next_Node;
	}
};

class List : public AbstractList
{
private:
	Node* head; //ссылка на первый элемент в списке
	int list_Size; //количество элементов в списке

public:
	class Error //класс для вывода ошибок, если такие будут наблюдаться
	{
	public:
		char msg[256]; //массив, куда будет записана причина ошибки. Запись провожу я
		Error(const char* err_msg)
		{
			strcpy(msg, err_msg);
			cout << msg << endl; //вывод этого сообщения
		}
	};

	List(MemoryManager& mem); //конструктор

	~List(); //деструктор

	/*Node* get_Head()
	{
		return this->head;
	}*/

	//Методы из ListAbstract.h
	int push_front(void* elem, size_t elemSize); //добавление элемента в начало списка
	void pop_front(); //удаление элемента из начала списка
	void* front(size_t& size); //возвращает указатель на первый элемент в списке
	int insert(Container::Iterator* iter, void* elem, size_t elemSize); //добавдение нового элемента по итератору

	////Меотды из Container.h
	int size(); //возвращает количество элементов
	size_t max_bytes(); // Функция возвращает значение, равное максимальной вместимости контейнера в байтах
	Container::Iterator* find(void* elem, size_t size); //создание итератора, который указывает на элемент списка, который содержит в себе elem
	Container::Iterator* newIterator(); //создание итератора, который указывает на первый элемент списка
	void remove(Container::Iterator* iter); //Удаление элемента с позиции, на который указывает итератор
	void clear(); //удаление всех элементов списка
	bool empty(); //проверка, есть ли в списке элементы или он пустой
	class Iterator : public Container::Iterator 
	{
	private: 
		Node* address;
		Node* first_elem;
		Node* last_elem;
		List* lst;

	public: 
		Iterator(Node* _head = nullptr);
		void* getElement(size_t& size); //получение ссылки на объект элемента списка
		bool hasNext(); //проверка на наличие следующего элемента
		void goToNext(); //переход к следующему элементу
		bool equals(Container::Iterator* right); //проверка на совпадение элементов

	};
	void* operator[](const int index); //не особо важно
};

