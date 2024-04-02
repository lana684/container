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
	Node* head;
	int list_Size;

public:
	class RangeError
	{
	private:
		int index;
	public:
		RangeError(int _index) : index(_index) {}
		void out_of_range()
		{
			cout << "invalid index" << this->index << endl;
		}
	};
	class Error
	{
	public:
		char msg[256];
		Error(const char* err_msg)
		{
			strcpy(msg, err_msg);
			cout << msg << endl;
		}
	};

	List(MemoryManager& mem);

	~List();

	Node* get_Head()
	{
		return this->head;
	}

	//Методы из ListAbstract.h
	int push_front(void* elem, size_t elemSize);
	void pop_front();
	void* front(size_t& size);
	int insert(Container::Iterator* iter, void* elem, size_t elemSize);

	//Меотды из Container.h
	int size();
	size_t max_bytes();
	Container::Iterator* find(void* elem, size_t size);
	Container::Iterator* newIterator();
	void remove(Container::Iterator* iter);
	void clear();
	bool empty();
	class Iterator : public Container::Iterator //перенести в private или в protected GroupList. рассмотреть 
	{
	private: //в случае переноса всего класса сделать поля public
		Node* address;
		Node* first_elem;
		Node* last_elem;
		List* lst;
		
		//bool in_the_end = 0;

	public:
		Iterator(Node* _head = nullptr);
		void* getElement(size_t& size);
		bool hasNext();
		void goToNext();
		bool equals(Container::Iterator* right);

		//bool end(); //аналогично hasNext
	};
	/*Iterator begin() {
		return Iterator(head);
	}
	Iterator end() {
		return Iterator(nullptr);
	}*/
	void* operator[](const int index);
};

