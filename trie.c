#include "trie.h"

#include <stdlib.h>

Trie * createTrie(){
    Trie * trie = (Trie*)malloc(sizeof(Trie));
    trie->content = NULL;
    for(int i = 0; i < ALPHABET_SIZE; i++){
        trie->children[i] = NULL;
    }
    return trie;
}

void destroyTrie(Trie * trie, void (*callback)(void *)){
    /* Destroy the whole Trie and FREES THE CONTENT MEMORY
       Calling this function makes you lose access to data that is allocated in the data structure
       Callback function pointer is called to handle memory dealocation of the allocated content
       If no callback is used, should be passed NULL */
    if(trie == NULL){
        return;
    }
    for(int i = 0; i < ALPHABET_SIZE; i++){
        destroyTrie(trie->children[i], callback);
        trie->children[i] = NULL;
    }
    if(callback) callback(trie->content);
    if(trie->content) {
        free (trie->content);
        trie->content = NULL;
    };
    free(trie);
}

void insertTrie(Trie * trie, char * word, void * content){
    // Inserts some content into the Trie
    if(word[0] == '\0'){
        trie->content = content;
        return;
    }
    unsigned int index = word[0] - 'a';
    
    if(trie->children[index] == NULL){
        trie->children[index] = createTrie();
    }
    insertTrie(trie->children[index], word + 1, content);
    return;
}

int isNodeChildless(Trie * node){
    for(int i = 0; i < ALPHABET_SIZE; i++){
        if(node->children[i] != NULL) return 0;
    }
    return 1;
}

int removeTrie(Trie * trie, char * word, void ** output){
    // Removes key from Trie but DOES NOT FREE THE CONTENT MEMORY
    // Freeing the content memory is the user's responsability
    if(word[0] == '\0'){
        if(isNodeChildless(trie)){
                void * temp_content = trie->content;
                if(trie) free(trie);
                *output = temp_content;
                return 1;
            } else {
                void * temp_content = trie->content;
                trie->content = NULL;
                *output = temp_content;
                return 0;
            }
    }

    unsigned int index = word[0] - 'a';

    if(trie->children[index] == NULL){
        *output = NULL;
        return 0;
    }

    int ret = removeTrie(trie->children[index], word+1, output);
    if(ret) trie->children[index] = NULL;
    if(isNodeChildless(trie) && !trie->content){
        free(trie);
        return 1;
    }
    return 0;
}

void * searchTrie(Trie * trie, char * word){
    // Returns NULL if key doesn't exist
    // Returns pointer to content in case it exists
    unsigned int index = word[0] - 'a';
    if(trie->children[index] == NULL){
        if(word[0] == '\0'){
            return trie->content;
        } else return NULL;
    } else if (word[0] == '\0'){
        return trie->content;
    } else {
        return searchTrie(trie->children[index], word + 1);
    }
}