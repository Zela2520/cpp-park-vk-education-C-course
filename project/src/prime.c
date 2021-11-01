#define YES 1
#define NO  0

int is_prime(int number) {
	if (number < 2) {
		return 0;
	}
	int number_is_prime = YES;
	for (int i = 2; i * i <= number; ++i) {
		if (number % i == 0) {
			number_is_prime = NO;
			break;
		}
	}
	return number_is_prime;
}
