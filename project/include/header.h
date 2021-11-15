#ifndef PROJECT_INCLUDE_HEADER_H_
#define PROJECT_INCLUDE_HEADER_H_

#include <stddef.h>

typedef struct {
    char* str;
    size_t size;
    size_t max_size;
} Header;

Header* create_header(const size_t len_str);
int increase_header(Header* caption, const size_t len_str);
int copy_header(Header* left, const Header* right, size_t num, size_t begin_copy);
int free_header(Header* caption);

#endif  // PROJECT_INCLUDE_HEADER_H_
