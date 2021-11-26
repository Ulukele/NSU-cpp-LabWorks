#pragma once
#include <stdexcept>
#include <string>
#include <functional>
#include <list>
#include <vector>

template <class T>
class HashTable;

template <class T>
bool operator==(const HashTable<T>& a, const HashTable<T>& b);
template <class T>
bool operator!=(const HashTable<T>& a, const HashTable<T>& b);

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

    typename Storage::iterator find(const Key& k) const {
        int idx = hash(k) % memorySize;
        for (auto iter = memory[idx].begin(); iter != memory[idx].end(); ++iter) {
            if ((*iter).first == k) {
                return iter;
            }
        }
        throw std::runtime_error("There is no such key");
    }

    public:

    HashTable() {
        memorySize = 1000;
        actualSize = 0;
        memory = new HashTable<T>::Storage[memorySize];
    }

    ~HashTable() {
        delete[] memory;
    }

    HashTable(const HashTable<T>& b)
            : memorySize(b.memorySize), actualSize(b.actualSize) {
        memory = new HashTable<T>::Storage[b.memorySize];
        for (int i = 0; i < b.memorySize; ++i) {
            memory[i] = HashTable<T>::Storage(b.memory[i]);
        }
    }

    HashTable(HashTable<T>&& b) noexcept
            : memorySize(b.memorySize), actualSize(b.actualSize)  {
        memory = b.memory;
        b.memory = nullptr;
        b.actualSize = 0;
    }

    HashTable<T>& operator=(const HashTable<T>& b) {
        if (&b != this) {
            memorySize = b.memorySize;
            actualSize = b.actualSize;
            delete[] memory;
            memory = new HashTable<T>::Storage[b.memorySize];
            for (int i = 0; i < b.memorySize; ++i) {
                memory[i] = HashTable<T>::Storage(b.memory[i]);
            }

        }
        return *this;
    }

    HashTable<T>& operator=(HashTable<T>&& b) noexcept {
        memorySize = b.memorySize;
        actualSize = b.actualSize;
        memory = b.memory;
        b.memory = nullptr;

        return *this;
    }

    void swap(HashTable<T>& b) {
        std::swap(memorySize, b.memorySize);
        std::swap(actualSize, b.actualSize);
        std::swap(memory, b.memory);
    }

    void clear() {
        for (int i = 0; i < memorySize; ++i) {
            memory[i].clear();
        }
        actualSize = 0;
    }

    bool erase(const Key& k) {
        int idx = hash(k) % memorySize;
        if ( !contains(k) ) {
            return false;
        }
        auto iter = find(k);
        memory[idx].erase(iter);
        actualSize -= 1;
        return true;
    }

    bool insert(const Key& k, const Value& v) {
        int idx = hash(k) % memorySize;
        if ( contains(k) ) {
            return false;
        }
        memory[idx].push_back(Node(k, v));
        actualSize += 1;
        return true;
    }

    bool contains(const Key& k) const {
        int idx = hash(k) % memorySize;
        for (auto iter = memory[idx].begin(); iter != memory[idx].end(); ++iter) {
            if (iter->first == k) {
                return true;
            }
        }
        return false;
    }

    Value& operator[](const Key& k) {

        if ( !contains(k) ) {
            insert(k, T());
        }
        typename HashTable<T>::Storage::iterator iter = find(k);
        return iter->second;
    }

    Value& at(const Key& k) {
        if ( !contains(k) ) {
            throw std::runtime_error("There is no such key");
        }
        typename HashTable<T>::Storage::iterator iter = find(k);
        return iter->second;
    }

    const Value& at(const Key& k) const {
        if ( !contains(k) ) {
            throw std::runtime_error("There is no such key");
        }
        typename HashTable<T>::Storage::iterator iter = find(k);
        return iter->second;
    }

    size_t size() const {
        return actualSize;
    }

    bool empty() const {
        return  (actualSize == 0);
    }

    friend bool operator==<T>(const HashTable& a, const HashTable& b);
    friend bool operator!=<T>(const HashTable& a, const HashTable& b);
};

template <class T>
bool operator==(const HashTable<T>& a, const HashTable<T>& b) {
    for (int i = 0; i < a.memorySize; ++i) {
        for (const auto& key_value : a.memory[i]) {
            if (!b.contains(key_value.first)) {
                return false;
            }
            if (b.at(key_value.first) != key_value.second) {
                return false;
            }
        }
    }
    for (int i = 0; i < b.memorySize; ++i) {
        for (const auto& key_value : b.memory[i]) {
            if (!a.contains(key_value.first)) {
                return false;
            }
            if (a.at(key_value.first) != key_value.second) {
                return false;
            }
        }
    }
    return true;
}

template <class T>
bool operator!=(const HashTable<T>& a, const HashTable<T>& b) {
    return !(a == b);
}
