#pragma once
#include "TreeAbstract.h"
#include <list>
#include "ListAbstract.h"
class Node
{
	friend class Tree;
public:
	void* value = 0;
	list<Node>* child = nullptr;
	int index=0;
	Node* parent = nullptr;
	size_t node_size=0;
	Node(MemoryManager& mem, void* _value=nullptr, Node* _parent=nullptr, int _node_size=0)
	{
		value=_value; 
		child= (list<Node>*)mem.allocMem(sizeof(list<Node>));
		parent = _parent; 
		node_size = _node_size;
	}
	size_t get_size() { return node_size; }
};
class Tree :public AbstractTree
{
	Node* root;
	int count_of_elements;

public:
	Tree(MemoryManager& mem) :AbstractTree(mem) 
	{
		root = (Node*)(_memory.allocMem(sizeof(Node(mem))));
		root->child = (list<Node>*)(_memory.allocMem(sizeof(list<Node>)));
		count_of_elements = 0;
	}
	class Iterator : public Container::Iterator
	{
		Node* it;
	public:
		Iterator(Node* x) :it(x) {}
		Node* get_it() { return it; }
		void set_element(Node* it) { this->it = it; }
		bool goToParent();
		bool goToChild(int child_index);
		void* getElement(size_t& size) override;
		bool hasNext() override;
		void goToNext() override;
		bool equals(Container::Iterator* right) override;
	};
	Node* get_root() { return root; }
	Iterator* iter=(Iterator*)_memory.allocMem(sizeof(Iterator(root)));
	int insert(AbstractTree::Iterator* iter, int child_index, void* elem, size_t size) override;
	bool remove(AbstractTree::Iterator* iter, int leaf_only) override;
	int size() override;
	size_t max_bytes() override;
	Iterator* find(void* elem, size_t size) override;
	Iterator* newIterator() override;
	void Container::remove(Iterator* iter) {};
	void clear() override;
	bool empty() override;
	~Tree() {};
};