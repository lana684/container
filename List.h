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

	//ּועמהû טח ListAbstract.h
	int push_front(void* elem, size_t elemSize);
	void pop_front();
	void* front(size_t& size);
	int insert(Container::Iterator* iter, void* elem, size_t elemSize);

	//ּומעהû טח Container.h
	int size();
	size_t max_bytes();
	Container::Iterator* find(void* elem, size_t size);
	Container::Iterator* newIterator();
	void remove(Container::Iterator* iter);
	void clear();
	bool empty();
	class Iterator : public Container::Iterator
	{
		Node* current;
	public:
		Iterator(Node* _current)
		{
			current = _current;
		}
		void* getElement(size_t& size);
		bool hasNext();
		void goToNext();
		bool equals(Container::Iterator* right);
	};
	Iterator begin() {
		return Iterator(head);
	}
	Iterator end() {
		return Iterator(nullptr);
	}
	void* operator[](const int index);
};

