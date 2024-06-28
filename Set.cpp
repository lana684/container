#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include "Mem.h"
#include "Set.h"


Set::Iterator::Iterator(Set* set)
{
    if (!set->empty())
    {
        this->set = set;
        size_t first_index = 0, end_index = set->hash_size;
        end_index--;
        while (set->list_arr[first_index]->empty())
            first_index++;
        while (set->list_arr[end_index]->empty())
            end_index--;
        this->index = first_index;
        this->curent = set->list_arr[first_index];
        this->end_i = end_index;
        if(!this->iter_l)
            this->iter_l = set->list_arr[first_index]->newIterator();
        else
        {
            delete this->iter_l;
            this->iter_l = set->list_arr[first_index]->newIterator();
        }
    }
}

Set::Iterator::~Iterator()
{
    List::Iterator* iter = (List::Iterator*)this->iter_l;
    delete iter;
    this->set = nullptr;
    this->curent = nullptr;
}

void* Set::Iterator::getElement(size_t& size)
{
    return this->iter_l->getElement(size);
}

bool Set::Iterator::hasNext()
{
    size_t hash = this->set->hash_size; hash--;
    int tmp_i = this->index;
    int empty = 0;
    if (this->iter_l->hasNext() == true)
        return true;
    else if (this->iter_l->hasNext() == false && this->index != this->end_i )
    {
        void* tmp_list = nullptr;
        while (tmp_list == nullptr && tmp_i < hash)
        {
            tmp_i++;
            if (!this->set->list_arr[tmp_i]->empty())
                tmp_list = this->set->list_arr[tmp_i];
        }
        if (tmp_list)
            return true;
        else { return false; }
    }
    return false;
}

void Set::Iterator::goToNext()
{
    if (this->hasNext() == true)
    {
        if (this->iter_l->hasNext() == false && this->index != this->end_i)
        {
            int tmp = this->set->hash_size; tmp--;
            void* tmp_list = nullptr;
            while (tmp_list == nullptr && this->index < tmp)
            {
                this->index++;
                if (!this->set->list_arr[this->index]->empty())
                    tmp_list = this->set->list_arr[this->index];
            }
            if (tmp_list)
            {
                if(!this->iter_l)
                    this->iter_l = this->set->list_arr[this->index]->newIterator(); //утекает итератор
                else
                {
                    delete this->iter_l;
                    this->iter_l = this->set->list_arr[this->index]->newIterator();
                }
            }
        }
        else if (this->iter_l->hasNext())
        {
            this->iter_l->goToNext();
        }
    }
}


void Set::Iterator::shiftIter(List* list, Container::Iterator* listIter)
{
    List::Iterator* iter = dynamic_cast<List::Iterator*>(listIter);
    List::Iterator* tmp = list->newIterator();
    iter->address = tmp->address;
    iter->headInIter = iter->address;
    iter->prev_elem = nullptr;
    delete tmp;
}

//+-
bool Set::Iterator::equals(Container::Iterator* right)
{
    Set::Iterator* iter_r = dynamic_cast<Set::Iterator*>(right);
    if (this->iter_l->equals(iter_r->iter_l) == true)
    {
        return true;
    }
    else { return false; }
    /*void* elem = nullptr;
    size_t size = 0, tmp = 0;
    elem = right->getElement(size);
    if (memcmp(this->getElement(tmp), elem, size) == 0)
    {
        return true;
    }
    else { return false; }*/
}


int Set::size() {
    return this->set_count;
}

size_t Set::max_bytes() {
    return _memory.size();
}

Container::Iterator* Set::find(void* elem, size_t size)
{
    size_t hash = this->hash_function(elem, size);
    if (this->list_arr[hash]->empty())
        return nullptr;

    Set::Iterator* Iter = dynamic_cast<Set::Iterator*>(this->newIterator());
    if (Iter->index != hash) {
        Iter->index = hash;
        Iter->curent = this->list_arr[hash];
    }
    List::Iterator* iter = (List::Iterator*)Iter->iter_l;
    delete iter;
    Iter->iter_l = Iter->set->list_arr[hash]->find(elem, size);
    

    if (Iter->iter_l == nullptr)
    {
        delete Iter;
        return nullptr;
    }
    else { return Iter; }
}

Container::Iterator* Set::newIterator()
{
    if (this->set_count == 0) { return nullptr; }
    else
    {
        Set::Iterator* Iter = new Set::Iterator(this); // утекает 56 байт
        return Iter;
    }
}

void Set::remove(Container::Iterator* iter)
{
    if (iter != nullptr)
    {
        Set::Iterator* iter1 = dynamic_cast<Set::Iterator*>(iter);
        if (iter1 && iter1->iter_l)
        {
            size_t size = 0;
            void* elem = iter1->iter_l->getElement(size);
            if (!this->list_arr[iter1->index]->empty() /* && this->list_arr[iter1->index]->find(elem, size) != nullptr*/)
            {
                List::Iterator* it = (List::Iterator*)this->list_arr[iter1->index]->find(elem, size);
                if (it)
                {
                    int flag = 1;
                    size_t hash_num = hash_function(elem, size);
                    Container::Iterator* tmp_iter = this->list_arr[hash_num]->find(elem, size); //указатель типа лист итератор
                    List::Iterator* help = (List::Iterator*)tmp_iter;
                    if (tmp_iter)
                    {
                        // если последний элемент последнего непустого списка
                        if (iter->hasNext() == false && tmp_iter->hasNext() == false)
                        {
                            size_t tmp_size = 0;
                            this->list_arr[hash_num]->remove(tmp_iter);
                            if (!tmp_iter && tmp_iter->getElement(tmp_size) == this->list_arr[hash_num]->front(size))
                            {
                                throw Set::Error("The iterator has reached the end of the array");
                            }
                            flag = 0;
                        }
                        // последний элемент текущего списка
                        else if (iter->hasNext() && !tmp_iter->hasNext())
                        {
                            iter->goToNext();
                            this->list_arr[hash_num]->remove(tmp_iter);
                            flag = 0;
                        }
                        // если  не последний элемент текущего списка
                        else if (tmp_iter->hasNext())
                        {
                            this->list_arr[hash_num]->remove(tmp_iter);
                            flag = 0;
                        }

                        if (flag == 0)
                            this->set_count--;
                        if (tmp_iter != nullptr)
                            tmp_iter = nullptr;
                        delete help;
                    }
                    delete it;
                }
            }
        }
    }

}

//+- ???
void Set::clear()
{
    if (this->empty() == false)
    {
        int size = this->hash_size;
        int cur_list_size = 0;
        int tmp_set_size = this->set_count;
        for (int i = 0; i < size; i++)
        {
            cur_list_size = this->list_arr[i]->size();
            this->list_arr[i]->clear();
            if (this->list_arr[i]->empty() != true)
            {
                std::cout << "Error of claening";
                return;
            }
            tmp_set_size -= cur_list_size;
        }
        this->set_count = tmp_set_size;
    }
}

bool Set::empty() 
{
    int tmp = this->hash_size;
    for (int i = 0; i < tmp; i++)
        if (!this->list_arr[i]->empty())
            return false;
    return true;
}

//+- ???
int Set::insert(void* elem, size_t size)
{
    size_t hash = this->hash_function(elem, size);
    Container::Iterator* iter = nullptr;
    int result = -2;
    int rehash_flag = 0;
    if (hash < this->hash_size)
    {
        if (this->list_arr[hash]->empty() == false)
        {
            iter = this->list_arr[hash]->find(elem, size); // утекает созданный итератор
            if (iter == nullptr)
            {
                if (this->list_arr[hash]->size() == 50)
                {
                    rehash_flag++;
                }
                result = this->list_arr[hash]->push_front(elem, size);
                delete iter;
            }
            else {
                delete iter;
                return -1; 
            }
            if (rehash_flag == 1)
            {
                this->rehashing(_memory);
                cout << "NEW HASH SIZE " << this->hash_size << endl;
            }
        }
        else
        {
            result = this->list_arr[hash]->push_front(elem, size);
        }
        if (result == 1) { return -2; }
        else {
            this->set_count++;
            return 0;
        }
    }
    return -2;
}

//--
size_t Set::hash_function(void* value, size_t valueSize)
{
    if (value)
    {
        return GroupContainer::hash_function(value, valueSize) % this->hash_size;
    }
    else
        throw Container::Error("Hash_err");
}

//--
void Set::rehashing(MemoryManager& mem)
{
    size_t prev_hash_size = hash_size;
    hash_size = 2 * hash_size;
    List** new_list_arr = (List**)_memory.allocMem(sizeof(List*) * hash_size);   
    for (int i = 0; i < hash_size; i++)
    {
        new_list_arr[i] = new List(mem);
    }
    size_t size = 0;
    void* elem = nullptr;
    size_t hash_num = 0;
    Container::Iterator* iter = nullptr;
    for (int i = 0; i < prev_hash_size; i++)
    {
        if (!this->list_arr[i]->empty())
        {
            iter = this->list_arr[i]->newIterator(); //удалять
            while (iter->hasNext())
            {
                elem = iter->getElement(size);
                if (elem)
                {
                    hash_num = this->hash_function(elem, size);
                    new_list_arr[hash_num]->push_front(elem, size);
                }
                iter->goToNext();
            }
            this->list_arr[i]->clear();
        }
    }
    for (int i = 0; i < prev_hash_size; i++)
    {
        delete this->list_arr[i];
    }
    _memory.freeMem(this->list_arr);
    this->list_arr = new_list_arr;
    return;
}

Set::~Set()
{
    for (int i = 0; i < this->hash_size; i++)
    {
        delete list_arr[i];
    }
    _memory.freeMem(this->list_arr);
    _CrtDumpMemoryLeaks();
}