// A implmentation of TrieNode adapted from https://www.geeksforgeeks.org/trie-insert-and-search/
// Author: Jeanniton Monero
// email: jeanniton.mnr@gmail.com
// website: jeanniton.me


#ifndef TRIENODE_H
#define TRIENODE_H

// Representation of a TrieNode
typedef struct TrieNode {
    // The children of this node
    struct TrieNode children[INDEX_SIZE];
    // isEndOfWord is true if this node is the last char of a key/word
    bool isEndOfWord;
} TrieNode;



// Prototypes
struct TrieNode *getNode();
int getCharIndex(char a);
void insert(TrieNode *root, const char *key);
bool isInTrieNode(TrieNode *root, const char *key);

#endif // TRIENODE_H