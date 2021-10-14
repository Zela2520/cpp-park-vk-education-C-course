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


int custom_pow(int base, int power) {
	int result = 1;
	int currentPower = base;
	while (power > 0) {
		// смотрим чему равен последний бит числа в двоичном представлении
		if (power % 2 == 1) {  // если последний бит равен единицы, то он участвует в двоичном разложение числа
			result *= currentPower;  // добавим соответствующую степень двойки к результату
		}
		currentPower *= currentPower;
		power = power >> 1;  // переходим к обработке следующего бита
	}
	return result;
}

