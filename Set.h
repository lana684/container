#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "List.h"
#include "Mem.h"
#include "SetAbstract.h"

using namespace std;

class Set :public AbstractSet {
    size_t set_count;
    int hash_size;
    List** list_arr; //List* -тип, * массив списков
    public:
    Set(MemoryManager &mem, int hash_size) :AbstractSet(mem) {
        this->set_count = 0;
        this->hash_size = hash_size;
        this->list_arr = (List**)_memory.allocMem(sizeof(List*) * hash_size);
        
        //this->list_arr = (List**)malloc(sizeof(List*) * hash_size);
        
        
        for (int i = 0; i < hash_size; i++)
        {
            //this->list_arr[i] = (List*)malloc(sizeof(List));
            this->list_arr[i] = new List(mem);
        }
    }

    class Iterator : public Container::Iterator
    {
        Set* set;
        size_t index;
        void *curent; //head 
        size_t end_i;
        Container::Iterator* end;
        //List::Iterator *end;
        Container::Iterator* iter_l;
        //List::Iterator* iter_l; // указатель на итератор списка 0
    public:
        Iterator(Set* set);
        // Возврашает явно указатель на элемент, на который указывает итератор в данный момент.
        // Неявно возвращает размер данных.
        void* getElement(size_t& size);
        // Возвращает true, если есть следующий элемент, иначе false.
        bool hasNext();
        // Переход к следующему элементу.
        void goToNext();
        // проверка на равенство итераторов
        bool equals(Container::Iterator* right);
        // Возвращает неявно индекс последнего заполненого листа. 
        // Перемещает указатель конца на последний элемент этого списка.
        // Явно возращает 1 в случае успеха и 0 неудачи.
        void find_end(size_t &index_end);

        friend class Set;
        ~Iterator();
    };

    class Error //класс вывода ошибок
    {
    public:
        char msg[256];
        Error(const char* err_msg)
        {
            strcpy(msg, err_msg);
            cout << msg << endl; //вывод этого сообщения 
        }
    };

    int size() override;
    size_t max_bytes() override;
    Container::Iterator* find(void *elem, size_t size) override;
    Container::Iterator* newIterator() override;
    void remove(Container::Iterator *iter) override;
    void clear() override;
    bool empty() override;


    // Добавление элемента в контейнер в соответствующую позицию, в соответствии с выбором реализации множества.
    // В случае успешного добавления функция возвращает значение 0, если такой элемент уже есть в контейнере - 1, во всех остальных случаях - 2.
    int insert(void *elem, size_t size) override;

    // вынести в общий
    size_t hash_function(void* key_or_value, size_t key_or_value_Size);

    void rehashing(MemoryManager& mem);

    ~Set();
    friend class Set::Iterator;
};