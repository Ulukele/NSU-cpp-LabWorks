#include "HashTable.h"
#include <stdexcept>

template <class T>
typename HashTable<T>::Storage::iterator HashTable<T>::find(const Key& k) {
    int idx = hash(k) % memorySize;
    for (auto iter = memory[idx].begin(); iter != memory[idx].end(); ++iter) {
        if ((*iter).first == k) {
            return iter;
        }
    }
    throw std::runtime_error("There is no such key");
}

template <class T>
HashTable<T>::HashTable() {
    memorySize = 1000;
    actualSize = 0;
    memory = new HashTable<T>::Storage[memorySize];
}


template <class T>
HashTable<T>::~HashTable() {
    delete[] memory;
}

template <class T>
HashTable<T>::HashTable(const HashTable& b) 
    : memorySize(b.memorySize), actualSize(b.actualSize) {
    memory = new HashTable<T>::Storage(*b.memory);
}

template <class T>
HashTable<T>::HashTable(HashTable&& b) noexcept
    : memorySize(b.memorySize), actualSize(b.actualSize)  {
    memory = b.memory;
    b.memory = nullptr;
}

template <class T>
HashTable<T>& HashTable<T>::operator=(const HashTable& b) {
    if (&b != this) {
        memorySize = b.memorySize;
        actualSize = b.actualSize;
        delete[] memory;
        memory = new HashTable<T>::Storage(*b.memory);
    }
    return *this;
}

template <class T>
HashTable<T>& HashTable<T>::operator=(HashTable&& b) noexcept {
    memorySize = b.memorySize;
    actualSize = b.actualSize;
    memory = b.memory;
    b.memory = nullptr;

    return *this;
}

template <class T>
void HashTable<T>::swap(HashTable& b) {
    std::swap(memorySize, b.memorySize);
    std::swap(actualSize, b.actualSize);
    std::swap(memory, b.memory);
}

template <class T>
void HashTable<T>::clear() {
    for (int i = 0; i < memorySize; ++i) {
        memory[i].clear();
    }
    actualSize = 0;
}

template <class T>
bool HashTable<T>::erase(const Key& k) {
    int idx = hash(k) % memorySize;
    if ( !contains(k) ) {
        return false;
    }
    auto iter = find(k);
    memory[idx].erase(iter);
    actualSize -= 1;
    return true;
}

template <class T>
bool HashTable<T>::insert(const Key& k, const Value& v) {
    int idx = hash(k) % memorySize;
    if ( contains(k) ) {
        return false;
    }
    memory[idx].push_back(Node(k, v));
    actualSize += 1;
    return true;
}

template <class T>
bool HashTable<T>::contains(const Key& k) const {
    int idx = hash(k) % memorySize;
    for (auto iter = memory[idx].begin(); iter != memory[idx].end(); ++iter) {
        if (iter->first == k) {
            return true;
        }
    }
    return false;
}

template <class T>
typename HashTable<T>::Value& HashTable<T>::operator[](const Key& k) {

    if ( !contains(k) ) {
        insert(k, T());
    }
    typename HashTable<T>::Storage::iterator iter = find(k);
    return iter->second;
}

template <class T>
typename HashTable<T>::Value& HashTable<T>::at(const Key& k) {
    typename HashTable<T>::Storage::iterator iter = find(k);
    return iter->second;
}

template <class T>
const typename HashTable<T>::Value& HashTable<T>::at(const Key& k) const {
    int idx = hash(k) % memorySize;
    for (auto iter = memory[idx].begin(); iter != memory[idx].end(); ++iter) {
        if ((*iter).first == k) {
            return iter->second;
        }
    }
    throw std::runtime_error("There is no such key");
}

template <class T>
size_t HashTable<T>::size() const {
    return actualSize;
}

template <class T>
bool HashTable<T>::empty() const {
    return  (actualSize == 0);
}