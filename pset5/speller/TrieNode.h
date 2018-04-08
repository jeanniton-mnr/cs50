// A implmentation of TrieNode adapted from https://www.geeksforgeeks.org/trie-insert-and-search/
// Author: Jeanniton Monero
// email: jeanniton.mnr@gmail.com
// website: jeanniton.me

/***********************************************************
* This implementation of Trie only works with key only
* contains lower case alphabet letters and/or apostrphes `'`
***********************************************************/


#ifndef TRIENODE_H
#define TRIENODE_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define AlPHABET_SIZE   (26)
#define CHILDREN_SIZE  (27)

// Representation of a TrieNode
struct TrieNode {
    // The children of this node
    struct TrieNode *children[CHILDREN_SIZE];
    // isEndOfWord is true if this node is the last char of a key/word
    bool isEndOfWord;
};



// Prototypes
struct TrieNode *getNode();
int getCharIndex(char a);
void insert(struct TrieNode *root, const char *key);
bool isInTrieNode(struct TrieNode *root, const char *key);
bool destroy(struct TrieNode *root);

#endif // TRIENODE_H