#include "record.h"

void writeToFile(const char *filename, Data data) {
	FILE *fptr = fopen(filename, "r+");
	if (fptr == NULL) {
		puts("Not access");
	} else {
		while (fromTheStream(stdin, &data, filename) != -1) {
			intoTheStream(fptr, data, filename);
		}
		fclose(fptr);
	}
}

void readFromFile(const char *filename_1, const char *filename_2, Data client, Data transfer) {
	FILE *fptr_1 = fopen(filename_1, "r");
	FILE *fptr_2 = fopen(filename_2, "r");
	FILE *fptr_3 = fopen("blackrecord.dat", "w");
	if (fptr_1 == NULL || fptr_2 == NULL) {
		puts("Not access");
	} else {
		while (fromTheStream(fptr_1, &client, filename_1) != -1) {
			while (fromTheStream(fptr_2, &transfer, filename_2) != -1) {
				if (client.Number == transfer.Number && transfer.cash_payments != 0) {
					client.credit_limit += transfer.cash_payments;
				}
			}
			intoTheStream(fptr_3, client, "blackrecord.dat");
			rewind(fptr_2);
		}
		fclose(fptr_1);
		fclose(fptr_2);
	  }
	fclose(fptr_3);
}
