#include "print.h"
#include <stdio.h>

void display(int cur_num, int n) {
	if (cur_num == n) {
		printf("%d", cur_num);
		return;
	}
	printf("%d ", cur_num);
	if (n > 0) {
		cur_num++;
	} else {
		cur_num--;
	}
	display(cur_num, n);
}
