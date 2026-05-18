#ifndef WORD_MAP_H
#define WORD_MAP_H
typedef struct file_node {
    char *file_name;
    int count;
    struct file_node *last;
    struct file_node *next;
} File_node;

typedef struct word_hash {
    char *word;
    int count;
    File_node *file;
    struct word_hash *next;
    struct word_hash *last;
} Word_hash;

typedef enum { SUCCESS, FAILURE } Status;
#endif // !DEBUG WORD_MAP_H
