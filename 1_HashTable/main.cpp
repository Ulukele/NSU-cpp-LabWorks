#include <iostream>
#include "HashTable.h"
#include <string>

int main() {

    std::cout << "Start work with Hash table | <int>" << std::endl;

    std::cout << "Create HT with constructor | <int>" << std::endl;
    HashTable<int> ht;

    std::string keys[] = {"Alice", "Bob", "Clare"};

    std::cout << "HT empty=" << ht.empty() << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::cout << "Check HT contains (" << keys[i] << ", " << i << ") is " << ht.contains(keys[i]) << std::endl;
        std::cout << "HT insert(" << keys[i] << ", " << i << ")" << std::endl;
        ht.insert(keys[i], i);
        std::cout << "Check HT contains (" << keys[i] << ", " << i << ") is " << ht.contains(keys[i]) << std::endl;
        std::cout << "HT size is: " << ht.size() << std::endl;
    }
    std::cout << "HT empty=" << ht.empty() << std::endl;


    std::string keyToRemove = "Bob";
    std::cout << "Try to erase key: " << keyToRemove << " result: " << ht.erase(keyToRemove) << std::endl;
    std::cout << "HT size is: " << ht.size() << std::endl;

    std::cout << "Try to erase that key again: " << keyToRemove << " result: " << ht.erase(keyToRemove) << std::endl;
    std::cout << "HT size is: " << ht.size() << std::endl;

    std::string testKey = "Alice";
    std::cout << "Try to get access to element by [" << testKey << "], result: " << ht[testKey] << std::endl;
    std::cout << "HT size is: " << ht.size() << std::endl;

    std::string unknown = "Unknown";
    std::cout << "Try to get access to element by [" << unknown << "], result: " << ht[unknown] << std::endl;
    std::cout << "HT size is: " << ht.size() << std::endl;

    std::cout << "Try to change value (+ 10) by [" << unknown << "], result: ";
    ht[unknown] += 10;
    std::cout << ht[unknown] << std::endl;
    std::cout << "HT size is: " << ht.size() << std::endl;

    std::string existing = "Clare";
    std::cout << "Try to get access to existing with key: " << existing << " result: " << ht.at(existing) << std::endl;

    std::string notExist = "NotExist";
    try {
        std::cout << "Try to get access to not existing with key: " << notExist << " result: ";
        ht.at(notExist);
        std::cout << "Success" << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cout << "Failed with message '" << e.what() << "'" << std::endl;
    };

    std::cout << "Create new (with copying constructor)" << std::endl;
    HashTable<int> copied(ht);
    copied.insert("Copied", -1);

    std::cout << "HT contains : " << ht.contains("Copied") << std::endl;
    std::cout << "copied contains : " << copied.contains("Copied") << std::endl;

    std::cout << "Do swap between HT and copied" << std::endl;
    ht.swap(copied);
    std::cout << "(after swap) HT contains : " << ht.contains("Copied") << std::endl;
    std::cout << "(after swap) copied contains : " << copied.contains("Copied") << std::endl;

    std::cout << "Do swap back between HT and copied" << std::endl;
    ht.swap(copied);
    std::cout << "(after swap back) HT contains : " << ht.contains("Copied") << std::endl;
    std::cout << "(after swap back) copied contains : " << copied.contains("Copied") << std::endl;

    std::cout << "Copy HT to copied" << std::endl;
    copied = ht;

    std::cout << "HT contains : " << ht.contains("Copied") << std::endl;
    std::cout << "copied contains : " << copied.contains("Copied") << std::endl;

    std::cout << "Clear HT. ";
    ht.clear();
    std::cout << "HT size: " << ht.size() << std::endl;
    std::cout << "copied size: " << copied.size() << std::endl;

    std::cout << "Compare HT == copied, result: " << (ht == copied) << std::endl;
    std::cout << "Compare HT != copied, result: " << (ht != copied) << std::endl;

    std::cout << "Call ht = copied" << std::endl;
    ht = copied;
    std::cout << "Compare HT == copied, result: " << (ht == copied) << std::endl;
    std::cout << "Compare HT != copied, result: " << (ht != copied) << std::endl;

    std::cout << "End work with Hash Table | <int>" << std::endl;
    
    return 0;
}