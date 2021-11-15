#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

#define ERROR (-1)
#define SUCCESS 0

Header* create_header(const size_t len_str) {
    Header* caption = (Header*)calloc(1, sizeof(Header));
    if (caption == NULL) {
	free_header(caption);
	return NULL;
    }
    caption->size = len_str;
    caption->max_size = 2 * len_str;
    caption->str = (char*)calloc(caption->max_size, sizeof(char));
    if (caption->str == NULL) {
	free_header(caption);
	return NULL;
    }
    return caption;
}

int increase_header(Header* caption, const size_t len_str) {
    if (caption == NULL) {
        return ERROR;
    }
    caption->size += len_str;
    if (caption->max_size < caption->size) {
        caption->max_size = 2 * caption->size;
        char* new_obj = (char*)realloc(caption->str, caption->max_size);
        if (new_obj == NULL) {
            return ERROR;
        }
        for (size_t i = caption->size - len_str; i < caption->max_size; ++i) {
            new_obj[i] = '\0';
        }
        caption->str = new_obj;
    }
    return SUCCESS;
}

int copy_header(Header* left, const Header* right, size_t num, size_t begin_copy) {
    if (left == NULL || right == NULL) {
        return ERROR;
    }
    if (right->size < num) {
        return ERROR;
    }
    if (left->size <= num + begin_copy) {
        if (increase_header(left, num + begin_copy)) {
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

int free_header(Header* caption) {
	if (caption == NULL) {
		return ERROR;
	}
	free(caption->str);
	free(caption);
	return SUCCESS;
}
