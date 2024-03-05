#pragma once
#include "TableAbstract.h"

class Table: public AbstractTable
{
public:
    Table(MemoryManager& mem) : AbstractTable(mem){}

    class Iterator: public Container::Iterator
    {
    public:
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

    };


    // Функция возвращает значение, равное количеству элементов в контейнере.
    virtual int size() override;

    // Функция возвращает значение, равное максимальной вместимости контейнера в байтах.
    virtual size_t max_bytes() override;

    // Функция создает в динамической памяти итератор, указывающий на первый найденный
    // в контейнере элемент. Если элемент не найден, возвращается пустой указатель.
    // Удаление этого итератора должно делаться пользователем с помощью оператора delete.
    virtual Iterator* find(void* elem, size_t size) override;

    // Функция создает в динамической памяти итератор, указывающий на первый элемент
    // контейнера. Если контейнер пустой, возвращается нулевой указатель.
    // Удаление этого итератора должно делаться пользователем с помощью оператора delete.
    virtual Iterator* newIterator() override;

    // Удаление элемента из позиции, на которую указывает итератор iter.
    // После удаления итератор указывает на следующий за удаленным элемент.
    virtual void remove(Container::Iterator* iter) override;

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
    virtual Iterator* findByKey(void* key, size_t keySize) override;

    // доступ к элементу с ключом key
    virtual void* at(void* key, size_t keySize, size_t& valueSize) override;

    // хэш функция
    virtual size_t hash_function(void* key, size_t keySize) override;
    virtual ~Table(){}

};
