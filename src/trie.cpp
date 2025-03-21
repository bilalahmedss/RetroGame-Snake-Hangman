#include <map>
#include <memory>
#include <string>
#include "trie.h"

Trie::Trie() : root(std::make_shared<TrieNode>()) {}
void Trie::insert(const std::string& word) {
        std::shared_ptr<TrieNode> currentNode = root;
        for (size_t i = 0; i < word.length(); ) {
            bool found = false;
            for (auto& child : currentNode->children) {
                if (word.substr(i, 1) == child.first.substr(0, 1)) {
                    // Find the longest common prefix
                    size_t j = 0;
                    while (j < child.first.length() && i + j < word.length() && word[i + j] == child.first[j]) {
                        j++;
                    }
                    if (j == child.first.length()) {
                        // Full match with the edge label, move down the trie
                        currentNode = child.second;
                        i += j;
                        found = true;
                        break;
                    } else {
                        // Partial match, split the edge
                        std::string commonPrefix = child.first.substr(0, j);
                        std::string remainingEdge = child.first.substr(j);
                        std::string remainingWord = word.substr(i + j);

                        auto newNode = std::make_shared<TrieNode>();
                        newNode->children[remainingEdge] = child.second;

                        if (!remainingWord.empty()) {
                            newNode->children[remainingWord] = std::make_shared<TrieNode>();
                            newNode->children[remainingWord]->isEndOfWord = true;
                        }

                        currentNode->children[commonPrefix] = newNode;
                        currentNode->children.erase(child.first);
                        found = true;
                        break;
                    }
                }
            }
            if (!found) {
                currentNode->children[word.substr(i)] = std::make_shared<TrieNode>();
                break;
            }
        }
    }

std::string Trie::getRandomWord() {
    std::string word;
    auto node = root;
    while (!node->children.empty()) {
        int count = node->children.size();
        int choice = rand() % count; // Choose a random child
        
        auto it = node->children.begin();
        std::advance(it, choice); // Advance iterator to the chosen child
        
        word += it->first; // Append the string of the chosen path
        node = it->second; // Move to the chosen node
        
        if (node->isEndOfWord && (rand() % 2 == 0 || node->children.empty())) { // Randomly decide to stop if it's a valid word
            break;
        }
    }
    return word;
}

bool Trie::removeHelper(std::shared_ptr<TrieNode>& node, const std::string& word, size_t depth) {
    if (node == nullptr) {
        return false;
    }

    // When the end of the word is reached
    if (depth == word.size()) {
        // If the word is not actually a word in the trie
        if (!node->isEndOfWord) {
            return false;
        }

        // Unmark the end of word and check if node has no children
        node->isEndOfWord = false;
        return node->children.empty();
    }

    // If not the end of the word, recursively call delete for the child
    char ch = word[depth];
    auto it = node->children.find(word.substr(depth));
    if (it == node->children.end()) {
        return false; // The word doesn't exist
    }

    bool shouldDeleteChildNode = removeHelper(it->second, word, depth + 1);

    // If true is returned and the child node is not the end of a word
    if (shouldDeleteChildNode) {
        node->children.erase(it);
        // Return true if no children left in the node and it is not the end of a word
        return node->children.empty() && !node->isEndOfWord;
    }

    return false;
}

bool Trie::remove(const std::string& word) {
    return removeHelper(root, word, 0);
}

