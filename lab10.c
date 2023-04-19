#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Trie{
    int isWord;
    struct Trie *next[26];
} Trie;

void insert(struct Trie **ppTrie, char *word)
{
    Trie* temp = (*ppTrie);
    Trie* create;
    int len = strlen(word);
    int nextIndex;
    int i = 0;

    while (1)
    {
        if (i == len)
        {   
            temp->isWord++;
 
            return;
        }

        nextIndex = word[i] - 'a';

        if (temp->next[nextIndex] == NULL)
        {
            create= (Trie*)malloc(sizeof(Trie));
            create->isWord = 0;

            for (int i = 0; i < 26; i++)
                create->next[i] = NULL;

            temp->next[nextIndex] = create;
            temp = temp->next[nextIndex];
        }
        else
        {
            temp = temp->next[nextIndex];
        }

        i++;
    }
}

int numberOfOccurances(struct Trie *pTrie, char *word)
{
    if (pTrie == NULL)
    {
        printf("This should not hit.");
        return 0;
    }

    int len = strlen(word);
    int i = 0;
    Trie *temp = pTrie;
    int nextIndex;

    while (1)
    {
        if (i == len)
        {
            return temp->isWord;
        }

        nextIndex = word[i] - 'a';

        if (temp->next[nextIndex] != NULL)
            temp = temp->next[nextIndex];
        
        i++;
    }
}

struct Trie *deallocateTrie(struct Trie *pTrie)
{
    // Recursive free-ing starting from the "leaf" nodes.
    for (int i = 0; i < 26; i++)
        if (pTrie->next[i] != NULL)
            deallocateTrie(pTrie->next[i]);

    free(pTrie);
    pTrie = NULL;

    return pTrie;
}

int main(void)
{
    Trie *trie = (Trie*)malloc(sizeof(Trie));
    trie->isWord = 0;

    for (int i = 0; i < 26; i++)
    {
        trie->next[i] = NULL;
    }

    //read the number of the words in the dictionary
    // parse line  by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};

    for (int i = 0; i < 5; i++)
    {
        insert(&trie, pWords[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n",pWords[i], numberOfOccurances(trie, pWords[i]));
    }

    trie = deallocateTrie(trie);

    if (trie != NULL)
       printf("There is an error in this program\n");

    return 0;
}