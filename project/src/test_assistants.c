#include "test_module.h"

#define SUCCESS 0
#define ERROR 1

void write_to_test_file(const char *writing_file_name, Data reading_data) {
	FILE *into_fptr = fopen(writing_file_name, "a+");
	if (into_fptr == NULL) {
		puts("There is no access to the file");
	} else {
		fprintf(into_fptr, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
				reading_data.number,
				reading_data.name,
				reading_data.surname,
				reading_data.addres,
				reading_data.tel_number,
				reading_data.indebtedness,
				reading_data.credit_limit,
				reading_data.cash_payments);
		fclose(into_fptr);
	}
}

void read_from_test_file(const char *reading_file_name, Data *writing_data) {
	FILE *off_fptr = fopen(reading_file_name, "r");
	if (off_fptr == NULL) {
		puts("There is no access to the file");
	} else {
		fscanf(off_fptr, "%12d%20s%20s%30s%15s%lf%lf%lf",
				&writing_data->number,
				writing_data->name,
				writing_data->surname,
				writing_data->addres,
				writing_data->tel_number,
				&writing_data->indebtedness,
				&writing_data->credit_limit,
				&writing_data->cash_payments);
		fclose(off_fptr);
	}
}

int test_function(Data expected_data, Data recived_data) {
	if (expected_data.number == recived_data.number &&
        strncmp(expected_data.name, recived_data.name, 5) == 0 &&
        strncmp(expected_data.surname, recived_data.surname, 5) == 0 &&
        strncmp(expected_data.addres, recived_data.addres, 5) == 0 &&
        strncmp(expected_data.tel_number, recived_data.tel_number, 5) == 0 &&
        expected_data.indebtedness == recived_data.indebtedness &&
        expected_data.credit_limit == recived_data.credit_limit &&
        expected_data.cash_payments == recived_data.cash_payments) {
        return SUCCESS;
    } else {
        return ERROR;
    }
}
