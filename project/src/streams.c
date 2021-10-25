#include "record.h"

#define ERROR (-1)

int read_from_the_stream(FILE *off_fptr, Data *writing_data, const char *reading_file) {
	if (strncmp(reading_file, "record.dat", 5) == 0 ||
			strncmp(reading_file, "blackrecord.dat", 5) == 0 ||
			strncmp(reading_file, "test.dat", 5) == 0) {
		clients_information();
		return fscanf(off_fptr, "%12d%20s%20s%30s%15s%lf%lf%lf",
				&writing_data->number, writing_data->name,
				writing_data->surname, writing_data->addres,
				writing_data->tel_number, &writing_data->indebtedness,
				&writing_data->credit_limit, &writing_data->cash_payments);
	} else if (strncmp(reading_file, "transaction.dat", 5) == 0) {
		transactions_information();
		return fscanf(off_fptr, "%d %lf",
				&writing_data->number,
				&writing_data->cash_payments);
	}
	return ERROR;
}

void write_into_the_stream(FILE *into_fptr, Data reading_data, const char *writing_file) {
	if (strncmp(writing_file, "record.dat", 5) == 0 ||
			strncmp(writing_file, "blackrecord.dat", 5) == 0 ||
			strncmp(writing_file, "test.dat", 5) == 0) {
		fprintf(into_fptr, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
				reading_data.number, reading_data.name,
				reading_data.surname, reading_data.addres,
				reading_data.tel_number, reading_data.indebtedness,
				reading_data.credit_limit, reading_data.cash_payments);
	} else if (strncmp(writing_file, "transaction.dat", 5) == 0) {
		fprintf(into_fptr, "%-3d%-6.2f\n", reading_data.number, reading_data.cash_payments);
	}
}
