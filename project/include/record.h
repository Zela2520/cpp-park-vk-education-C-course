#ifndef PROJECT_INCLUDE_RECORD_H_
#define  PROJECT_INCLUDE_RECORD_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void masterWrite(FILE *ofPTR, Data Client);
void transactionWrite(FILE *ofPTR, Data transfer);
void blackRecord(FILE *ofPTR, FILE *ofPTR_2, FILE *blackrecord, Data client_data, Data transfer);




#endif  // PROJECT_INCLUDE_RECORD_H_
