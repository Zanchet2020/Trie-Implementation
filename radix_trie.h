#ifndef RADIX_TRIE_H_
#define RADIX_TRIE_H_

#include "char_mapper.h"

#include <stdbool.h>

typedef struct Trie
{
    struct Trie * children[NUMBER_OF_CHARACTERS];
    void * content;
} Trie;

Trie * createTrie();

void destroyTrie(Trie * trie, void (*callback)(void *));

int removeTrie(Trie * trie, char * word, void ** output);

void insertTrie(Trie * trie, char * word, void * content);

void * searchTrie(Trie * trie, char * word);

#endif