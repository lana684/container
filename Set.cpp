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
        this->iter_l = set->list_arr[first_index]->newIterator();
        this->find_end(end_index);
    }
}

/*Set::Iterator::Iterator(Set* set)
{
    this->index = 0;
    this->set = set;
    this->curent = set->list_arr[index];
    try {
        this->iter_l = this->set->list_arr[this->index]->newIterator();
        this->end_i = this->set->hash_size; this->end_i--;
        this->end = set->list_arr[this->end_i]->newIterator();
    }
    catch (List::Error) { printf("Go to next"); }// оптимизация?
}*/

Set::Iterator::~Iterator()
{
    delete this->iter_l;
    delete this->end;
    this->set = NULL;
    this->curent = NULL;
}

void* Set::Iterator::getElement(size_t& size)
{
    return this->iter_l->getElement(size);
}

bool Set::Iterator::hasNext()
{
    size_t hash = this->set->hash_size; hash--;
    int tmp_i = this->index;//re
    int empty = 0;
    if (this->iter_l->hasNext() == true)
        return true;
    else if (this->iter_l->hasNext() == false && this->iter_l != this->end )
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
}

void Set::Iterator::goToNext()
{
    if (this->hasNext() == true)
    {
        if (this->iter_l->hasNext() == false && this->iter_l != this->end)
        {
            int tmp = this->set->hash_size; tmp--;
            while (this->iter_l == NULL || this->index != tmp)
            {
                this->index++; 
                this->iter_l->goToNext();
                this->curent = this->set->list_arr[this->index];
            }
        }
        else if (this->iter_l->hasNext())
        {
            this->iter_l->goToNext();
        }
    }
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

void Set::Iterator::find_end(size_t& indx_end)
{
    int max_indx = this->set->hash_size;
    max_indx--;
    for (int j = max_indx; j >= 0; j--)
    {
        if (!this->set->list_arr[j]->empty())
        {
            indx_end = j;
            size_t size = 0;
            this->end = this->set->list_arr[j]->newIterator();
            if (this->end)
            {
                while (this->end->hasNext()) {
                    this->end->goToNext();
                }
                return;
            }
        }
    }
    return;
}

int Set::size() {
    return this->set_count;
}

size_t Set::max_bytes() {
    return _memory.size();
}

//+- менялся
/*Container::Iterator* Set::find(void* elem, size_t size)
{
    size_t hash = this->hash_function(elem, size);
    Set::Iterator* Iter = dynamic_cast<Set::Iterator*>(this->newIterator());
    if (this->list_arr[hash]->empty() && Iter)
    {
        if (Iter->index != hash) {
            Iter->index = hash;
            Iter->curent = this->list_arr[hash];
        }
        Iter->iter_l = Iter->set->list_arr[hash]->find(elem, size);
        Iter->find_end(Iter->end_i);
        if (Iter->iter_l == nullptr)
        {
            //delete Iter;
            return nullptr;
        }
        else { return Iter; }
    }
}*/

Container::Iterator* Set::find(void* elem, size_t size)
{
    size_t hash = this->hash_function(elem, size);
    // dynamic_cast<тип_в_который_преобразуем>(преобразуемый_объект)
    if (this->list_arr[hash]->empty())
        return nullptr;

    Set::Iterator* Iter = dynamic_cast<Set::Iterator*>(this->newIterator());
    if (Iter->index != hash) {
        Iter->index = hash;
        Iter->curent = this->list_arr[hash];
    }
    Iter->iter_l = Iter->set->list_arr[hash]->find(elem, size);
    //Iter->find_end(Iter->end_i);

    if (Iter->iter_l == nullptr)
    {
        return nullptr;
    }
    else { return Iter; }
}

//менялся
Container::Iterator* Set::newIterator()
{
    if (this->set_count == 0) { return nullptr; }
    else
    {
        Set::Iterator* Iter = new Set::Iterator(this);
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
            if (!this->list_arr[iter1->index]->empty() && this->list_arr[iter1->index]->find(elem, size) != nullptr)
            {
                int flag = 1;
                size_t hash_num = hash_function(elem, size);
                Container::Iterator* tmp_iter = this->list_arr[hash_num]->find(elem, size); //указатель типа лист итератор
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
                }
            }
        }
    }

}

//+- ???
/*void Set::remove(Container::Iterator* iter)
{
    char remove_flg = 1;
    Set::Iterator* iter_s = dynamic_cast<Set::Iterator*>(iter);
    size_t tmp_size = 0;
    void* tmp_elem = iter->getElement(tmp_size);
    size_t hash = hash_function(tmp_elem, tmp_size);
    Set::Iterator* it = dynamic_cast<Set::Iterator*>(this->find(tmp_elem, tmp_size));
    if (it && iter_s)
    {
        if (it->equals(iter) == true)
        {
            if (it->hasNext() == false && it->iter_l->equals(it->end) == true) //если последний элемент последнего непустого списка
            {
                try {
                    this->list_arr[hash]->remove(it->iter_l);
                }
                catch (List::Error)
                {
                    std::cout << "Error";
                }
                remove_flg = 0;
                it->find_end(it->end_i);
            }
            else if (it->hasNext() == true && it->iter_l->hasNext() == false) // последний элемент текущего списка
            {
                iter_s->goToNext();
                this->list_arr[hash]->remove(it->iter_l);
                remove_flg = 0;
            }
            else if (it->iter_l->hasNext() == true) //если  не последний элемент текущего списка
            {
                this->list_arr[hash]->remove(iter_s->iter_l);
                remove_flg = 0;
            }
            if (remove_flg == 0)
            {
                it->set->set_count--;
            }
        }
        if (it != nullptr) { _memory.freeMem(it); } // проверка на пустоту
    }
}*/

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
    try {
        if (hash < this->hash_size)
        {
            if (this->list_arr[hash]->empty() == false)
            {
                iter = this->list_arr[hash]->find(elem, size);
                if (iter == nullptr)
                {
                    result = this->list_arr[hash]->push_front(elem, size);
                }
                else { return -1; }
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
    }
    catch (std::bad_alloc& ba)
    {
        std::cerr << ba.what() << std::endl;
    }
    return -2;
}

//--
size_t Set::hash_function(void* value, size_t valueSize)
{
    if (value)
    {
        /*size_t hash = 0;
        char* k = (char*)value;
        for (int i = 0; i < valueSize; i++)
        {
            hash = (hash << 5) - hash + k[i];
        }*/
        size_t hash = 0;
        char* k = (char*)value;
        for (int i = 0; i < valueSize; i++)
        {
            hash = (hash << 5) - hash + k[i];
            hash ^= (hash << 5) + 1;
        }
        //printf("%d ", hash % this->hash_size);
        return hash % this->hash_size;
        // хэш номер списка, остаток от деления на количество списков
    }
    else
        throw Container::Error("Hash_err");
}

//--
void Set::rehashing(MemoryManager& mem)
{
    size_t prev_hesh_size = hash_size;
    hash_size = 2 * hash_size;
    List** new_list_arr = (List**)_memory.allocMem(sizeof(List*) * hash_size);   
    for (int i = 0; i < hash_size; i++)
    {
        this->list_arr[i] = new List(mem);
    }
    size_t size = 0;
    void* elem = nullptr;
    size_t hash_num = 0;
    Container::Iterator* iter = nullptr;
    for (int i = 0; i < prev_hesh_size; i++)
    {
        if (!this->list_arr[i]->empty())
        {
            iter = this->list_arr[i]->newIterator();
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
    for (int i = 0; i < this->hash_size; i++)
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
        delete this->list_arr[i];
    }
    _memory.freeMem(this->list_arr);
}