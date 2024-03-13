#include "ListAbstract.h"
#include "Mem.h"

class Node 
{
	friend class List;
	Node* next_Node;
	void* data;
	size_t data_Size;

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
	Mem* mm;
	//память не должна создаваться отдельно для каждого списка.

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
	class Iterator : public Container::Iterator
	{
	private:
		Node* address;
		List* lst;
		//нужна запомни ещё что-то. например адресс на сам list
	public:
		Iterator(Node* _head = nullptr)
		{
			this->address = _head;
		}
		void* getElement(size_t& size);
		bool hasNext();
		void goToNext();
		bool equals(Container::Iterator* right);
	};
	/*Iterator begin() {
		return Iterator(head);
	}
	Iterator end() {
		return Iterator(nullptr);
	}*/
	void* operator[](const int index);
};

