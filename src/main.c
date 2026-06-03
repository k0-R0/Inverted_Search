#include "inverted_index.h"
#include "validations.h"
#include <sys/stat.h>

long get_total_size(char *argv[]) {
    long total = 0;
    struct stat st;
    for (int i = 1; argv[i]; i++) {
        if (stat(argv[i], &st) == 0) {
            total += st.st_size;
        }
    }
    return total;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file1.txt> <file2.txt> ...\n", argv[0]);
        return 1;
    }

    // Basic validation (using existing validations.c logic, adjusted for index)
    // For simplicity, we'll iterate from 1 here as main.c used 2 before
    for (int i = 1; i < argc; i++) {
        char *ext = strstr(argv[i], ".txt");
        if (!ext || strcmp(ext, ".txt") != 0) {
            printf("Error: %s is not a .txt file\n", argv[i]);
            return 1;
        }
    }

    // Heuristic: Total Size / 8 for unique words, then 1.3x for low load factor
    long total_size = get_total_size(argv);
    int estimated_unique_words = (total_size / 8) * 1.3;
    int table_size = find_closest_prime(estimated_unique_words);

    printf("Initializing Inverted Index with table size: %d\n", table_size);
    InvertedIndex *index = create_table(table_size);
    if (!index) {
        printf("Error: Failed to initialize hash table\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        printf("Indexing %s...\n", argv[i]);
        if (update_index(index, argv[i]) != SUCCESS) {
            printf("Warning: Failed to index %s\n", argv[i]);
        }
    }

    int choice;
    char search_word[100];
    do {
        printf("\n1. Display Index\n2. Search Word\n3. Exit\nEnter choice: ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1:
                display_index(index);
                break;
            case 2:
                printf("Enter word to search: ");
                scanf("%99s", search_word);
                search_index(index, search_word);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 3);

    // TODO: Implement cleanup function to free all memory
    return 0;
}
