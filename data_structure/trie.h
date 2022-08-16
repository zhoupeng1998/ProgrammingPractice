#ifndef TRIE_H_
#define TRIE_H_

#include <string>
#include <vector>

namespace ZP {

struct TrieNode {

    std::vector<TrieNode*> children;
    bool end;

    TrieNode();

};

class Trie {

    TrieNode* root;

public:
    Trie();
    ~Trie();

    void insert(std::string& str);
    bool contains(const std::string& str);

};

}

#endif