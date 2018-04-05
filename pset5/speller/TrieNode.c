// A implmentation of TrieNode adapted from https://www.geeksforgeeks.org/trie-insert-and-search/
// Author: Jeanniton Monero
// email: jeanniton.mnr@gmail.com
// website: jeanniton.me


#include <string.h>
#include <type.h>

#include "helper.h"
#include "TrieNode.h"

#define AlPHABET_SIZE   (26)
#define CHILDREN_SIZE  (27)



// Return a new TrieNode
struct TrieNode *getNode()
{
    struct TrieNode *pNode = (struct TrieNode)malloc(sizeof(struct TrieNode));
    // Initialize this node children to NULL
    for(int index=0; index < CHILDREN_SIZE; index++)
    {
        pNode->children[index] = NULL;
    }
    return pNode;
};

// Return the leaf index for this char
int getCharIndex(char a)
{
    int index;
    if(isalpha(a))
    {
        index = (int)'a' - a;
    }else
    {
        switch(a)
        {
            case '\'':
                index = 27; // ALPHABET_SIZE + 1;
                break;
            default:
                // Crash the program
                char *msg = concatenate("Cannot get index for char: ", a);
                // Crach function not yet implemented
                crash(1, msg);
        }
    }

    return index;
}


// Insert a new Key into the TrieNode tree
// If the key is a prefix, just mark the last
// leaf IsEndOfWord
void insert(TrieNode *root, const char *key)
{
    TrieNode *crawl = root;
    int index;
    int len = strlen(key);
    int level;

    for(level = 0; level < len; level++)
    {
        // Get the index for this char in key
        index = getCharIndex(key[level]);
        // Check to see if the leaf for index exists
        if(!crawl->children[index])
        {
            crawl->children[index] = getNode();
        }
        crawl = children[index];
    }
    // Mark the last char of this key
    crawl->isEndOfWord = true;
};

bool isInTrieNode(TrieNode *root, const char *key)
{
    TrieNode *crawl = root;
    int level;
    int len = str(key);
    int index;

    for(level = 0; level < len; level++)
    {
        index = getCharIndex(key[level]);
        if(!crawl->children[index]){
            return false;
        }
        crawl = crawl->children(key[level]);
    }

    return ( (crawl != NULL) && (crawl->isEndOfWord) );
}