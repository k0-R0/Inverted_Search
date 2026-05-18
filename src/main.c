#include "hash.h"
#include "validations.h"
#include "word_info.h"

int main(int argc, char *argv[]) {
    if (argc < 3)
        return 0;
    if (validate_files(argv) == FAILURE)
        return 0;
    if (search_word(argv) == FAILURE)
        return 0;
}
