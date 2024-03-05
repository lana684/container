#pragma once
#include "TableAbstract.h"

class Table: public AbstractTable
{
public:
    Table(MemoryManager& mem) : AbstractTable(mem){}

    class Iterator: public Container::Iterator
    {
    public:
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

    };


    // ������� ���������� ��������, ������ ���������� ��������� � ����������.
    virtual int size() override;

    // ������� ���������� ��������, ������ ������������ ����������� ���������� � ������.
    virtual size_t max_bytes() override;

    // ������� ������� � ������������ ������ ��������, ����������� �� ������ ���������
    // � ���������� �������. ���� ������� �� ������, ������������ ������ ���������.
    // �������� ����� ��������� ������ �������� ������������� � ������� ��������� delete.
    virtual Iterator* find(void* elem, size_t size) override;

    // ������� ������� � ������������ ������ ��������, ����������� �� ������ �������
    // ����������. ���� ��������� ������, ������������ ������� ���������.
    // �������� ����� ��������� ������ �������� ������������� � ������� ��������� delete.
    virtual Iterator* newIterator() override;

    // �������� �������� �� �������, �� ������� ��������� �������� iter.
    // ����� �������� �������� ��������� �� ��������� �� ��������� �������.
    virtual void remove(Container::Iterator* iter) override;

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
    virtual Iterator* findByKey(void* key, size_t keySize) override;

    // ������ � �������� � ������ key
    virtual void* at(void* key, size_t keySize, size_t& valueSize) override;

    // ��� �������
    virtual size_t hash_function(void* key, size_t keySize) override;
    virtual ~Table(){}

};
