#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

// создаём пользовательский тип данных для хранения записей об объектах
struct masterRecord {
	int Number;
       	char Name[20];
	char Surname[20];
	char addres[30];
	char TelNumber[15];
	double indebtedness;
	double credit_limit;
	double cash_payments;
};

// создаём псевдоним для пользовательского типа данных
typedef struct masterRecord Data;


int main(void) {
	// выполним объявление необходимых переменных, функций и потоков
	int choice;
	void masterWrite(FILE *ofPTR, Data Client),
	     transactionWrite(FILE *ofPTR, Data transfer),
	     blackRecord(FILE *ofPTR, FILE *ofPTR_2, FILE *blackrecord, Data client_data, Data transfer);
	FILE *Ptr, *Ptr_2, *blackrecord;
	// выполним инициализацию экземпляров структуры
	Data client_data = {0};
	Data transfer = {0};
	printf("%s", "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
	// производим выбранные пользователем действия над потоками
	while (scanf("%d", &choice) != -1) {
		switch(choice) {
			case 1:
				// Записываем в файл для хранения данных о клиенте
				Ptr = fopen("record.dat", "r+");
				if (Ptr == NULL) {
					puts("Not aсcess");
				} else {
					masterWrite(Ptr, client_data);
					fclose(Ptr);
				}
				break;
			case 2:
				// Записываем в файл для хранения данных о переводах
				Ptr = fopen(filename, "r+");
				if (Ptr == NULL) {
					puts("Not aсcess");
				} else {
					transactionWrite(Ptr, transfer);
					fclose(Ptr);
				}
				break;
			case 3:
				// Считываем данные о клиенте и его переводах
				// из соответствующих файлов.
				// На основе выполненных клиентом платежей
				// формируем кредитный лимит каждого клиента
				Ptr = fopen("record.dat", "r");
				Ptr_2 = fopen("transaction.dat", "r");
				blackrecord = fopen("blackrecord.dat", "w");
				if (Ptr == NULL || Ptr_2 == NULL) {
					puts("exit");
				} else {
					blackRecord(Ptr, Ptr_2, blackrecord, client_data, transfer);
					fclose(Ptr);
					fclose(Ptr_2);
					fclose(blackrecord);
				}
				break;
			default:
				puts("error");
				break;
		}
		printf("%s", "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
	}
	return 0;
}


// выполним определение соответствующих функций
void masterWrite(FILE *ofPTR, Data Client) {
	printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
			"1 Number account: ",
			"2 Client name: ",
			"3 Surname: ",
			"4 Addres client: ",
			"5 Client Telnum: ",
			"6 Client indebtedness: ",
			"7 Client credit limit: ",
			"8 Client cash payments: "
	);
	while (scanf("%12d%20s%20s%30s%15s%lf%lf%lf",
				&Client.Number,
				Client.Name,
				Client.Surname,
				Client.addres,
				Client.TelNumber,
				&Client.indebtedness,
				&Client.credit_limit,
				&Client.cash_payments) != -1) {
		fprintf(ofPTR, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
				Client.Number,
				Client.Name,
				Client.Surname,
				Client.addres,
				Client.TelNumber,
				Client.indebtedness,
				Client.credit_limit,
				Client.cash_payments);
		printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
				"1 Number account: ",
				"2 Client name: ",
				"3 Surname: ",
				"4 Addres client: ",
				"5 Client Telnum: ",
				"6 Client indebtedness: ",
				"7 Client credit limit: ",
				"8 Client cash payments:");
	}
}


void transactionWrite(FILE *ofPtr, Data transfer) {
	printf("%s\n%s\n",
			"1 Number account: ",
			"2 Client cash payments: ");
	while (scanf("%d %lf", &transfer.Number, &transfer.cash_payments) != -1) {
		fprintf(ofPtr, "%-3d%-6.2f\n", transfer.Number, transfer.cash_payments);
		printf("%s\n%s\n",
				"1 Number account:",
				"2 Client cash payments: ");
	}
}


void blackRecord(FILE *ofPTR, FILE  *ofPTR_2, FILE *blackrecord, Data client_data, Data transfer) {
	while (fscanf(ofPTR, "%12d%20s%20s%30s%15s%lf%lf%lf",
				&client_data.Number,
				client_data.Name,
				client_data.Surname,
				client_data.addres,
				client_data.TelNumber,
				&client_data.indebtedness,
				&client_data.credit_limit,
				&client_data.cash_payments) != -1) {
		while (fscanf(ofPTR_2, "%d %lf", &transfer.Number, &transfer.cash_payments) != -1) {
			if(client_data.Number == transfer.Number && transfer.cash_payments != 0) {
				client_data.credit_limit += transfer.cash_payments;
			}
		}
		fprintf(blackrecord, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
				client_data.Number,
				client_data.Name,
				client_data.Surname,
				client_data.addres,
				client_data.TelNumber,
				client_data.indebtedness,
				client_data.credit_limit,
				client_data.cash_payments);
		rewind(ofPTR_2);
	}
}
