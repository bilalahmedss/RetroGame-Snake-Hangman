#ifndef TRIE_H
#define TRIE_H

#include <map>
#include <memory>
#include <string>

class TrieNode {
public:
    TrieNode() : isEndOfWord(false) {}
    std::map<std::string, std::shared_ptr<TrieNode>> children;
    bool isEndOfWord;
};

class Trie {
public:
    Trie();
    void insert(const std::string& word);
    std::string getRandomWord();
    bool remove(const std::string& word);
private:
    std::shared_ptr<TrieNode> root;
    bool removeHelper(std::shared_ptr<TrieNode>& node, const std::string& word, size_t depth);
};

#endif // TRIE_H
