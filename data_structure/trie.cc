#include "trie.h"

namespace ZP {

TrieNode::TrieNode()
: children(std::vector<TrieNode*>(26, nullptr)), end(false) {}

Trie::Trie()
: root(new TrieNode()) {}

Trie::~Trie() {

}

void Trie::insert(std::string& str) {
    TrieNode* node = root;
    for (int i = 0; i < str.size(); i++) {
        if (node->children[str[i] - 'a'] == nullptr) {
            node->children[str[i] - 'a'] = new TrieNode();
        }
        node = node->children[str[i] - 'a'];
    }
    node->end = true;
}

bool Trie::contains(const std::string& str) {
    TrieNode* node = root;
    for (int i = 0; i < str.size(); i++) {
        if (node->children[str[i] - 'a'] == nullptr) {
            return false;
        }
        node = node->children[str[i] - 'a'];
    }
    return node->end == true;
}

}