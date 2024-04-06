
#pragma once
#include "TreeAbstract.h"
//#include "list.h"
#include <list>

class Node
{
	Node* next;
	Node* prev;
	void* data;
	size_t data_Size;


public:
	Node* get_next() { return next; }
	Node* get_prev() { return prev; }
	void* get_data() { return data; }
	void set_data(void* _data) { data = _data; }
	Node(void* _data, size_t _data_Size, Node* _next = nullptr, Node* _prev=nullptr)
	{
		data = _data;
		data_Size = _data_Size;
		next = _next;
		prev = _prev;
	}
};
class my_Node
{
public:
	void* data;
	size_t size;
	Node* parent;
	Node* me;
	list<Node>* list_me;
	list<Node>* child;
	//my_Node(void* _data, size_t _size, Node* _parent, Node* _me, list<Node>* _child=nullptr): data(_data), size(_size), parent(_parent), me(_me), child(_child) {}
};
class Tree :public AbstractTree
{
private:

	list<Node>* root; // указатель на двусвязанный список двусвязанных списков
	//List2* mylist;
	int count_of_elements;

	MemoryManager* mm;
public:
	class Iterator : public AbstractTree::Iterator
	{
		//list<my_Node>* it;
		my_Node* it;
		//list<my_Node>* it_list;
		//list<my_Node>* Node_list;
		//my_Node* Node;
	public:
		//Iterator(list<my_Node>* x) :it(x) {}
		//////////Iterator(list<list<my_Node>>* x) :it(x) {}
		//list<my_Node>* get_it() { return it; }
		//////////list<list<my_Node>>* get_it() { return it; }
		void set_it(my_Node* _it) { it = _it; }
		my_Node* get_it() { return it; }
		//void set_it_list(list<my_Node>* _it_list) { it_list = _it_list; }
		//void set_Node(my_Node* _Node) { Node = _Node; }
		//void set_Node_list(list<my_Node>* _Node_list) { Node_list = _Node_list; }
		//////////void set_element(list<list<my_Node>>* it) { this->it = it; }
		bool goToParent();
		bool goToChild(int child_index);
		void* getElement(size_t& size) override;
		bool hasNext() override;
		void goToNext() override;
		bool equals(Container::Iterator* right) override {};
		bool equals(Iterator* right);
	};

	Iterator* my_it = nullptr;

	Tree(MemoryManager& mem);

	//Tree_Node* get_root() { return root->front(); } 

	int insert(AbstractTree::Iterator* iter, int child_index, void* elem, size_t size) override;
	bool remove(AbstractTree::Iterator* iter, int leaf_only) override ;

	//int insert(Iterator* iter, int child_index, void* elem, size_t size);
	//bool remove(Iterator* iter, int leaf_only);
	int size() override;
	size_t max_bytes() override;
	Iterator* find(void* elem, size_t size) override;
	Iterator* newIterator() override;

	void remove(Container::Iterator* iter) override;
	void clear() override;
	bool empty() override;
	~Tree();
};
