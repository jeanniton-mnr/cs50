// Implements a dictionary's functionality

#include <stdio.h>
#include <stdbool.h>

#include "dictionary.h"
#include "helper.h"
#include "TrieNode.h"

//
TriedNode *dictionaryTrie = (TrieNode)malloc(sizeof(TrieNode));

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *inptr = fopen(dictionary, "r");
    if(inptr){
        // Create buffer to read each word in the dictionary
        char word[LENGTH + 1];
        int index = 0;
        char c;
        // Load word from the dictionary file to the dictionaryTrie/memory
        while( c = fgetc(inptr) &&  c != EFO){

            // Append this char at to the word buffer if not a cariage return
            if( c != '\n'){
                word[index] = c;
                index++;
            }

            // We find a new complete word
            else
            {
                word[index] = '\0';
                index = 0;
                // Insert this word in the dictionaryTrie
                insert(dictionaryTrie, word);
            }
        }
        // Insert the last word found in the dictionary file
        insert(dictionaryTrie, word);
        // Close the file stream
        fclose(inptr);

        return true;
    }

    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}
