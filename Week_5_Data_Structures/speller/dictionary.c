// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10000;

// Number of words in the dictionary we load
int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{

    unsigned int index = hash(word); // we have to convert this world to lowercase! This happens on the has function.

    node *checker = table[index]; // creates a node pointer

    while (checker != NULL)
    {
        // goes to where the pointer is and compares the word on the node to word we are checking;
        if (strcasecmp((*checker).word, word) == 0)
        {
            return true;
        }
        checker = checker->next;
    }

    // if we dont find the word
    return false;
}

// Hashes word to a number
// this function was done based on djb2 from http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *word)
{
    unsigned int hash = 5381;
    int c;

    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + tolower(c); /* hash * 33 + c */
    }

    return (hash % N); // to make sure the number fits our table
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");

    if (dict == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(dict, "%s", word) != EOF)
    {
        // creates new node for the word
        node *newWord = malloc(sizeof(node));

        if (newWord == NULL)
        {
            return false;
        }

        // copies the word read to created node
        strcpy(newWord->word, word);

        // gets the hash index to the word
        unsigned int index = hash(word);

        // gets pointer to the current first element of list
        node *temp = table[index];

        // sets our newly created node's pointer to the first element
        newWord->next = temp;

        // sets first pointer of the list to our newly created node
        table[index] = newWord;

        // add the word to the count
        word_count += 1;
    }

    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }

    }
    return true;
}
