// A implmentation of TrieNode adapted from https://www.geeksforgeeks.org/trie-insert-and-search/
// Author: Jeanniton Monero
// email: jeanniton.mnr@gmail.com
// website: jeanniton.me

/***********************************************************
* This implementation of Trie here only works with key which
* contains alphabet letters and/or apostrphes `'` and it's
* case insensitive.
***********************************************************/

#include <string.h>
#include <ctype.h>

#include "helper.h"
#include "TrieNode.h"



// Return a new TrieNode
struct TrieNode *getNode()
{
    struct TrieNode *pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));

    // Initialize this node children to NULL
    for(int index=0; index < CHILDREN_SIZE; index++)
    {
        pNode->children[index] = NULL;
    }

    pNode->isEndOfWord = false;

    return pNode;
};

// Return the leaf index for this char
int getCharIndex(char a){
    int index = -1;
    if(isalpha(a))
    {
        index = a - (int)'a';
    }else
    {
        switch(a)
        {
            case '\'':
                index = CHILDREN_SIZE - 1; // ALPHABET_SIZE + 1 ( -1, for array indexing);
                break;
            default:
                // Crash the program
                printf("Cannot get index for char `%i`.\n", a);
                crash(1);
        }
    }

    return index;
}


// Insert a new Key into the TrieNode tree
// If the key is a prefix, just mark the last
// leaf IsEndOfWord = true
void insert(struct TrieNode *root, const char *key)
{
    struct TrieNode *crawl = root;
    int index;
    int len = strlen(key);
    int level;
    int keyChar;

    for(level = 0; level < len; level++)
    {
        keyChar = tolower(key[level]);
        // Get the index for this char in key
        index = getCharIndex(keyChar);
        // Check to see if the leaf for index exists
        if(!crawl->children[index])
        {
            crawl->children[index] = getNode();
        }
        crawl = crawl->children[index];
    }
    // Mark the last char of this key
    crawl->isEndOfWord = true;
};

bool isInTrieNode(struct TrieNode *root, const char *key)
{
    struct TrieNode *crawl = root;
    int level;
    int len = strlen(key);
    int index;
    int keyChar;

    for(level = 0; level < len; level++)
    {
        keyChar = tolower(key[level]);
        // Get the index for this char in key
        index = getCharIndex(keyChar);
        if(!crawl->children[index]){
            return false;
        }
        crawl = crawl->children[index];
    }

    return ( (crawl != NULL) && (crawl->isEndOfWord) );
}

bool destroy(struct TrieNode *root)
{

    for(int i = 0; i < CHILDREN_SIZE; i++)
    {
        if(root->children[i] != NULL)
            destroy(root->children[i]);
    }

    if(root)
    {
        free(root);
        root = NULL;
    }

    return true;
}