#include "record.h"

#define WRITE_CLIENT_DATA 1
#define WRITE_TRANSFER_DATA 2
#define READ_CLIENT_DATA 3

int main(void) {
	int choice;
	// выполним инициализацию экземпляров структуры
	Data client_data = {0};
	Data transfer = {0};
	actions_information();
	// производим выбранные пользователем действия над потоками
	while (scanf("%d", &choice) != EOF) {
		switch(choice) {
			case WRITE_CLIENT_DATA:
				// Записываем в файл для хранения данных о клиенте
				write_to_file("record.dat", client_data);
				break;
			case WRITE_TRANSFER_DATA:
				// Записываем в файл для хранения данных о переводах
				write_to_file("transaction.dat", transfer);
				break;
			case READ_CLIENT_DATA:
				// Считываем данные о клиенте и его переводах
				// из соответствующих файлов.
				// На основе выполненных клиентом платежей
				// формируем кредитный лимит каждого клиента
				read_from_file("record.dat", "transaction.dat", client_data, transfer);
				break;
			default:
				puts("error");
				break;
		}
		actions_information();
	}
	return 0;
}
