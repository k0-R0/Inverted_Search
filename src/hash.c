#include "word_info.h"
#include <stdlib.h>
#include <string.h>

unsigned int hash_function(char *str) {
    unsigned int hash = 5381;
    while (*str) {
        hash = ((hash << 5) + hash) + *str++;
    }
    return hash;
}

Status update_file_node(Word_hash *hash_table_index, char *file_name) {

    File_node *curr = hash_table_index->file;
    while (curr->next && strcmp(curr->next->file_name, file_name))
        curr = curr->next;
    if (curr->next) {
        curr = curr->next;
        curr->count++;
        return SUCCESS;
    }

    File_node *new = calloc(1, sizeof(File_node));
    if (!new)
        return FAILURE;
    new->file_name = file_name;
    new->count = 1;
    hash_table_index->file->last = new;

    return SUCCESS;
}

void insert(Word_hash *hash_table, char *word, char *file_name) {
    unsigned int index = hash_function(word);
    if (!hash_table[index].word) {
        hash_table[index].word = word;
        hash_table[index].count++;
        update_file_node(&hash_table[index], file_name);
        hash_table[index].next = NULL;
    }
}

Status search_word(char *argv[]) { return SUCCESS; }
