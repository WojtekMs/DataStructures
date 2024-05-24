#include <gtest/gtest.h>
#include "Trie.hpp"
#include <vector>
#include <string> 

class TrieTest : public testing::Test
{
protected:
    Trie trieSut;
};

TEST_F(TrieTest, GivenInsertedWord_WhenWordExistsCalled_ThenReturnTrue)
{
    trieSut.insertWord("word");

    ASSERT_TRUE(trieSut.wordExists("word"));
}

TEST_F(TrieTest, GivenNotInsertedWord_WhenWordExistsCalled_ThenReturnFalse)
{
    trieSut.insertWord("word");

    ASSERT_FALSE(trieSut.wordExists("wor"));
}

TEST_F(TrieTest, GivenInsertedWords_WhenFindWordsWithPrefixCalled_ThenReturnWords)
{
    std::vector<std::string> words{"do", "don", "donald", "dock", "doom", "house", "hen", "chicken"};
    for (const auto & word : words) {
        trieSut.insertWord(word);
    }
    std::vector<std::string> expectedWords{"dock", "don", "donald", "doom", "do"};

    const auto actualWords = trieSut.findWordsWithPrefix("do");

    ASSERT_EQ(actualWords, expectedWords);
}