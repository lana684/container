#include "GroupList.h"

GroupList::Iterator::Iterator()
{
	this->address = nullptr;
	this->prev_elem = nullptr;
	this->headInIter = nullptr;
}

void* GroupList::Iterator::getElement(size_t& size)
{
	if (address != nullptr)
	{
		size = address->data_Size;
		return address->data;
	}
	else
		return nullptr;
}

bool GroupList::Iterator::hasNext()
{
	if (address->next_Node == nullptr)
		return false;
	else
		return true;
}
void GroupList::Iterator::goToNext()
{

	if (Iterator::hasNext())
	{
		prev_elem = address;
		address = address->next_Node;
	}
	else
	{
		prev_elem = nullptr;
		address = headInIter;
	}
}
bool GroupList::Iterator::equals(Container::Iterator* right)
{
	if (address->data != right->getElement(address->data_Size))
		return false;
	else
		return true;
}