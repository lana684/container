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

	//������ �� ListAbstract.h
	int push_front(void* elem, size_t elemSize);
	void pop_front();
	void* front(size_t& size);
	int insert(Container::Iterator* iter, void* elem, size_t elemSize);

	//������ �� Container.h
	int size();
	size_t max_bytes();
	Container::Iterator* find(void* elem, size_t size);
	Container::Iterator* newIterator();
	void remove(Container::Iterator* iter);
	void clear();
	bool empty();
	class Iterator : public Container::Iterator //��������� � private ��� � protected GroupList. ����������� 
	{
	private: //� ������ �������� ����� ������ ������� ���� public
		Node* address;
		Node* first_elem;
		Node* last_elem;
		List* lst;

	public: //������ ��� �� �����. ��� ��� ���������� ����� �������������� ��� ���������� �� container. ��� ��� ��� ������. ����� ����� ��������� node � protected ����� ��� ������ � groupList
		Iterator(Node* _head = nullptr);
		void* getElement(size_t& size);
		bool hasNext();
		void goToNext();
		bool equals(Container::Iterator* right);

	};
	void* operator[](const int index);
};

