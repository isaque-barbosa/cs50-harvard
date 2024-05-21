// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N_HASH = 1;
const unsigned int N = 26;

// Hash table
node *table[26];

unsigned int length = 0;

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    const int A_UPPER_ASCII = 64, Z_UPPER_ASCII = 90, A_LOWER_ASCII = 96, Z_LOWER_ASCII = 122;
    int hash = 0;
    for(int i = 0; i < N_HASH; i++)
    {
        if (word[i] >= A_UPPER_ASCII && word[i] <= Z_UPPER_ASCII)
        {
            hash += word[i] - A_UPPER_ASCII;
            continue;
        }
        if (word[i] >= A_LOWER_ASCII && word[i] <= Z_LOWER_ASCII)
        {
            hash += word[i] - A_LOWER_ASCII;
        }
    }
    return hash;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    const int index = hash(word);
    for(node *current = table[index]; current != NULL; current = current->next)
    {
        if(strcasecmp(current->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if(file == NULL)
    {
        return false;
    }
    char d_word[LENGTH + 1];
    while(fscanf(file, "%s", d_word) != EOF)
    {
        node *current = malloc(sizeof(node));
        if(current == NULL)
        {
            unload();
            fclose(file);
            return false;
        }
        strcpy(current->word, d_word);
        unsigned int index = hash(d_word);
        current->next = table[index];
        table[index] = current;
        length++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return length;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *ptr;
    node *temp;

    for (int i = 0; i < N; i++) {
        for (temp = table[i];  temp != NULL;  temp = ptr) {
            ptr = temp->next;
            free(temp);
            temp = NULL;
        }
        table[i] = NULL;
        if (i == N - 1 && ptr == NULL)
        {
            return true;
        }
    }

    return false;
}
