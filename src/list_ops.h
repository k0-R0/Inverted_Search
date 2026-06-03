#ifndef LIST_OPS_H
#define LIST_OPS_H

#include "common.h"

Status add_word_node(Word_node **head, char *word, char *file_name, int line_num);
Status add_file_node(File_node **head, char *file_name, int line_num);
Status add_line_node(Line_node **head, int line_num);

#endif
