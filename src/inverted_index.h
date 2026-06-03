#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include "common.h"
#include "hashing.h"
#include "list_ops.h"

typedef struct {
    Word_node **table;
    int size;
} InvertedIndex;

InvertedIndex* create_table(int size);
Status update_index(InvertedIndex *index, char *file_name);
void search_index(InvertedIndex *index, char *word);
void display_index(InvertedIndex *index);

#endif
