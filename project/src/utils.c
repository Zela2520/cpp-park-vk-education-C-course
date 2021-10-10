#include <stdio.h>
#include "utils.h"

size_t timer_from(int from) {
    size_t counter = 0;
    for (int i = from; i >= 0; --i) {
        ++counter;
	if(i == 0) {
		printf("%d", i);
	} else {
		printf("%d ", i);
	}
    }
    if (counter != 0) {
    	printf("\n");
    }
    return counter;
}

// TODO(daniil-zzz@mail.ru): Implement `power of` function

int custom_pow(int base, int power) {
	int res = 1;
	int currentPower = base;
	while (power > 0) {
	if (power % 2 == 1) {
		res *= currentPower;
	}
	currentPower *= currentPower;
	power = power >> 1;
	}
    return res;
}

