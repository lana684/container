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
    this->index = 0;
    this->set = set;
    this->curent = set->list_arr[index];
    this->iter_l = this->set->list_arr[this->index]->newIterator();
    this->end_i = this->set->hash_size; this->end_i--;
    this->end = set->list_arr[this->end_i]->newIterator(); // оптимизация?
}

Set::Iterator::~Iterator()
{
    this->set = NULL;
    this->curent = NULL;
    delete this->iter_l;
    delete this->end;
}

void* Set::Iterator::getElement(size_t& size)
{
    return this->iter_l->getElement(size);
}

bool Set::Iterator::hasNext()
{
    int tmp_i = this->index;
    void* tmp_list = this->curent;
    if (this->iter_l->hasNext() == true)
    {
        return true;
    }
    else if (this->iter_l->hasNext() == false && this->iter_l != this->end )
    {
        while (tmp_list == NULL || tmp_i != this->set->hash_size - 1)
        {
            tmp_i++;
            tmp_list = this->set->list_arr[tmp_i];
        }
        if (tmp_list)
        {
            return true;
        }
        else { return false; }
    }
}

void Set::Iterator::goToNext()
{
    if (this->hasNext() == true)
    {
        if (this->iter_l->hasNext() == false && this->iter_l != this->end)
        {
            while (this->iter_l == NULL || this->index != this->set->hash_size - 1)
            {
                this->index++; 
                this->iter_l->goToNext();
                this->curent = this->set->list_arr[this->index];
            }
        }
        else if (this->iter_l->hasNext() == true)
        {
            this->iter_l->goToNext();
        }
    }
}

// +-
bool Set::Iterator::equals(Container::Iterator* right)
{
    Set::Iterator* iter_r = dynamic_cast<Set::Iterator*>(right);
    if (this->iter_l->equals(iter_r->iter_l) == true)
    {
        return true;
    }
    else { return false; }
}

void Set::Iterator::find_end(size_t& indx_end)
{
    size_t max_indx = this->set->hash_size;
    max_indx--;
    for (size_t j = max_indx; j >= 0; j--)
    {
        if (this->set->list_arr[j] != NULL)
        {
            indx_end = j;
            size_t size = 0;
            void* elem = this->set->list_arr[j]->front(size);
            this->end = this->set->list_arr[j]->find(elem, size);
            return;
        }
    }
    return;
}

/*void Set::Iterator::change_index(int new_indx)
{
    this->index = new_indx;
}
int Set::Iterator::get_index()
{
    return this->index;
}*/

int Set::size() {
    return this->set_size;
}
size_t Set::max_bytes() {
    return _memory.size();
}

//+-
Container::Iterator* Set::find(void* elem, size_t size)
{
    size_t hash = this->hash_function(elem, size);
    // dynamic_cast<тип_в_который_преобразуем>(преобразуемый_объект)
    Set::Iterator* Iter = dynamic_cast<Set::Iterator*>(this->newIterator());//???
    if (Iter->index != hash) {
        Iter->index = hash;
        Iter->curent = this->list_arr[hash];
    }
    Iter->iter_l = Iter->set->list_arr[hash]->find(elem, size);
    Iter->find_end(Iter->end_i);
    if (Iter->iter_l == nullptr)
    {
        delete Iter;
        return nullptr;
    }
    else { return Iter; }
}

Container::Iterator* Set::newIterator()
{
    if (this->set_size == 0) { return nullptr; }
    else
    {
        Set::Iterator* Iter = new Set::Iterator(this);
        return Iter;
    }
}

//--
void Set::remove(Container::Iterator* iter)
{

}
    //приведение типов

//--
void Set::clear()
{
}

bool Set::empty()
{
    if (this->set_size == 0)
    {
        return true;
    }
    else {
        return false;
    }
}

//--
int Set::insert(void* elem, size_t size)
{
    size_t hash = Set::hash_function(elem, size);
    Set::Iterator* iter = new Set::Iterator(this);
    if (Set::empty() == true)
    {
        
        


    }
    else
    {
    }
    return 0;
}

size_t Set::hash_function(void* value, size_t valueSize)
{
    size_t h = 0;

    return h;
}

    // хэш номер списка, остаток от деления на количество списков

