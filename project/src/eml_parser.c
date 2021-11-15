#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "eml_parser.h"


static const size_t size_buf = 10000;

static int move_file_id(FILE* fptr, const char* newword) {
    if (fptr == NULL || newword == NULL) {
        return -1;
    }
    Object* obj = create_obj(strlen(newword) + 1);
    while (1) {
        fgets(obj->str, obj->size, fptr);
        if (strncmp(newword, obj->str, strlen(newword)) == 0) {
           char ch = fgetc(fptr);
           if (ch != ' ') {
               fseek(fptr, -1, SEEK_CUR);
           }
           free_obj(obj);
           return 0;
        }
        if (obj->str[0] == '\n' || obj->str[0] == '\r') {
            break;
        }
        if (obj->str[strlen(obj->str) - 1] != '\n'
            && obj->str[strlen(obj->str) - 1] != '\r') {
            char end_line = fgetc(fptr);
            while (end_line != '\n' && !feof(fptr)) {
                end_line = fgetc(fptr);
            }
        }
    }
    rewind(fptr);
    free_obj(obj);
    return -1;
}

static int get_value(FILE* fptr, const char* header, Object* header_val) {
    if (fptr == NULL || header == NULL || header_val == NULL) {
        return -1;
    }
    rewind(fptr);
    if (move_file_id(fptr, header) == 0) {
        Object* obj = create_obj(header_val->size);
        if (obj == NULL) {
            return -1;
        }
        while (1) {
            do {
                if (fgets(obj->str, obj->size, fptr) == NULL) {
                    free_obj(obj);
                    return -1;
                }
                if (copy_obj(header_val, obj, strlen(obj->str), strlen(header_val->str))) {
                    free_obj(obj);
                    return -1;
                }
            } while (obj->str[strlen(obj->str) - 1] != '\n'
                && obj->str[strlen(obj->str) - 1] != '\r');
            char new_line = fgetc(fptr);
            if ((new_line != ' ' && new_line != '\t')
                || new_line == '\n' || new_line == '\r' || feof(fptr)) {
                free_obj(obj);
                break;
            }
            if (fgetc(fptr) != ' ') {
                fseek(fptr, -2, SEEK_CUR);
            }
        }
    } else {
        header_val->str[0] = '\0';
    }
    return 0;
}

static int num_part(FILE* fptr, size_t* parts) {
    if (fptr == NULL || parts == NULL) {
        return -1;
    }
    *parts = 1;
    Object* header_val = create_obj(size_buf);
    if (header_val == NULL) {
        return -1;
    }
    if ((get_value(fptr, "Content-Type:", header_val) == 0)) {
        if (strstr(header_val->str, "multipart")
            || strstr(header_val->str, "MULTIPART")) {
            char* key = strstr(header_val->str, " boundary=");
            if (key == NULL) {
                key = strstr(header_val->str, " BOUNDARY=");
            }
            if (key == NULL) {
                key = strstr(header_val->str, ";boundary=");
            }
            if (key == NULL) {
                key = strstr(header_val->str, ";BOUNDARY=");
            }
            if (key == NULL) {
                key = strstr(header_val->str, "\tboundary=");
            }
            if (key == NULL) {
                key = strstr(header_val->str, "\tBOUNDARY=");
            }
            if (key == NULL) {
                free_obj(header_val);
                return 0;
            }
            key += strlen(" boundary=");
            if (key[0] == '"') {
               key++;
            }
            for (size_t i = strlen(key) - 1; (int) i > 0; i--) {
                if (key[i] == ';' || key[i] == ' '
                    || key[i] == ',' ||  key[i] == '"') {
                    key[i] = '\0';
                }
            }
            Object* obj = create_obj(strlen(key) + 3);
            size_t num_key = 0;
            while (!feof(fptr)) {
                fgets(obj->str, obj->size, fptr);
                if (strstr(obj->str, key)) {
                    char new_line = fgetc(fptr);
                    if ((new_line == '\n' || new_line == '\r')) {
                        num_key++;
                    }
                }
            }
            free_obj(obj);
            *parts = num_key;
        } else {  // look for the body of the letter
            *parts = 0;
            while (!feof(fptr)) {
                char new_line = fgetc(fptr);
                if ((new_line != '\n' && new_line != '\r') || feof(fptr)) {
                    *parts = 1;
                    break;
                }
            }
        }
    }
    free_obj(header_val);
    return 0;
}

Result* get_result(const char* path_to_eml) {
    FILE* fptr = fopen(path_to_eml, "r");
    if (fptr == NULL) {
        return NULL;
    }
    Result* res = create_result(size_buf, size_buf, size_buf);
    if (res == NULL) {
	fclose(fptr);
	return NULL;
    }
    if (get_value(fptr, "From:", res->from) != 0) {
    	free_result(res);
    	fclose(fptr);
    	return NULL;
    }
    if (get_value(fptr, "To:", res->to) != 0) {
        free_result(res);
    	fclose(fptr);
    	return NULL;
    }
    if (get_value(fptr, "Date:", res->date) != 0) {
	free_result(res);
    	fclose(fptr);
    	return NULL;
    }
    size_t parts = 0;
    if (num_part(fptr, &parts) != 0) {
	free_result(res);
    	fclose(fptr);
    	return NULL;
    }
    res->parts = parts;
    fclose(fptr);
    return res;
}

Result* create_result(size_t size_from, size_t size_to, size_t size_date) {
    Result* res = (Result*)calloc(1, sizeof(Result));
    if (res == NULL) {
        return NULL;
    }
    res->from = create_obj(size_from);
    res->to = create_obj(size_to);
    res->date = create_obj(size_date);
    if (res->from == NULL || res->to == NULL || res->date == NULL) {
        free_result(res);
        return NULL;
    }
    return res;
}

int print(const Result* res) {
    if (res) {
        printf("%s|%s|%s|%zu", res->from->str, res->to->str, res->date->str, res->parts);
        return 0;
    }
    return -1;
}

int free_result(Result* res) {
    if (res) {
        free_obj(res->from);
        free_obj(res->to);
        free_obj(res->date);
        free(res);
        return 0;
    }
    return -1;
}
