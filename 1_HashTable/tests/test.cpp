#include <gtest/gtest.h>
#include <string>
#include <stdexcept>
#include "../HashTable.h"

class HashTableIntTest : public ::testing::Test {
    protected:
    HashTable<int> emptyHT;
    HashTable<int> ht;
    void SetUp() override {
        emptyHT = HashTable<int>(); // init always empty hash table
        ht = HashTable<int>(); // init main hash table
        for (int i = 0; i < 10; ++i) {
            ht.insert(std::to_string(i), i);
        }
    }
};

TEST_F(HashTableIntTest, IsEmptyInitially) {
    EXPECT_EQ(emptyHT.size(), 0);
    EXPECT_TRUE(emptyHT.empty());
}

TEST_F(HashTableIntTest, InsertWorks) {
    EXPECT_TRUE(emptyHT.insert("0", 0));
    EXPECT_EQ(emptyHT.size(), 1);
    EXPECT_FALSE(emptyHT.empty());
}

TEST_F(HashTableIntTest, InsertContainedWorks) {
    size_t ht_size = ht.size();
    EXPECT_FALSE(ht.insert("0", 0));
    EXPECT_EQ(ht.size(), ht_size);
    EXPECT_FALSE(ht.empty());
}

TEST_F(HashTableIntTest, EqOperatorWorks) {
    EXPECT_EQ(ht, ht);
    HashTable<int> not_equal = ht;
    not_equal.insert("some_key", 0);
    EXPECT_NE(not_equal, ht);
}

TEST_F(HashTableIntTest, CopyConstructorWorks) {
    HashTable<int> copy = HashTable<int>(ht);
    EXPECT_EQ(ht, copy);
}

TEST_F(HashTableIntTest, SwapWorks) {
    HashTable<int> ht_copy = ht;
    HashTable<int> empty_copy = emptyHT;
    ht.swap(emptyHT);
    EXPECT_EQ(ht, empty_copy);
    EXPECT_EQ(emptyHT, ht_copy);
}

TEST_F(HashTableIntTest, ClearWorks) {
    EXPECT_NE(ht.size(), 0);
    ht.clear();
    EXPECT_EQ(ht.size(), 0);
}


TEST_F(HashTableIntTest, ContainsWorks) {
    EXPECT_FALSE(ht.contains("unknown_key"));
    ht.insert("unknown_key", 0);
    EXPECT_TRUE(ht.contains("unknown_key"));
}

TEST_F(HashTableIntTest, EraseWorks) {
    EXPECT_FALSE(ht.contains("key_to_insert"));
    ht.insert("key_to_insert", 0);
    EXPECT_TRUE(ht.contains("key_to_insert"));
    ht.erase("key_to_insert");
    EXPECT_FALSE(ht.contains("key_to_insert"));
}

TEST_F(HashTableIntTest, OperatorAtWorks) {
    EXPECT_EQ(ht["0"], 0);
    ht.insert("key1", 1);
    EXPECT_EQ(ht["key1"], 1);
    EXPECT_EQ(ht["1"]++, 1);
    EXPECT_EQ(++ht["2"], 3);
}
TEST_F(HashTableIntTest, OperatorAtErrorWorks) {
    EXPECT_FALSE(ht.contains("unknown_key"));
    EXPECT_EQ(ht["unknown_key"], int());
    int checker = int();
    EXPECT_EQ(++ht["unknown_key"], ++checker);
}

TEST_F(HashTableIntTest, AtWorks) {
    EXPECT_EQ(ht.at("1"), 1);
    ht.at("1") = -1;
    EXPECT_EQ(ht.at("1"), -1);
}

TEST_F(HashTableIntTest, AtErrorWorks) {
    EXPECT_FALSE(ht.contains("unknown_key"));
    EXPECT_THROW(ht.at("unknown_key"), std::runtime_error);
}

TEST_F(HashTableIntTest, MoveConstructorWorks) {
    HashTable<int> copy = ht;
    HashTable<int> right_copy = HashTable<int>(std::move(ht));
    EXPECT_EQ(right_copy, copy);
    EXPECT_DEATH(ht.insert("any_key", 0), "");
}

TEST_F(HashTableIntTest, MoveOperatorWorks) {
    HashTable<int> copy = ht;
    HashTable<int> right_copy = std::move(ht);
    EXPECT_EQ(right_copy, copy);
    EXPECT_DEATH(ht.insert("any_key", 0), "");
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}