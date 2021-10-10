#include "prime.h"

int is_prime(int number) {
	if (number == 1 || number == 0) {
		return 0;
	}
	if (number < 0) {
		return 0;
	}
	for (int i = 2; i * i <= number; ++i) {
		if(number % i == 0) {
			return 0;
		}
	}
	return 1;
}
