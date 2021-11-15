#include <stdio.h>
#include <stdlib.h>

#include "eml_parser.h"

int main(int argc, const char **argv) {
    if (argc != 2) {
        return -1;
    }
    const char *path_to_eml = argv[1];
    Result* res = get_result(path_to_eml);
    print(res);
    free_result(res);
    return 0;
}
