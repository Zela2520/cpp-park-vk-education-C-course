#ifndef PROJECT_INCLUDE_TEST_MODULE_H_
#define PROJECT_INCLUDE_TEST_MODULE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int number;
       	char name[20];
	char surname[20];
	char addres[30];
	char tel_number[15];
	double indebtedness;
	double credit_limit;
	double cash_payments;
} Data;

void write_to_test_file(const char *writing_file_name, Data reading_data);
void read_from_test_file(const char *reading_file_name, Data *writing_data);
int test_function(Data expected_data, Data recived_data);

#endif  // PROJECT_INCLUDE_TEST_MODULE_H_
