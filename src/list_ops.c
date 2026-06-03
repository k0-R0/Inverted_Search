#include "list_ops.h"

Status add_line_node(Line_node **head, int line_num) {
    Line_node *new = malloc(sizeof(Line_node));
    if (!new) return FAILURE;
    new->line_number = line_num;
    new->next = NULL;

    if (*head == NULL) {
        *head = new;
        return SUCCESS;
    }

    Line_node *temp = *head;
    while (temp->next) {
        if (temp->line_number == line_num) {
            free(new);
            return SUCCESS; // Already recorded
        }
        temp = temp->next;
    }
    if (temp->line_number == line_num) {
        free(new);
        return SUCCESS;
    }
    temp->next = new;
    return SUCCESS;
}

Status add_file_node(File_node **head, char *file_name, int line_num) {
    File_node *temp = *head;
    while (temp) {
        if (strcmp(temp->file_name, file_name) == 0) {
            temp->count++;
            return add_line_node(&(temp->line_head), line_num);
        }
        if (temp->next == NULL) break;
        temp = temp->next;
    }

    File_node *new = malloc(sizeof(File_node));
    if (!new) return FAILURE;
    new->file_name = strdup(file_name);
    new->count = 1;
    new->line_head = NULL;
    new->next = NULL;

    if (add_line_node(&(new->line_head), line_num) == FAILURE) {
        free(new->file_name);
        free(new);
        return FAILURE;
    }

    if (*head == NULL) {
        *head = new;
    } else {
        temp->next = new;
    }
    return SUCCESS;
}

Status add_word_node(Word_node **head, char *word, char *file_name, int line_num) {
    Word_node *temp = *head;
    while (temp) {
        if (strcmp(temp->word, word) == 0) {
            temp->count++;
            return add_file_node(&(temp->file_head), file_name, line_num);
        }
        if (temp->next == NULL) break;
        temp = temp->next;
    }

    Word_node *new = malloc(sizeof(Word_node));
    if (!new) return FAILURE;
    new->word = strdup(word);
    new->count = 1;
    new->file_head = NULL;
    new->next = NULL;

    if (add_file_node(&(new->file_head), file_name, line_num) == FAILURE) {
        free(new->word);
        free(new);
        return FAILURE;
    }

    if (*head == NULL) {
        *head = new;
    } else {
        temp->next = new;
    }
    return SUCCESS;
}
