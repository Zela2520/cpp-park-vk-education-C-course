#ifndef PROJECT_INCLUDE_RECORD_H_
#define  PROJECT_INCLUDE_RECORD_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "information.h"

// создаём пользовательский тип данных для хранения записей об объектах
typedef struct {
	int Number;
       	char Name[20];
	char Surname[20];
	char addres[30];
	char TelNumber[15];
	double indebtedness;
	double credit_limit;
	double cash_payments;
} Data;

int fromTheStream(FILE *fptr, Data *data, const char *filename);
void intoTheStream(FILE *fptr, Data data, const char *filename);
void writeToFile(const char *filename, Data data);
void readFromFile(const char *filename_1, const char *filename_2, Data client, Data transfer);

#endif  // PROJECT_INCLUDE_RECORD_H_
