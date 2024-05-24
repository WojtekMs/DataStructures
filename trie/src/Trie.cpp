#include "Trie.hpp"

#include <iostream>
#include <algorithm>

std::vector<std::string> Trie::scanChildrenForPrefix(const TrieNode* node, const std::string& prefix) const {
    std::vector<std::string> results{};
    for (int i = 0; i < node->children_.size(); ++i) {
        const TrieNode* child = node->children_[i].get();
        if (child) {
            std::string newPrefix{prefix + static_cast<char>('a' + i)};
            if (child->wordEnd_) {
                results.push_back(newPrefix);
            }
            auto scannedWords = scanChildrenForPrefix(child, newPrefix);
            std::ranges::move(scannedWords, std::back_inserter(results));
        }
    }
    return results;
};

void Trie::insertWord(std::string_view word)
{
    if (word.length() <= 0)
    {
        return;
    }
    TrieNode *currentNode = &root_;
    for (const char character : word)
    {
        std::unique_ptr<TrieNode> &characterNode = currentNode->children_[character - 'a'];
        if (!characterNode)
        {
            characterNode = std::make_unique<TrieNode>();
        }
        currentNode = characterNode.get();
    }
    currentNode->wordEnd_ = true;
}

bool Trie::wordExists(std::string_view word) const
{
    const TrieNode *currentNode = &root_;
    for (const char character : word)
    {
        const std::unique_ptr<TrieNode> &characterNode = currentNode->children_[character - 'a'];
        if (!characterNode)
        {
            return false;
        }
        currentNode = characterNode.get();
    }
    return currentNode->wordEnd_;
}

std::vector<std::string> Trie::findWordsWithPrefix(std::string_view prefix) const
{
    const TrieNode *currentNode = &root_;
    for (const char character : prefix)
    {
        const std::unique_ptr<TrieNode> &characterNode = currentNode->children_[character - 'a'];
        if (!characterNode)
        {
            return {};
        }
        currentNode = characterNode.get();
    }
    std::vector<std::string> results;
    if (currentNode->wordEnd_) {
        results.emplace_back(prefix);
    }
    auto childrenWords = scanChildrenForPrefix(currentNode, std::string(prefix));
    std::ranges::move(results, std::back_inserter(childrenWords));
    return childrenWords;
}
