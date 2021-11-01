#include <stdio.h>

void print_numbers_in_range(int begin, int end) {
	if (begin == end) {
		printf("%d", begin);
		return;
	}
	printf("%d ", begin);
	if (end > begin) {
		++begin;
	} else {
		--begin;
	}
	print_numbers_in_range(begin, end);
}
