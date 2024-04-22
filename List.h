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
	size_t list_Size; // количество элементов в списке 

	size_t mem_Size_List;

public:
	class Error //класс вывода ошибок, если такие будут наблюдаться
	{
	public:
		char msg[256]; //массив куда будет записана причина ошибки. Запись ошибки от меня
		Error(const char* err_msg)
		{
			strcpy(msg, err_msg);
			cout << msg << endl; //вывод этого сообщения 
		}
	};

	List(MemoryManager& mem); //конструктор List

	~List();//деструктор List

	/*Node* get_Head()
	{
		return this->head;
	}*/

	//Методы из ListAbstract.h
	int push_front(void* elem, size_t elemSize); //добавление элемента в начало списка
	void pop_front();//удаление элемента из начала списка 
	void* front(size_t& size);//возвращает указатель на первый элемент в списке
	int insert(Container::Iterator* iter, void* elem, size_t elemSize);//добавление нового элемента по итератору

	//Меотды из Container.h
	int size(); //возвращет количество элементов в списке 
	size_t max_bytes();//Функция возвращает значение, равное максимальной вместимости контейнера в байтах
	Container::Iterator* find(void* elem, size_t size); //создание итератора, который указывает на элемент списка, который содержит в себе elem 
	Container::Iterator* newIterator();// создание итератора, который указывает на первый элемент в списке
	void remove(Container::Iterator* iter); //Удаление элемента с позиции на который указывает итератор
	void clear(); //удаление всех элементов в списке
	bool empty();//проверка на наличие элементов в списке
	class Iterator : public Container::Iterator //перенести в private или в protected GroupList. рассмотреть 
	{
	private: //в случае переноса всего класса сделать поля public
		Node* address;
		Node* first_elem; //?? тут надо подумать. Если я знаю свой списко, то я могу знать и первый элемент в списке без использования отдельной ссылки, хотя кто знает?
		Node* last_elem;
		List* lst;

	public: //методы тут не нужны. Так как реализация будет восприниматься как реализация из container. так как они похожи. Тогда можно перенести node в protected листа или вообще в groupList
		Iterator(List* _lst = nullptr);
		void* getElement(size_t& size);//получение ссылки на объект элемента в списике
		bool hasNext(); //проверка на наличие следующего элемента
		void goToNext();//переход к следующему элементу 
		bool equals(Container::Iterator* right); //проверка на совпадение элементов
	};
};

