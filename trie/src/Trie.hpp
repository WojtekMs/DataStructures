#include <memory>
#include <array>
#include <string_view>
#include <vector>
#include <string> 

class Trie;

class TrieNode
{
    friend Trie;

public:
    constexpr static int charsInAlphabet = 26;

    TrieNode() = default;

private:
    std::array<std::unique_ptr<TrieNode>, charsInAlphabet> children_;
    bool wordEnd_ = false;
};

class Trie
{
public:
    Trie() = default;

    void insertWord(std::string_view word);
    bool wordExists(std::string_view word) const;
    // O(N*L), where N is the number of words in Trie, L is the length of the longest word
    std::vector<std::string> findWordsWithPrefix(std::string_view prefix) const;

private:
    std::vector<std::string> scanChildrenForPrefix(const TrieNode* node, const std::string& prefix) const;

    TrieNode root_;
};