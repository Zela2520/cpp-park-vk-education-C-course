#include "record.h"

int main(void) {
	int choice;
	// выполним инициализацию экземпляров структуры
	Data client_data = {0};
	Data transfer = {0};
	actionsInformation();
	// производим выбранные пользователем действия над потоками
	while (scanf("%d", &choice) != -1) {
		switch(choice) {
			case 1:
				// Записываем в файл для хранения данных о клиенте
				writeToFile("record.dat", client_data);
				break;
			case 2:
				// Записываем в файл для хранения данных о переводах
				writeToFile("transaction.dat", transfer);
				break;
			case 3:
				// Считываем данные о клиенте и его переводах
				// из соответствующих файлов.
				// На основе выполненных клиентом платежей
				// формируем кредитный лимит каждого клиента
				readFromFile("record.dat", "transaction.dat", client_data, transfer);
				break;
			default:
				puts("error");
				break;
		}
		actionsInformation();
	}
	return 0;
}
