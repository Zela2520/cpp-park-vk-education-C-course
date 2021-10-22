#include "record.h"

int fromTheStream(FILE *fptr, Data *data, const char *filename) {
	if (strcmp(filename, "record.dat") == 0 ||
			strcmp(filename, "blackrecord.dat") == 0 ||
			strcmp(filename, "test.dat") == 0) {
		clientsInformation();
		return fscanf(fptr, "%12d%20s%20s%30s%15s%lf%lf%lf",
				&data->Number,
				data->Name,
				data->Surname,
				data->addres,
				data->TelNumber,
				&data->indebtedness,
				&data->credit_limit,
				&data->cash_payments);
	} else if (strcmp(filename, "transaction.dat") == 0) {
		transactionsInformation();
		return fscanf(fptr, "%d %lf", &data->Number, &data->cash_payments);
	}
	return -1;
}

void intoTheStream(FILE *fptr, Data data, const char *filename) {
	if (strcmp(filename, "record.dat") == 0 ||
			strcmp(filename, "blackrecord.dat") == 0 ||
			strcmp(filename, "test.dat") == 0) {
		fprintf(fptr, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
				data.Number,
				data.Name,
				data.Surname,
				data.addres,
				data.TelNumber,
				data.indebtedness,
				data.credit_limit,
				data.cash_payments);
	} else if (strcmp(filename, "transaction.dat") == 0) {
		fprintf(fptr, "%-3d%-6.2f\n", data.Number, data.cash_payments);
	}
}
