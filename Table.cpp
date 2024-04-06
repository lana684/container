#pragma once
#include "Tree.h"
#include <stdio.h>
Tree::Tree(MemoryManager& mem) :AbstractTree(mem)
{
		mm = &mem;
		//my_it = (Iterator*)(mem.allocMem(sizeof(Iterator)));
		count_of_elements = 0;
		root = nullptr;//new list<my_Node>;//(list<my_Node>*)(mem.allocMem(sizeof(list<my_Node>)));
		//root->push_back(my_Node(nullptr, 0));
		//my_it->set_element(root);
		//my_it->set_it(&root->front());
		//my_it->set_this_list(root);
}
bool Tree::Iterator::goToParent()
{
	if (it->parent != nullptr)
	{
		it = (my_Node*)it->parent->get_data();
		return true;
	}
	//list<my_Node>::iterator iter = /*find_if(this_list->begin(), this_list->end(), &(*it));*/this_list->begin();
	//it->begin() = iter;
	return false;
}
bool Tree::Iterator::goToChild(int child_index)
{
	if (it->child != nullptr)
	{
		child_index %= it->child->size();
		list<Node>::iterator iter = it->child->begin();
		for (int i = 0; i < child_index; i++)
			iter++;
		return true;
	}
	return false;
}
void* Tree::Iterator::getElement(size_t& size)
{
	size = it->size;
	return it->data;

}
bool Tree::Iterator::hasNext()
{
	if (it->me->get_next() != nullptr)
		return true;
	return false;
}
void Tree::Iterator::goToNext()
{
	if (hasNext())
	{
		it = (my_Node*)it->me->get_next()->get_data();
	}
}
bool Tree::Iterator::equals(Iterator* right)
{
	if (it == right->get_it())
		return true;
	return false;
}
void Tree::remove(Container::Iterator* iter)
{
	//size_t size;
	//my_Node* node = (my_Node*)iter->getElement(size);
	////list<Node>::iterator it = std::find(node->list_me->begin(), node->list_me->begin(), (Node*)node->me->get_data());
}
int Tree::insert(AbstractTree::Iterator* iter, int child_index, void* elem, size_t size)
{
	size_t sizex;
	if (((my_Node*)(iter->getElement(sizex)))->child == nullptr)
	{
		((my_Node*)(iter->getElement(sizex)))->child = (list<Node>*)mm->allocMem(sizeof(list<Node>));
		child_index = 0;
	}
	else child_index %= ((my_Node*)(iter->getElement(sizex)))->child->size();
	list<Node>::iterator it = ((my_Node*)(iter->getElement(sizex)))->child->begin();
	for (int i = 0; i < child_index; i++)
		it++;
	my_Node* node = (my_Node*)mm->allocMem(sizeof(my_Node));
	Node* tmp = (Node*)mm->allocMem(sizeof(Node));
	tmp->set_data((void*)node);
	node->data = elem;
	node->size = size;
	node->me = tmp;
	node->child = nullptr;
	node->parent = ((my_Node*)(iter->getElement(sizex)))->me;
	node->list_me = ((my_Node*)(iter->getElement(sizex)))->child;
	((my_Node*)(iter->getElement(sizex)))->child = (list<Node>*)mm->allocMem(sizeof(list<Node>));
	((my_Node*)(iter->getElement(sizex)))->child->insert(it, *tmp);
	count_of_elements++;
	return 0;
}
bool Tree::remove(AbstractTree::Iterator* iter, int leaf_only)
{
	size_t size;
	if (leaf_only == 1)
	{
		if (((my_Node*)(iter->getElement(size)))->child != nullptr)
			return false;
		//list<Node>::iterator it = std::find_if(iter->get_it()->list_me->begin(), iter->get_it()->list_me->end(), iter->get_it()->me);
		//iter->get_it()->list_me->erase(it);
		return true;
	}
	remove(iter);
	return true;
}
int Tree::size()
{
	return count_of_elements;
}
size_t Tree::max_bytes()
{
	return mm->maxBytes();
}
Tree::Iterator* Tree::find(void* elem, size_t size)
{
	return NULL;
}
Tree::Iterator* Tree::newIterator()
{
	return NULL;
}
void Tree::clear()
{

}
bool Tree::empty()
{

	return true;
}
Tree::~Tree()
{

}
