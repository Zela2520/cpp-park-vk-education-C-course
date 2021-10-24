#include "record.h"

void write_to_file(const char *writing_file_name, Data reading_data) {
	FILE *writing_file = fopen(writing_file_name, "r+");
	if (writing_file == NULL) {
		puts("There is no access to the file");
	} else {
		while (read_from_the_stream(stdin, &reading_data, writing_file_name) != -1) {
			write_into_the_stream(writing_file, reading_data, writing_file_name);
		}
		fclose(writing_file);
	}
}

void read_from_file(const char *reading_client_filename,
		const char *reading_transfer_filename,
		Data writing_clients_data,
		Data writing_transfers_data) {
	FILE *off_client_fptr = fopen(reading_client_filename, "r");
	FILE *off_transfer_fptr = fopen(reading_transfer_filename, "r");
	FILE *into_record_fptr = fopen("blackrecord.dat", "w");
	if (off_client_fptr == NULL || off_transfer_fptr == NULL) {
		puts("There is no access to the file");
	} else {
		while (read_from_the_stream(off_client_fptr,
					&writing_clients_data,
					reading_client_filename) != -1) {
			while (read_from_the_stream(off_transfer_fptr,
						&writing_transfers_data,
						reading_transfer_filename) != -1) {
				if (writing_clients_data.number == writing_transfers_data.number &&
						writing_transfers_data.cash_payments != 0) {
					writing_clients_data.credit_limit += writing_transfers_data.cash_payments;
				}
			}
			write_into_the_stream(into_record_fptr, writing_clients_data, "blackrecord.dat");
			rewind(off_transfer_fptr);
		}
		fclose(off_client_fptr);
		fclose(off_transfer_fptr);
	  }
	fclose(into_record_fptr);
}
