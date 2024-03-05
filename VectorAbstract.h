#pragma once
#include "GroupContainer.h"

// Абстрактный класс: вектор
class AbstractVector: public GroupContainer
{
public:
    // конструктор
    AbstractVector(MemoryManager &mem): GroupContainer(mem) {}

    // деструктор
    virtual ~AbstractVector() {}

    // Добавление элемента в конец контейнера.
    // В случае успешного добавления функция возвращает значение 0, в случае неудачи 1.
    virtual int push_back(void *elem, size_t elemSize) = 0;

    // Удаление элемента из конца контейнера.
    virtual void pop_back() = 0;

    // Функция явно возвращает указатель на элемент, находящийся в начале контейнера.
    // и неявно возвращает размер данных
    virtual void* front(size_t &size) = 0;

    // Функция явно возвращает указатель на элемент, находящийся в конеце контейнера.
    // и неявно возвращает размер данных
    virtual void* back(size_t &size) = 0;

    // доступ к элементу с индексом i
    // Возврашает явно указатель на элемент.
    // Неявно возвращает размер данных
    virtual void* at(size_t i, size_t &size) = 0;

    // Добавление элемента в позицию, на которую указывает итератор iter.
    // В случае успешного добавления функция возвращает значение 0, в случае неудачи 1.
    virtual int insert(Iterator *iter, void *elem, size_t elemSize) = 0;
};
