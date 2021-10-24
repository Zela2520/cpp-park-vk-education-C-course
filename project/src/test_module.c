#include "test_module.h"

int main() {
	const char *filename = "test.dat";
	Data expected_data = {2000,
		"Daniil",
		"Zelenko",
		"Academica Anochina",
		"89165555055",
		80.00,
		20.00,
		200
       	};
	write_to_test_file(filename, expected_data);
	Data recived_data = {0};
	read_from_test_file(filename, &recived_data);
	return test_function(expected_data, recived_data);
}
