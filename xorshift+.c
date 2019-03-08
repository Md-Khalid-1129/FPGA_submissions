#include <stdio.h>
#include <stdint.h>
#define N 20

uint64_t state[2] = {4, 3};

uint64_t xor_shift_128_plus() {
	uint64_t x = state[0];
	uint64_t const y = state[1];
	state[0] = y;
	x = (x) ^ (x << 23);
	state[1] = x ^ y ^ (x >> 17) ^ (x >>26);
	return state[1] + y;
}

int main() {
	for (int i = 0; i < N; i++) {
		printf("%ld\n", xor_shift_128_plus());
	}
	return 0;
}