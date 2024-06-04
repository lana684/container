#pragma once
#include "TableAbstract.h"
#include "List.h"
#include "Memory_Manager_Table.h"
//#include "Pair.h"

//����������, �����, ��������

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
    void operator = (const Pair& otherPair)     // ������������
    {
        keySize = otherPair.keySize;
        valueSize = otherPair.valueSize;
        memcpy(key, otherPair.key, keySize);
        memcpy(value, otherPair.value, valueSize);
    }
    Pair(const Pair& otherPair)               // �������������
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
        int index_current_list;  //�� ������� ���������� � ������������ ������� ������� keys_values
        Table* table; // ��������� �� ��� table, � ��� keys_values
        size_t size_table; //max_number_of_lists = 0;

    public:
        Pair* current_elem = nullptr;
        size_t size_current_elem = 0;
        List::Iterator* current_list_iter = nullptr;
        //List::Iterator* next_list_iter = nullptr;


        // ���������� ���� ��������� �� �������, �� ������� ��������� �������� � ������ ������.
        // ������ ���������� ������ ������.
        // ���� �������� ���������� �� ������� ���������� (��������, ������ ��������� �������), ���������� NULL.
        virtual void* getElement(size_t& size) override;

        // ���������� true, ���� ���� ��������� �������, ����� false.
        virtual bool hasNext() override;

        // ������� � ���������� ��������.
        virtual void goToNext() override;

        // �������� �� ��������� ����������       
        virtual bool equals(Container::Iterator* right) override;
        friend Table;
        //�������������� Container::Iterator* �� Table::Iterator
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

    // ������� ���������� ��������, ������ ���������� ��������� � ����������.
    virtual int size() override;

    // ������� ���������� ��������, ������ ������������ ����������� ���������� � ������.
    virtual size_t max_bytes() override;

    // ������� ������� � ������������ ������ ��������, ����������� �� ������ ���������
    // � ���������� �������. ���� ������� �� ������, ������������ ������ ���������.
    // �������� ����� ��������� ������ �������� ������������� � ������� ��������� delete.
    virtual Container::Iterator* find(void* elem, size_t size) override;

    // ������� ������� � ������������ ������ ��������, ����������� �� ������ �������
    // ����������. ���� ��������� ������, ������������ ������� ���������.
    // �������� ����� ��������� ������ �������� ������������� � ������� ��������� delete.
    virtual Container::Iterator* newIterator() override;

    // �������� �������� �� �������, �� ������� ��������� �������� iter.
    // ����� �������� �������� ��������� �� ��������� �� ��������� �������.
    virtual void remove(Container::Iterator* iter) override;
    //�������������� Container::Iterator* �� Table::Iterator

    // �������� ���� ��������� �� ����������.
    virtual void clear() override;

    // ���� ��������� ���� ���������� true, ����� false
    virtual bool empty() override;

    // ���������� �������� � ���������, � �������������� ������.
    // ���� ����� ���� ��� ����, ������� ������ �� ������ � ���������� 1.
    // � ������ ��������� ���������� ������� ���������� �������� 0, � ������ ������� 1.
    virtual int insertByKey(void* key, size_t keySize, void* elem, size_t elemSize) override;

    // �������� �������� � �������������� ������ �� ����������.
    virtual void removeByKey(void* key, size_t keySize) override;

    // ������� ���������� ��������� �� ��������, ����������� �� ��������� � ���������� ������� � �������������� ������.
    // ���� ������� �� ������, ������������ ������� ���������.
    virtual Container::Iterator* findByKey(void* key, size_t keySize) override;

    // ������ � �������� � ������ key
    virtual void* at(void* key, size_t keySize, size_t& valueSize) override;
    //������������ ��������� Pair = key_value

    // ��� �������
    virtual size_t hash_function(void* key, size_t keySize) override;
    //���������� ������ �������, ���� ��������� �������
    
    //void operator delete(void* MMT, size_t size);
    //void* operator new(size_t size);
    friend Iterator;
    virtual ~Table();

};
