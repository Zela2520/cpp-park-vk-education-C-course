#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


#define ERROR (-1)

/*typedef enum {
	L_STRING,
	L_COLON, // :
	L_SEMICOLON, // ;
	L_EQUALLY, // =
	L_BEGIN_KEY, // 
	L_END_KEY, // 
	L_NEW_STRING, // '\n'
	L_CONTINUE_VAL, // ' + string'
	L_EMPTY_STRING, // spaces + '\0'
	L_COUNT,
} lexem_t;

typedef enum {
	S_HEADER,
	S_COLON,
	S_VALUE,
	S_CONT_VAL,
	S_SEMICOLON,
	S_MORE_VAL,
	S_KEY,
	S_BODY,
	S_FIND_KEY,
	S_MESSAGE,
	S_END,
	S_COUNT,
} state_t;*/

typedef enum {
	L_STRING,
	L_COLON, // :
	L_SEMICOLON, // ;
	L_NEW_STRING, // '\n'	
	L_EMPTY_STRING, // spaces + '\0'
	L_CONT_VAL, // 'spaces + string'
	L_COUNT,
	L_ERR,
	L_SPACES,
} lexem_t;

typedef enum {
	S_HEADER,
	S_COLON,
	S_VALUE,
	S_SEMICOLON,,
	S_COUNT,
	S_ERR,
	S_END,
	S_CONT_VAL,
} state_t;

typedef int (*action_t)(const char *s, const char **end);

typedef struct {
	state_t state;
	action_t action;
} rule_t;

/*rule_t sintax[S_COUNT][L_COUNT] = {
//			L_SRTRING 		L_COLON 	L_SEMICOLON 	      L_EQUALLY 	L_BEGIN_KEY	L_END_KEY	L_NEW_STRING	L_CONTINUE_VAL 			L_EMPTY_STRING
S_HEADER		{S_COLON, get_header},	{S_ERR, NULL},	{S_ERR, NULL},	     {S_ERR, NULL},	{S_ERR, NULL},	{S_ERR, NULL},	{S_ERR, NULL},	{S_ERR, NULL},			{S_ERR, NULL},
S_COLON			{S_ERR, NULL},		{S_VALUE, NULL},{S_ERR, NULL},	     {S_ERR, NULL},	{S_ERR, NULL},	{S_ERR, NULL},	{S_ERR, NULL},	{S_ERR, NULL},			{S_ERR, NULL},
S_VALUE			{S_SEMICOLON, get_eml},	{S_ERR, NULL},	{S_ERR, NULL},	     {S_ERR, NULL},	{S_ERR, NULL},	{S_ERR, NULL},	{S_ERR, NULL},	{S_ERR, NULL},			{S_ERR, NULL},
S_CONT_VAL		{S_ERR, NULL},		{S_ERR, NULL},	{S_ERR, NULL},	     {S_ERR, NULL},	{S_ERR, NULL},	{S_ERR, NULL},	{S_ERR, NULL},	{S_SEMICOLON, take_prev_val},	{S_ERR, NULL},
S_SEMICOLON		{S_ERR, NULL},		{S_ERR, NULL},	{S_MORE_VAL, NULL},  {S_ERR, NULL},	{S_ERR, NULL},	{S_ERR, NULL},	{S_ERR, NULL},	{S_ERR, NULL},			{S_ERR, NULL},
S_MORE_VAL		{S_KEY, take_key},	{S_ERR, NULL},	{S_ERR, NULL},	     {S_ERR, NULL},	{S_ERR, NULL},	{S_ERR, NULL},	{S_ERR, NULL},	{S_ERR, NULL},			{S_ERR, NULL},
S_KEY			{S_ERR, NULL},		{S_ERR, NULL},	{S_ERR, NULL},	     {S_ERR, NULL},	{S_ERR, NULL},	{S_ERR, NULL},	{S_ERR, NULL},	{S_ERR, NULL},			{S_ERR, NULL},
S_BODY			{S_ERR, NULL},		{S_ERR, NULL},	{S_ERR, NULL},	     {S_ERR, NULL},	{S_ERR, NULL},	{S_ERR, NULL},	{S_ERR, NULL},	{S_ERR, NULL},			{S_ERR, NULL},
S_FIND_KEY		{S_ERR, NULL},		{S_ERR, NULL},	{S_ERR, NULL},	     {S_ERR, NULL},	{S_ERR, NULL},	{S_ERR, NULL},	{S_ERR, NULL},	{S_ERR, NULL},			{S_ERR, NULL},
S_MESSAGE		{S_ERR, NULL},		{S_ERR, NULL},	{S_ERR, NULL},	     {S_ERR, NULL},	{S_ERR, NULL},	{S_ERR, NULL},	{S_ERR, NULL},	{S_ERR, NULL},			{S_ERR, NULL},
}*/

/*rule_t sintax[S_COUNT][L_COUNT] = {
//			L_SRTRING 			L_COLON 	L_SEMICOLON 	     L_NEW_STRING		L_CONTINUE_VAL 			 	L_EMPTY_STRING
S_HEADER		{S_COLON, get_header},		{S_ERR, NULL},	{S_ERR, NULL},	     {S_COLON, get_header},	{S_ERR, NULL},			  	{S_BODY, NULL},
S_COLON			{S_ERR, NULL},			{S_VALUE, NULL},{S_ERR, NULL},	     {S_ERR, NULL},		{S_ERR, NULL},			  	{S_ERR, NULL},
S_VALUE			{S_SEMICOLON, get_value},	{S_ERR, NULL},	{S_ERR, NULL},	     {S_ERR, NULL},		{S_ERR, NULL},			 	{S_ERR, NULL},
S_CONT_VAL		{S_ERR, NULL},			{S_ERR, NULL},	{S_ERR, NULL},	     {S_ERR, NULL},		{S_SEMICOLON, record_to_prev_v},	{S_ERR, NULL},
S_SEMICOLON		{S_ERR, NULL},			{S_ERR, NULL},	{S_MORE_VAL, NULL},  {S_ERR, NULL},		{S_ERR, NULL},			  	{S_ERR, NULL},
S_MORE_VAL		{S_KEY, check_key},		{S_ERR, NULL},	{S_ERR, NULL},	     {S_ERR, NULL},		{S_ERR, NULL},			  	{S_BODY, NULL},
S_KEY			{S_HEADER, get_key},		{S_ERR, NULL},	{S_ERR, NULL},	     {S_ERR, NULL},		{S_ERR, NULL},			  	{S_ERR, NULL},
S_BODY			{S_ERR, NULL},			{S_ERR, NULL},	{S_ERR, NULL},	     {S_ERR, NULL},		{S_ERR, NULL},			  	{S_END, find_key},
}*/

/*S_CONT_VAL		{{S_ERR, NULL},			{S_ERR, NULL},		{S_ERR, NULL},  	{S_ERR, NULL},			{S_ERR, NULL}},			{S_ERR, NULL}*/

static int get_eml(const char *s, const char **end);

rule_t sintax[S_COUNT][L_COUNT] = {
//			L_SRTRING 			L_COLON 		L_SEMICOLON 	     	L_NEW_STRING			L_EMPTY_STRING			L_NEW_LINE_SPACES 
/*S_BEGIN*/		{{S_HEADER, NULL},		{S_ERR, NULL},		{S_ERR, NULL},	     	{S_ERR, NULL},			{S_ERR, NULL}, 			{S_ERR, NULL}}
/*S_HEADER*/		{{S_COLON, get_header},		{S_ERR, NULL},		{S_ERR, NULL},	     	{S_ERR, NULL},			{S_BODY, NULL},	 		{S_VALUE, NULL}}
/*S_COLON*/		{{S_ERR, NULL},			{S_VALUE, NULL},	{S_ERR, NULL},	     	{S_ERR, NULL},			{S_ERR, NULL},			{S_ERR, NULL}}
/*S_VALUE*/		{{S_SEMICOLON, get_value},	{S_ERR, NULL},		{S_ERR, NULL},		{S_ERR, NULL},			{S_ERR, NULL},			{S_ERR, NULL}}
/*S_SEMICOLON*/		{{S_ERR, NULL},			{S_ERR, NULL},		{S_VALUE, NULL},  	{S_HEADER, NULL},		{S_ERR, NULL},			{S_ERR, NULL}}
/*S_BODY*/		{{S_EXIT, find_key},		{S_ERR, NULL},		{S_ERR, NULL},	     	{S_ERR, NULL},			{S_EXIT, find_key},		{S_ERR, NULL}}
};


static lexem_t get_string(const char *s, const char **end) {
	const char *p = s + 1;
	while (*p != '\0' && *p != '"') {
		++p;
	}
	if (*p == '\0')
		return L_ERROR;
	*end = p + 1;
	return L_STRING;
}

static lexem_t get_lexem(const char *s, const char **end) {
	*end = s + 1;
	switch (*s): {
		case 's[0]':
		case '':
		case '\0': L_EMPTY_STRING;
	}
} 


// объединить эту функцию с функций ниже
// посмотреть, что считается строкой в этих тестах

static int get_eml(const char *s, const char **end. const char *res_str) {
	state_t state = S_BEGIN;	
	lexem_t lexem;
	if (*s == '\0') {
		lexem = L_EMPTY_STRING;
	}
	while (*s) {
		if () {
			;
		} else {
			lexem = get_lexem(s, end);
		}
		rule_t rule = syntax[state][lexem];
		if (rule.state == ERROR)
			return -1;
		if (rule.state == END )
			return 0;
		if (rule.action != NULL) {
			if (rule.action(s, end) == -1)
				return -1;
		}
		state = rule.state;
		s = end;
	}
	return -1;
}

int eml_parser(const char *path_to_file, const char *res_str) {
	if (path_to_file == NULL || res_str == NULL) {
		fprintf(stderr, "%s\n", "Incorect data format");
		return ERROR;
	}
	if (path_to_file[0] == '\0' || strlen(path_to_file) == 0) {
		fprintf(stderr, "%s\n", "The path to the file wasn't specified");
		return ERROR;
	}  
	FILE *fptr = fopen(path_to_file, "r");
    	if (fptr == NULL) {
	    	fprintf(stderr, "%s\n", "There is no access to the file");
	    	fclose(fptr);
	    	return ERROR;
   	}
	const char *end;
	const char *temp_res;
    	while (fscanf(fptr, "%s", temp_res) != EOF) {
		if (get_eml(temp_res, &end, res_str) == ERROR) {
			fprintf(stderr, "%s\n", "The incorrect file was transmitted");
			return ERROR;
		}
		if (*end != '\0') {
			return ERROR;
		}
		// *res_str += temp_str; удаляем всё ненужное из temp_str и записывем в res_str
    	}
	fclose(fptr);
	return 0;
}

int main(int argc, const char **argv) {
    if (argc != 2) {
        return ERROR;
    }
    const char *path_to_eml = argv[1];
    const char *res_str = "";
    if(eml_parser(path_to_eml, res_str) != 0) {
	    perror("ERROR");
	    return ERROR;
    }
    puts("SUCCESS");
    puts(res_str);
    return 0;
}
