#include "record.h"


int main(void) {
	// выполним объявление необходимых переменных и потоков
	int choice;
	FILE *Ptr, *Ptr_2, *blackrecord;
	// выполним инициализацию экземпляров структуры
	Data client_data = {0};
	Data transfer = {0};
	actionsInformation();
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
				Ptr = fopen("transaction.dat", "r+");
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
		actionsInformation();
	}
	return 0;
}
