#ifndef PROJECT_INCLUDE_EML_PARSER_H_
#define PROJECT_INCLUDE_EML_PARSER_H_

#include <stddef.h>
#include "header.h"

typedef struct {
    Header* from;
    Header* to;
    Header* date;
    size_t parts;
} Result;

Result* create_result(size_t size_from, size_t size_to, size_t size_date);
Result* get_result(const char* path_to_eml);
int print(const Result* res);
int free_result(Result* res);

#endif  // PROJECT_INCLUDE_EML_PARSER_H_

