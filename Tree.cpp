#include "Tree.h"
#include <list>
bool Tree::Iterator::goToParent()
{
	if (it->parent != nullptr)
	{
		it = it->parent;
		return true;
	}
	return false;
}
bool Tree::Iterator::goToChild(int child_index)
{
	if (it->child != nullptr)
	{
		it = &(it->child->front()); //get_Head
		return true;
	}
	return false;
}
void* Tree::Iterator::getElement(size_t& size)
{
	size = it->node_size;
	return it;
}
bool Tree::Iterator::hasNext()
{
	//list<Node>::iterator x = it;
	//Node* this_it = (it->parent->child->end());
	//if()

	return true;
}
void Tree::Iterator::goToNext()
{

}
bool Tree::Iterator::equals(Container::Iterator* right)
{
	Tree::Iterator* r = (Tree::Iterator*)(right);
	if (r->get_it() == it)
		return true;
	return false;
}
int Tree::insert(AbstractTree::Iterator* iter, int child_index, void* elem, size_t size)
{
	Tree::Iterator* it = (Tree::Iterator*)iter;
	Node* to = it->get_it();
	Tree::Iterator to_it(&(it->get_it()->child->front()));

	int i = 1;
	while (i < child_index && to_it.get_it() != nullptr)
		to_it.goToNext();

	return 0;
	//if(iter->goToChild(0) == false)
	return 1;
}
bool Tree::remove(AbstractTree::Iterator* iter, int leaf_only)
{

	return true;
}
int Tree::size()
{
	return count_of_elements;
}
size_t Tree::max_bytes()
{
	return _memory.maxBytes();
}
Tree::Iterator* Tree::find(void* elem, size_t size)
{
	Tree::Iterator* x = newIterator();
	/*while (x->hasNext())
	{
		if (x->get_it()->value == elem && x->get_it()->get_size() == size)
			return x;
		else
			x->goToNext();
	}
	*/
	return nullptr;
}
Tree::Iterator* Tree::newIterator()
{
	if (count_of_elements)
	{
	    Tree::Iterator* x=(Tree::Iterator*)malloc(sizeof(Tree::Iterator));
		x->set_element(root);
		return x;
	}
	return nullptr;
}
void Tree::clear()
{

}
bool Tree::empty()
{

	return true;
}
//void Tree::Container::remove(Iterator* iter)
//{
//
//}
