#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26

struct Trie {
    int count;
    bool endWord;
    struct Trie *children[ALPHABET_SIZE];
};

void insert(struct Trie **ppTrie, char *word) {
    struct Trie *pTrie = *ppTrie;
    if (!pTrie) {
        pTrie = *ppTrie = calloc(1, sizeof *pTrie);
    }
    for (int i = 0; word[i]; ++i) {
        int index = word[i] - 'a';
        if (!pTrie->children[index]) {
            pTrie->children[index] = calloc(1, sizeof *pTrie);
        }
        pTrie = pTrie->children[index];
    }
    pTrie->count++;
    pTrie->endWord = true;
}


int numberOfOccurances(struct Trie *pTrie, char *word) {
    if (pTrie == NULL) {
        return 0;
    }
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (pTrie->children[index] == NULL) {
            return 0;
        }
        pTrie = pTrie->children[index];
    }
    if (pTrie->endWord) {
        return pTrie->count;
    }
    return 0;
}

struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie == NULL) {
        return NULL;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        pTrie->children[i] = deallocateTrie(pTrie->children[i]);
    }
    free(pTrie);
    return NULL;
}

int main(void) {
    struct Trie *trie = NULL;
    // read the number of the words in the dictionary
    // parse line  by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    int n = sizeof(pWords) / sizeof(char *);
    for (int i = 0; i < n; i++) {
        insert(&trie, pWords[i]);
    }
    for (int i = 0; i < n; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));
    }
    trie = deallocateTrie(trie);
    if (trie != NULL) {
        printf("There is an error in this program\n");
    }
}
