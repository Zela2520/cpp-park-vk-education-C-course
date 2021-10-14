#include "display.h"
#include <stdio.h>

void display(int beginning_of_range, int end_of_range) {
	if (beginning_of_range == end_of_range) {
		printf("%d", beginning_of_range);
		return;
	}
	printf("%d ", beginning_of_range);
	if (end_of_range > 0) {
		++beginning_of_range;
	} else {
		--beginning_of_range;
	}
	display(beginning_of_range, end_of_range);
}
