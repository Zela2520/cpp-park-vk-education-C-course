#ifndef PROJECT_INCLUDE_MAIN_MODULE_H_
#define PROJECT_INCLUDE_MAIN_MODULE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void writeToTestFile(const char *filename, Data givenData);
void readFromTestFile(const char *filename, Data *getData);
int testFunction(Data expectedData, Data getData);

#endif  // PROJECT_INCLUDE_MAIN_MODULE_H_
