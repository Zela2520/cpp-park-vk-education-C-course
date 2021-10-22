#include "main_module.h"

void writeToTestFile(const char *filename, Data givenData) {
	FILE *fptr = fopen(filename, "a+");
	if (fptr == NULL) {
		puts("Not access");
	} else {
		fprintf(fptr, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
				givenData.Number,
				givenData.Name,
				givenData.Surname,
				givenData.addres,
				givenData.TelNumber,
				givenData.indebtedness,
				givenData.credit_limit,
				givenData.cash_payments);
		fclose(fptr);
	}
}

void readFromTestFile(const char *filename, Data *getData) {
	FILE *fptr = fopen(filename, "r");
	if (fptr == NULL) {
		puts("Not access");
	} else {
		fscanf(fptr, "%12d%20s%20s%30s%15s%lf%lf%lf",
				&getData->Number,
				getData->Name,
				getData->Surname,
				getData->addres,
				getData->TelNumber,
				&getData->indebtedness,
				&getData->credit_limit,
				&getData->cash_payments);
		fclose(fptr);
	}
}

int testFunction(Data expectedData, Data getData) {
	if (expectedData.Number == getData.Number &&
        strcmp(expectedData.Name, getData.Name) == 0 &&
        strcmp(expectedData.Surname, getData.Surname) == 0 &&
        strcmp(expectedData.addres, getData.addres) == 0 &&
        strcmp(expectedData.TelNumber, getData.TelNumber) == 0 &&
        expectedData.indebtedness == getData.indebtedness &&
        expectedData.credit_limit == getData.credit_limit &&
        expectedData.cash_payments == getData.cash_payments) {
        return 0;
    } else {
        return 1;
    }
}
