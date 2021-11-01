#include <stdio.h>
#include <stddef.h>

size_t timer_from(int from) {
	size_t ticks_count = 0;
    	for (int i = from; i > 0; --i) {
        	++ticks_count;
		printf("%d ", i);
    	}
    	if (ticks_count != 0) {
	    	puts("0");
		++ticks_count;
    	}
    	return ticks_count;
}


int custom_pow(int base, int power) {
	while (power < 0) {
		puts("Incorrect input data.\nPlease try again.");
		scanf("%i", &power);
	}
	int result = 1;
	int current_power = base;
	while (power > 0) {
		if (power % 2 == 1) {
			result *= current_power;
		}
		current_power *= current_power;
		power = power >> 1;
	}
	return result;
}

