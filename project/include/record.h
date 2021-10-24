#ifndef PROJECT_INCLUDE_RECORD_H_
#define  PROJECT_INCLUDE_RECORD_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "information.h"

// создаём пользовательский тип данных для хранения записей об объектах
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

int read_from_the_stream(FILE *off_fptr, Data *writing_data, const char *reading_file);
void write_into_the_stream(FILE *into_fptr, Data reading_data, const char *writing_file);
void read_from_file(const char *reading_client_filename,
		const char *reading_transfer_filename,
		Data writing_clients_data,
		Data writing_transfers_data);
void write_to_file(const char *writing_file_name, Data reading_data);

#endif  // PROJECT_INCLUDE_RECORD_H_
