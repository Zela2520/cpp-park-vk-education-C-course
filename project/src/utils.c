#include <stdio.h>
#include <stddef.h>
#include "utils.h"

size_t timer_from(unsigned char from) {
    size_t counter = 0;
    for (unsigned char i = from; i >= 1; --i) {
        ++counter;
        printf("%c", i);
    }
    return counter;
}

// TODO: Implement `power of` function
/*
int custom_pow(int base, int power) {
    return 0;
}
*/
