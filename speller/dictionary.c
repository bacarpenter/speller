// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h> //from help section
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

//Global var for wordCount
int wordCount = 0;

// Number of buckets in hash table
const unsigned int N = 26; //using 26 so that each letter gets one table

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *Scan = table[hash(word)];
    while (Scan != NULL) //Loop  untill one of the return statments are triggered, or all words are checked somehow.
    {
        if (strcasecmp(Scan->word, word) == 0)
        {
            return true;
        }
        
        Scan = Scan->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return (tolower(word[0]) - 97); 
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //Open the dictonary in read mode
    FILE *dictonaryPointer = fopen(dictionary, "r");

    if (dictonaryPointer == NULL) //check to make sure the file could be opened
    {
        return false;
    }

    char word[LENGTH]; //define a char arry of the max length of words,  taken and adapted from https://www.geeksforgeeks.org/scanf-and-fscanf-in-c-simple-yet-poweful/
    while (fscanf(dictonaryPointer, "%s", word) !=
           EOF) //Taken and adapted from https://www.geeksforgeeks.org/scanf-and-fscanf-in-c-simple-yet-poweful/ and helped from Carlos
    {
        //find the hash for the word
        int wordHased = hash(word);
  				
        //check if the table[word] == 0 or table[word] == NULL
        if (&table[wordHased] == 0x0)
        {
            node *newWord = malloc(sizeof(node));
         
            if (newWord == NULL)
            {
                return false;
            }
            strcpy(newWord->word, word); //Helped from Carlos
            newWord->next = NULL;
         
            table[wordHased] = newWord;
         
            wordCount++;
        }
        else
        {
            node *newWord = malloc(sizeof(node));
             
            if (newWord == NULL)
            {
                return false;
            }
             
            strcpy(newWord->word, word); //Helped from Carlos
             
            newWord->next = table[wordHased];
             
            table[wordHased] = newWord;
             
            wordCount++;
        }

    }
    fclose(dictonaryPointer);
    return true;

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void) 
{
    for (int i = 0; i < N; i++)
    {
        while ((table[i]) != NULL)
        {
            node *temp = table[i]->next;
            free(table[i]);
            table[i] = temp;
        }
    }
    if (*table != 0)
    {
        return false;
    }
    
    return true;
}

/*
    I would like to siencerly thank Carlos for his help in debugging my code, I wouldn't have preformed as well without him. 
    Other than that, any code coppied has been  cited to the best of my knowladge. I saw somecode without wanting to, however, 
    I do not belive it effected my work!
*/