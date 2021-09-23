#pragma once
#include <string>
#include <functional>
#include <list>

template <class T>

class HashTable {
    typedef std::string Key;
    typedef T Value;
    typedef std::pair<Key, Value> Node;
    typedef std::list< Node > Storage;

    int memorySize;
    size_t actualSize;
    Storage* memory;

    std::hash<Key> hash;

    typename Storage::iterator find(const Key& k);

    public:

    HashTable();
    ~HashTable();

    HashTable(const HashTable& b);
    HashTable(HashTable&& b) noexcept;


    HashTable& operator=(const HashTable& b);
    HashTable& operator=(HashTable&& b) noexcept;


    // Обменивает значения двух хэш-таблиц.
    void swap(HashTable& b);

    // Очищает контейнер.
    void clear();
    // Удаляет элемент по заданному ключу.
    bool erase(const Key& k);
    // Вставка в контейнер. Возвращаемое значение - успешность вставки.
    bool insert(const Key& k, const Value& v);

    // Проверка наличия значения по заданному ключу.
    bool contains(const Key& k) const;

    // Возвращает значение по ключу. Небезопасный метод.
    // В случае отсутствия ключа в контейнере, следует вставить в контейнер
    // значение, созданное конструктором по умолчанию и вернуть ссылку на него.
    Value& operator[](const Key& k);

    // Возвращает значение по ключу. Бросает исключение при неудаче.
    Value& at(const Key& k);
    const Value& at(const Key& k) const;

    size_t size() const;
    bool empty() const;

    // friend bool operator==(const HashTable& a, const HashTable& b);
    // friend bool operator!=(const HashTable& a, const HashTable& b);
};

template class HashTable<int>;
template class HashTable<std::string>;
