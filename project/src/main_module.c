#include "main_module.h"


int main() {
	const char *filename = "test.dat";
	Data expectedData = {2000,
		"Daniil",
		"Zelenko",
		"Academica Anochina",
		"89165555055",
		80.00,
		20.00,
		200
       	};
	writeToTestFile(filename, expectedData);
	Data gotData = {0};
	readFromTestFile(filename, &gotData);
	return testFunction(expectedData, gotData);
}
