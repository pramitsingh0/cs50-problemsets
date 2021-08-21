// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"
int word_count = 0;
bool endof = false;
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;


// Number of buckets in hash table
const unsigned int N = 190788;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);
    for (node *temp = table[index]; temp != NULL; temp = temp -> next)
    {
        if (strcasecmp(word, temp -> word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash (const char* word)
 {  /*A case-insensitive implementation of the djb2 hash function.
    implemented by Neel Mehta. Link:
    https://github.com/hathix/cs50-section/blob/master/code/7/sample-hash-functions/good-hash-function.c*/
     unsigned long hash = 5381;

     for (const char* ptr = word; *ptr != '\0'; ptr++)
     {
         hash = ((hash << 5) + hash) + tolower(*ptr);
     }

     return hash % N;
 }

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dicsource = fopen(dictionary, "r");
    if (dicsource == NULL)
    {
        return false;
    }

    char buffer[LENGTH + 1];
    while (fscanf(dicsource, "%s", buffer) != EOF)
    {
        node *dicword = malloc(sizeof(node));
        if (dicword == NULL)
        {
           return false;
        }
        strcpy(dicword -> word, buffer);
        int index = hash(dicword -> word);
        dicword -> next = table[index];
        table[index] = dicword;
        word_count++;
    }
    endof = true;
    fclose(dicsource);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (endof == true)
    {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor -> next;
            free (temp);
        }
    }
    return true;

}
