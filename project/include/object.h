#ifndef PROJECT_INCLUDE_OBJECT_H_
#define PROJECT_INCLUDE_OBJECT_H_

#include <stddef.h>

typedef struct {
    char* str;
    size_t size;
    size_t max_size;
} Object;

Object* create_obj(const size_t len_str);
int incr_size_obj(Object* obj, const size_t len_str);
int copy_obj(Object* left, const Object* right, size_t num, size_t begin_copy);
int free_obj(Object* obj);

#endif  // PROJECT_INCLUDE_OBJECT_H_
