#include "inverted_index.h"
#include <ctype.h>

InvertedIndex* create_table(int size) {
    InvertedIndex *index = malloc(sizeof(InvertedIndex));
    if (!index) return NULL;
    index->size = size;
    index->table = calloc(size, sizeof(Word_node*));
    if (!index->table) {
        free(index);
        return NULL;
    }
    return index;
}

Status update_index(InvertedIndex *index, char *file_name) {
    FILE *fptr = fopen(file_name, "r");
    if (!fptr) return FILE_NOT_FOUND;

    char word[100];
    int line_num = 1;
    char line[1024];

    while (fgets(line, sizeof(line), fptr)) {
        char *ptr = line;
        int offset;
        while (sscanf(ptr, "%99s%n", word, &offset) == 1) {
            ptr += offset;
            
            // Basic cleanup: remove punctuation and convert to lowercase
            int len = strlen(word);
            for (int i = 0; i < len; i++) {
                word[i] = tolower(word[i]);
                if (ispunct(word[i])) {
                    word[i] = '\0';
                    break;
                }
            }
            
            if (strlen(word) > 0) {
                unsigned int h = hash_function(word, index->size);
                add_word_node(&(index->table[h]), word, file_name, line_num);
            }
        }
        line_num++;
    }

    fclose(fptr);
    return SUCCESS;
}

void search_index(InvertedIndex *index, char *word) {
    // Cleanup word for search
    char clean_word[100];
    strncpy(clean_word, word, 99);
    for (int i = 0; clean_word[i]; i++) clean_word[i] = tolower(clean_word[i]);

    unsigned int h = hash_function(clean_word, index->size);
    Word_node *temp = index->table[h];

    while (temp) {
        if (strcmp(temp->word, clean_word) == 0) {
            printf("Word [%s] is present in %d total instances:\n", temp->word, temp->count);
            File_node *f_temp = temp->file_head;
            while (f_temp) {
                printf("  - File: %s (Count: %d)\n", f_temp->file_name, f_temp->count);
                printf("    Lines: ");
                Line_node *l_temp = f_temp->line_head;
                while (l_temp) {
                    printf("%d%s", l_temp->line_number, l_temp->next ? ", " : "");
                    l_temp = l_temp->next;
                }
                printf("\n");
                f_temp = f_temp->next;
            }
            return;
        }
        temp = temp->next;
    }
    printf("Word [%s] not found in index.\n", word);
}

void display_index(InvertedIndex *index) {
    printf("%-15s %-15s %-10s %-15s\n", "Word", "File", "Count", "Lines");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < index->size; i++) {
        Word_node *w_temp = index->table[i];
        while (w_temp) {
            File_node *f_temp = w_temp->file_head;
            while (f_temp) {
                printf("%-15s %-15s %-10d ", w_temp->word, f_temp->file_name, f_temp->count);
                Line_node *l_temp = f_temp->line_head;
                while (l_temp) {
                    printf("%d%s", l_temp->line_number, l_temp->next ? ", " : "");
                    l_temp = l_temp->next;
                }
                printf("\n");
                f_temp = f_temp->next;
            }
            w_temp = w_temp->next;
        }
    }
}
