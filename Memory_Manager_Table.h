#pragma once
#include "Table.h"

class Memory_Manager_Table : public Mem
{
    List* last_added_pair;            //указывает на последний добавленный элемент
    double factor = 0.75;
    List** pairs_key_value;
    size_t max_size = 0;                         //максимальный размер массива пар
    //есть size в MemoryManager
    size_t size_free_space = 0;                  //сколько еще можно добавить пар
    //bool checkMemory();
    
public:
    friend Table;
    Memory_Manager_Table(int size);

    /*
    void* create_object(size_t hash)
    {
        last_added_pair+=hash;
        size_free_space--;
        return last_added_pair;
        if (size_free_space > 0)
        {
            //last_added_pair++;
            size_free_space--;
            return last_added_pair;
        }
        else
        {
            return nullptr; //слишком мало места для создания
        }

    }
    void delete_object(int alldelete = 0)
    {
        if (last_added_pair > pairs_key_value)
        {
            last_added_pair--;
            size_free_space++;
        }
        if (alldelete == 1)
        {
            free(pairs_key_value);
        }
    }
    friend Table;
    */
   // void* alloc(size_t hash); //не нужно
    //void free(void* ptr); //не нужно
    void rehash();
    size_t _max_size() { return max_size; }
    ~Memory_Manager_Table();
};
