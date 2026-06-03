#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    SUCCESS,
    FAILURE,
    WORD_FOUND,
    WORD_NOT_FOUND,
    FILE_NOT_FOUND
} Status;

typedef struct line_node {
    int line_number;
    struct line_node *next;
} Line_node;

typedef struct file_node {
    char *file_name;
    int count;
    Line_node *line_head;
    struct file_node *next;
} File_node;

typedef struct word_node {
    char *word;
    int count; // Total occurrences across all files
    File_node *file_head;
    struct word_node *next;
} Word_node;

#endif
