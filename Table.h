#pragma once
#include "TableAbstract.h"
#include "List.h"
#include "Memory_Manager_Table.h"
//#include "Pair.h"

//добавление, поиск, удаление

//one 3
//4 5.9

struct Pair
{
    
public:
    //friend List;
    void* key;
    size_t keySize;
    void* value;
    size_t valueSize;
    Pair(void* k, size_t kSize, void* val, size_t vSize)     
    {
        keySize = kSize; valueSize = vSize;
        void* key = new char[keySize];     //_memory.allocMem(keySize); 
        memcpy(key, k, keySize);
        void* value = new char[valueSize];  //_memory.allocMem(elemSize);
        memcpy(value, val, valueSize);

    }
    /*
    void operator = (const Pair& otherPair)     // присваивание
    {
        keySize = otherPair.keySize;
        valueSize = otherPair.valueSize;
        memcpy(key, otherPair.key, keySize);
        memcpy(value, otherPair.value, valueSize);
    }
    Pair(const Pair& otherPair)               // инициализация
    {
        keySize = otherPair.keySize;
        valueSize = otherPair.valueSize;
        memcpy(key, otherPair.key, keySize);
        memcpy(value, otherPair.value, valueSize);
    }
    */
    ~Pair()
    {
        delete key;
        delete value;

    }
};


class Table: public AbstractTable
{ 
public:
    class Iterator: public  Container::Iterator
    {            
        int index_current_list;  //по индексу обращаемся к определенным спискам массива keys_values
        Table* table; // указатель на наш table, в нем keys_values
        size_t size_table; //max_number_of_lists = 0;

    public:
        Pair* current_elem = nullptr;
        size_t size_current_elem = 0;
        List::Iterator* current_list_iter = nullptr;
        //List::Iterator* next_list_iter = nullptr;


        // Возврашает явно указатель на элемент, на который указывает итератор в данный момент.
        // Неявно возвращает размер данных.
        // Если итератор показывает за пределы контейнера (например, удален последний элемент), возвращает NULL.
        virtual void* getElement(size_t& size) override;

        // Возвращает true, если есть следующий элемент, иначе false.
        virtual bool hasNext() override;

        // Переход к следующему элементу.
        virtual void goToNext() override;

        // проверка на равенство итераторов       
        virtual bool equals(Container::Iterator* right) override;
        friend Table;
        //переопределить Container::Iterator* на Table::Iterator
    };
private:
    //Table::Iterator;
    //Table::Iterator* exist_key(void* key, size_t keySize);
 
    size_t current_number_of_elements = 0;

    friend List;
    //friend TableTest;
public:
    List** keys_values;
    size_t max_number_of_lists = 0;
    List* last_list = nullptr;
    Table(MemoryManager& mem);

    Pair* operator[] (const char* key);

    Pair* operator[] (int key);

    // Функция возвращает значение, равное количеству элементов в контейнере.
    virtual int size() override;

    // Функция возвращает значение, равное максимальной вместимости контейнера в байтах.
    virtual size_t max_bytes() override;

    // Функция создает в динамической памяти итератор, указывающий на первый найденный
    // в контейнере элемент. Если элемент не найден, возвращается пустой указатель.
    // Удаление этого итератора должно делаться пользователем с помощью оператора delete.
    virtual Container::Iterator* find(void* elem, size_t size) override;

    // Функция создает в динамической памяти итератор, указывающий на первый элемент
    // контейнера. Если контейнер пустой, возвращается нулевой указатель.
    // Удаление этого итератора должно делаться пользователем с помощью оператора delete.
    virtual Container::Iterator* newIterator() override;

    // Удаление элемента из позиции, на которую указывает итератор iter.
    // После удаления итератор указывает на следующий за удаленным элемент.
    virtual void remove(Container::Iterator* iter) override;
    //переопределить Container::Iterator* на Table::Iterator

    // Удаление всех элементов из контейнера.
    virtual void clear() override;

    // Если контейнер пуст возвращает true, иначе false
    virtual bool empty() override;

    // Добавление элемента в контейнер, с сответствующим ключом.
    // Если такой ключ уже есть, функция ничего не делает и возвращает 1.
    // В случае успешного добавления функция возвращает значение 0, в случае неудачи 1.
    virtual int insertByKey(void* key, size_t keySize, void* elem, size_t elemSize) override;

    // Удаление элемента с сответствующим ключом из контейнера.
    virtual void removeByKey(void* key, size_t keySize) override;

    // Функция возвращает указатель на итератор, указывающий на найденный в контейнере элемент с сответствующим ключом.
    // Если элемент не найден, возвращается нулевой указатель.
    virtual Container::Iterator* findByKey(void* key, size_t keySize) override;

    // доступ к элементу с ключом key
    virtual void* at(void* key, size_t keySize, size_t& valueSize) override;
    //возвращается структура Pair = key_value

    // хэш функция
    virtual size_t hash_function(void* key, size_t keySize) override;
    //возвращает индекс массива, куда вставлять элемент
    
    //void operator delete(void* MMT, size_t size);
    //void* operator new(size_t size);
    friend Iterator;
    virtual ~Table();

};
