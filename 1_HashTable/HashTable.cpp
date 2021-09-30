#include "HashTable.h"
#include <stdexcept>
#include <string>

template <class T>
typename HashTable<T>::Storage::iterator HashTable<T>::find(const Key& k) const {
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
HashTable<T>::HashTable(const HashTable<T>& b)
    : memorySize(b.memorySize), actualSize(b.actualSize) {
    memory = new HashTable<T>::Storage[b.memorySize];
    for (int i = 0; i < b.memorySize; ++i) {
        memory[i] = HashTable<T>::Storage(b.memory[i]);
    }
}

template <class T>
HashTable<T>::HashTable(HashTable<T>&& b) noexcept
    : memorySize(b.memorySize), actualSize(b.actualSize)  {
    memory = b.memory;
    b.memory = nullptr;
    b.actualSize = 0;
}

template <class T>
HashTable<T>& HashTable<T>::operator=(const HashTable<T>& b) {
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

template <class T>
HashTable<T>& HashTable<T>::operator=(HashTable<T>&& b) noexcept {
    memorySize = b.memorySize;
    actualSize = b.actualSize;
    memory = b.memory;
    b.memory = nullptr;

    return *this;
}

template <class T>
void HashTable<T>::swap(HashTable<T>& b) {
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
    if ( !contains(k) ) {
        throw std::runtime_error("There is no such key");
    }
    typename HashTable<T>::Storage::iterator iter = find(k);
    return iter->second;
}

template <class T>
const typename HashTable<T>::Value& HashTable<T>::at(const Key& k) const {
    if ( !contains(k) ) {
        throw std::runtime_error("There is no such key");
    }
    typename HashTable<T>::Storage::iterator iter = find(k);
    return iter->second;
}

template <class T>
size_t HashTable<T>::size() const {
    return actualSize;
}

template <class T>
bool HashTable<T>::empty() const {
    return  (actualSize == 0);
}

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
template bool operator==<int>(const HashTable<int>& a, const HashTable<int>& b);
template bool operator==<std::string>(const HashTable<std::string>& a, const HashTable<std::string>& b);

template <class T>
bool operator!=(const HashTable<T>& a, const HashTable<T>& b) {
    return !(a == b);
}
template bool operator!=<int>(const HashTable<int>& a, const HashTable<int>& b);
template bool operator!=<std::string>(const HashTable<std::string>& a, const HashTable<std::string>& b);