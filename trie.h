#ifndef TRIE_H_
#define TRIE_H_

#include <stdbool.h>

#define ALPHABET_SIZE 26


typedef struct Trie
{
    struct Trie * children[ALPHABET_SIZE];
    void * content;
} Trie;

Trie * createTrie();

void destroyTrie(Trie * trie, void (*callback)(void *));

int removeTrie(Trie * trie, char * word, void ** output);

void insertTrie(Trie * trie, char * word, void * content);

void * searchTrie(Trie * trie, char * word);

#endif