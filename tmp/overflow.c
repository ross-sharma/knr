#include <stdio.h>

#define TYPE  float
#define PRINT_TYPE printf("%f\n", x);

//#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#endif


void print_byte(char* b) {
	for (char i = 7; i >= 0; i--) {
		char mask = (char)1 << i;
		char result = (*b) & mask;
		putchar(0 == result ? '0' : '1');
	}
}

void print_bits(void* x, unsigned short n_bytes) {
	DEBUG_PRINT("print_bits %d\n", n_bytes);
	char* start_byte = (char*)x;
	char* cur_byte = start_byte + (n_bytes - 1);

	while (cur_byte >= start_byte) {
		print_byte(cur_byte);
		putchar(' ');
		cur_byte--;
	}
	printf("\n");
}

void set_bit(void* x, unsigned short position) {
	DEBUG_PRINT("set %d\n", position);
	unsigned short bitpos = position % 8;
	unsigned char mask = 1 << bitpos;
	char* writep = (char*)x + (position/8);
	*writep = mask | *(writep);
}

void unset_bit(void* x, unsigned short position) {
	DEBUG_PRINT("unset %d\n", position);
	unsigned short bitpos = position % 8;
	unsigned char mask = 0xff - (1 << bitpos);
	char* writep = (char*)x + (position/8);
	*writep = mask & *(writep);
}

int main() {
	TYPE x = 0;
	unsigned short n_bytes = (unsigned short) sizeof(TYPE);
	unsigned short n_bits = n_bytes * 8;

	set_bit(&x, 0);
	print_bits(&x, n_bytes);
	PRINT_TYPE;
	putchar('\n');

	x = 1;
	for (unsigned short i = 0; i < n_bits - 1; i++) set_bit(&x, i);
	print_bits(&x, n_bytes);
	PRINT_TYPE;
	putchar('\n');

	x = 0;
	set_bit(&x, n_bits-1);
	print_bits(&x, n_bytes);
	PRINT_TYPE;
	putchar('\n');

	for (unsigned short i = 0; i < n_bits; i++) set_bit(&x, i);
	print_bits(&x, n_bytes);
	PRINT_TYPE;
	putchar('\n');

	return 0;
}


