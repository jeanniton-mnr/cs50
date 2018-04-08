// Implements a dictionary's functionality

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"
#include "helper.h"
#include "TrieNode.h"

// Initialize the root for the dictionary trie
struct TrieNode *dictionaryTrie = NULL;

// Iniatialize number of word loaded in the dictionary to zero (0)
unsigned int wordCount = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    return isInTrieNode(dictionaryTrie, word);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize the root of the dictionary
    dictionaryTrie = getNode();
    // Open dictionary file
    FILE *inptr = fopen(dictionary, "r");
    if(inptr){
        // Create buffer to read each word in the dictionary
        char word[LENGTH + 1];
        int index = 0;

        char c = fgetc(inptr);
        // Load word from the dictionary file to the dictionaryTrie/memory
        do
        {
            // Append this char at to the word buffer if not a cariage return
            if( c != '\n'){
                word[index] = tolower(c);
                index++;
            }

            // We find a new complete word
            else
            {
                word[index] = '\0';
                index = 0;
                // Insert this word in the dictionaryTrie
                insert(dictionaryTrie, word);
                wordCount++;
            }
            // Get the next character in the stream
            c = fgetc(inptr);
        }while(c != EOF);


        // Insert the last word found in the dictionary file
        /*
        * word[index] = '\0';
        * insert(dictionaryTrie, word);
        * wordCount++;
        */

        // Close the file stream
        fclose(inptr);
        return true;
    }

    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    return destroy(dictionaryTrie);
}
