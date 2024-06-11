#pragma once
#include "Container.h"

// Базовый класс для однонаправленного и двунаправленного списков
class GroupList: public Container
{
protected:
	struct Node
	{
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

	Node* head;

public:
	
    GroupList(MemoryManager &mem): Container(mem) {}

	virtual int creating_a_node(void* wdst_elem, void* elem, size_t elemSize, Node* prevNode)
	{
		memcpy(wdst_elem, elem, elemSize);			   //** копирование данных в выделенную нам область памяти

		Node* new_Node = new Node(wdst_elem, elemSize);//**
		if (new_Node != nullptr)                       //**
		{												   //**
			new_Node->next_Node = prevNode;				   //**
			//prevNode = new_Node;						   //**
			//условие проверки на head
		}
		if (prevNode == nullptr)
			return 1;
		else
			return 0;
    }

	/*class Iterator : public Container::Iterator
	{
	public:
		Node* address;
		Node* prev_elem;
		Node* headInIter;
		Iterator();

		void* getElement(size_t& size);
		bool hasNext();
		void goToNext();
		bool equals(Iterator* right);
	};*/


};
