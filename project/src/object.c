#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "object.h"

#define ERROR (-1)
#define SUCCESS 0

Object* create_obj(const size_t len_str) {
    Object* obj = (Object*)calloc(1, sizeof(Object));
    if (obj == NULL) {
	free_obj(obj);
	return NULL;
    }
    obj->size = len_str;
    obj->max_size = 2 * len_str;
    obj->str = (char*)calloc(obj->max_size, sizeof(char));
    if (obj->str == NULL) {
	free_obj(obj);
	return NULL;
    }
    return obj;
}

int incr_size_obj(Object* obj, const size_t len_str) {
    if (obj == NULL) {
        return ERROR;
    }
    obj->size += len_str;
    if (obj->max_size < obj->size) {
        obj->max_size = 2 * obj->size;
        char* new_obj = (char*)realloc(obj->str, obj->max_size);
        if (new_obj == NULL) {
            return ERROR;
        }
        for (size_t i = obj->size - len_str; i < obj->max_size; ++i) {
            new_obj[i] = '\0';
        }
        obj->str = new_obj;
    }
    return SUCCESS;
}

int copy_obj(Object* left, const Object* right, size_t num, size_t begin_copy) {
    if (left == NULL || right == NULL) {
        return ERROR;
    }
    if (right->size < num) {
        return ERROR;
    }
    if (left->size <= num + begin_copy) {
        if (incr_size_obj(left, num + begin_copy)) {
            return ERROR;
        }
    }
    for (size_t i = 0, j = 0; i < num; i++) {
        if (right->str[i] != '\n' && right->str[i] != '\r') {
            left->str[j + begin_copy] = right->str[i];
            j++;
        }
    }
    left->str[strlen(left->str)] = '\0';
    return SUCCESS;
}

int free_obj(Object* obj) {
	if (obj == NULL) {
		return ERROR;
	}
	free(obj->str);
	free(obj);
	return SUCCESS;
}
