#include "validations.h"

Status validate_files(char *argv[]) {
    for (int i = 1; argv[i]; i++) {
        char *extension = strstr(argv[i], ".txt");
        if (!extension || strcmp(extension, ".txt") != 0)
            return FAILURE;
    }
    return SUCCESS;
}
