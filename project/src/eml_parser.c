#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "eml_parser.h"

#define TRUE (1)
#define SUCCESS (0)
#define ERROR (-1)
#define BEGIN_VALUE (-2)

#define SPACE (' ')
#define TAB ('\t')
#define NEW_STR ('\n')
#define RETURN_CARRIAGE ('\r')
#define END_LINE ('\0')
#define SEMICOLON (';')
#define COMMA (',')


static const size_t size_buf = 10000;

static int move_file_id(FILE* reading_file, const char* new_word) {
    if (reading_file == NULL || new_word == NULL) {
        return ERROR;
    }
    Header* caption = create_header(strlen(new_word) + 1);
    while (TRUE) {
        fgets(caption->str, caption->size, reading_file);
        if (strncmp(new_word, caption->str, strlen(new_word)) == 0) {
           char ch = fgetc(reading_file);
           if (ch != SPACE) {
               fseek(reading_file, -1, SEEK_CUR);
           }
           free_header(caption);
           return SUCCESS;
        }
        if (caption->str[0] == NEW_STR || caption->str[0] == RETURN_CARRIAGE) {
            break;
        }
        if (caption->str[strlen(caption->str) - 1] != NEW_STR
            && caption->str[strlen(caption->str) - 1] != RETURN_CARRIAGE) {
            char end_line = fgetc(reading_file);
            while (end_line != NEW_STR && !feof(reading_file)) {
                end_line = fgetc(reading_file);
            }
        }
    }
    rewind(reading_file);
    free_header(caption);
    return ERROR;
}

static int get_value(FILE* reading_file, const char* head_path, Header* header_val) {
    if (reading_file == NULL || head_path == NULL || header_val == NULL) {
        return ERROR;
    }
    rewind(reading_file);
    if (move_file_id(reading_file, head_path) == 0) {
        Header* caption = create_header(header_val->size);
        if (caption == NULL) {
            return ERROR;
        }
        while (TRUE) {
            do {
                if (fgets(caption->str, caption->size, reading_file) == NULL) {
                    free_header(caption);
                    return ERROR;
                }
                if (copy_header(header_val, caption, strlen(caption->str), strlen(header_val->str))) {
                    free_header(caption);
                    return ERROR;
                }
            } while (caption->str[strlen(caption->str) - 1] != NEW_STR
                && caption->str[strlen(caption->str) - 1] != RETURN_CARRIAGE);
            char new_line = fgetc(reading_file);
            if ((new_line != SPACE && new_line != TAB)
                || new_line == NEW_STR || new_line == RETURN_CARRIAGE || feof(reading_file)) {
                free_header(caption);
                break;
            }
            if (fgetc(reading_file) != SPACE) {
                fseek(reading_file, BEGIN_VALUE, SEEK_CUR);
            }
        }
    } else {
        header_val->str[0] = END_LINE;
    }
    return SUCCESS;
}

static int num_part(FILE* reading_file, size_t* parts) {
    if (reading_file == NULL || parts == NULL) {
        return ERROR;
    }
    *parts = 1;
    Header* header_val = create_header(size_buf);
    if (header_val == NULL) {
        return ERROR;
    }
    if ((get_value(reading_file, "Content-Type:", header_val) == 0)) {
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
                free_header(header_val);
                return SUCCESS;
            }
            key += strlen(" boundary=");
            if (key[0] == '"') {
               key++;
            }
            for (size_t i = strlen(key) - 1; (int) i > 0; i--) {
                if (key[i] == SEMICOLON || key[i] == SPACE
                    || key[i] == COMMA ||  key[i] == '"') {
                    key[i] = '\0';
                }
            }
            Header* caption = create_header(strlen(key) + 3);
            size_t num_key = 0;
            while (!feof(reading_file)) {
                fgets(caption->str, caption->size, reading_file);
                if (strstr(caption->str, key)) {
                    char new_line = fgetc(reading_file);
                    if ((new_line == NEW_STR || new_line == RETURN_CARRIAGE)) {
                        num_key++;
                    }
                }
            }
            free_header(caption);
            *parts = num_key;
        } else {  // look for the body of the letter
            *parts = 0;
            while (!feof(reading_file)) {
                char new_line = fgetc(reading_file);
                if ((new_line != NEW_STR && new_line != RETURN_CARRIAGE) || feof(reading_file)) {
                    *parts = 1;
                    break;
                }
            }
        }
    }
    free_header(header_val);
    return SUCCESS;
}

Result* get_result(const char* path_to_eml) {
    FILE* reading_file = fopen(path_to_eml, "r");
    if (reading_file == NULL) {
        return NULL;
    }
    Result* res = create_result(size_buf, size_buf, size_buf);
    if (res == NULL) {
	fclose(reading_file);
	return NULL;
    }
    if (get_value(reading_file, "From:", res->from) != 0) {
    	free_result(res);
    	fclose(reading_file);
    	return NULL;
    }
    if (get_value(reading_file, "To:", res->to) != 0) {
        free_result(res);
    	fclose(reading_file);
    	return NULL;
    }
    if (get_value(reading_file, "Date:", res->date) != 0) {
	free_result(res);
    	fclose(reading_file);
    	return NULL;
    }
    size_t parts = 0;
    if (num_part(reading_file, &parts) != 0) {
	free_result(res);
    	fclose(reading_file);
    	return NULL;
    }
    res->parts = parts;
    fclose(reading_file);
    return res;
}

Result* create_result(size_t size_from, size_t size_to, size_t size_date) {
    Result* res = (Result*)calloc(1, sizeof(Result));
    if (res == NULL) {
        return NULL;
    }
    res->from = create_header(size_from);
    res->to = create_header(size_to);
    res->date = create_header(size_date);
    if (res->from == NULL || res->to == NULL || res->date == NULL) {
        free_result(res);
        return NULL;
    }
    return res;
}

int print(const Result* res) {
    if (res) {
        printf("%s|%s|%s|%zu", res->from->str, res->to->str, res->date->str, res->parts);
        return SUCCESS;
    }
    return ERROR;
}

int free_result(Result* res) {
    if (res) {
        free_header(res->from);
        free_header(res->to);
        free_header(res->date);
        free(res);
        return SUCCESS;
    }
    return ERROR;
}
