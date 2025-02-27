#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TYPE  float
#define PRINT_TYPE printf("%f\n", x);
#define FLOAT_TYPE

#define die(...) do { printf(__VA_ARGS__);exit(255); } while(0);

#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#endif


void print_byte(char b) {
	for (char i = 7; i >= 0; i--) {
		char mask = 1 << i;
		char result = b & mask;
		putchar(0 == result ? '0' : '1');
		if (i == 4) putchar('.');
	}
}

void print_bits(void* x, unsigned int n_bytes) {
	char* start_byte = (char*)x;
	for (char* cur_byte = start_byte + n_bytes - 1; cur_byte >= start_byte; cur_byte--) {
		print_byte(*cur_byte);
		putchar(' ');
	}
	printf("\n");
}

void set_bit(void* x, unsigned int position, int on) {
	char* writep = (char*)x + (position / 8);
	char mask = 1 << (position % 8);

	if (0 == on) {
		mask = ~mask;
		*writep =  mask & (*writep);
	}
	else {
		*writep =  mask | (*writep);
	}
}

unsigned int strLen(char* input) {
	unsigned int i = 0;
	while (*input != 0) {
		input++;
		i++;
	}
	return i;
}

void reverse(char* input, char* output) {
	unsigned int len = strLen(input);
	for (int i = 0; i < len; i++) {
		int inIndex = len - i - 1;
		output[i] = input[inIndex];
	}		
}

void filter(char* str) {
	char* left = str;
	char* right = str;
	while (*right) {
		if (*right == '0' || *right == '1') {
			*left = *right;
			left++;
		}
		right++;
	}
	*left = 0;
}

TYPE binStrToType(char* str) {

	char buf[100];
	memset(buf, '\0', 100 * sizeof(char) );

	reverse(str, buf);
	filter(buf);
	unsigned int len = strLen(buf);
	if (len > sizeof(TYPE)*8) {
		die("binary string too long: %d chars.\n'%s'\n", len, buf);
	}

	TYPE result = 0;
	unsigned int pos = 0;
	char c = 0;
	while( (c = buf[pos]) ) {
		if (c == '1') set_bit(&result, pos, 1);
		else if (c == '0') set_bit(&result, pos, 0);
		else die("Unexpected char %c (%d)", c, c);
		pos++;
	}

	return result;
}


void runFloat(char* bitStr) {
	unsigned int nBytes = sizeof(TYPE);
	TYPE x = binStrToType(bitStr);
	print_bits(&x, nBytes);
	PRINT_TYPE;
	putchar('\n');
}


void main_float(unsigned int nBytes, unsigned int nBits) {
	printf("\n=== FLOAT ===\n\n");
	runFloat("1 0111.1111 | 000.0000 0000.0000 0000.0000");
	runFloat("1 1000.0000 | 000.0000 0000.0000 0000.0000");
	runFloat("1 1000.0001 | 000.0000 0000.0000 0000.0000");
	runFloat("0 1000.0010 | 000.0000 0000.0000 0000.0000");
	runFloat("0 1000.0011 | 000.0000 0000.0000 0000.0000");
	runFloat("0 1000.0100 | 000.0000 0000.0000 0000.0000");
	runFloat("0 1000.0100 | 100.0000 0000.0000 0000.0000");
}

void tests() {
	assert(strLen("") == 0);
	assert(strLen("0") == 1);
	assert(strLen("00") == 2);
}


int main() {
	tests();

	TYPE x = 127;
	unsigned int n_bytes = sizeof(TYPE);
	unsigned int n_bits = n_bytes * 8;

	for (int i = 0; i < n_bits - 1;) set_bit(&x, i++, 0);
	set_bit(&x, 0, 1);
	print_bits(&x, n_bytes);
	PRINT_TYPE;
	putchar('\n');

	x = 0;
	for (int i = 0; i < n_bits - 1;) set_bit(&x, i++, 1);
	print_bits(&x, n_bytes);
	PRINT_TYPE;
	putchar('\n');

	x = 0;
	set_bit(&x, n_bits-1, 1);
	print_bits(&x, n_bytes);
	PRINT_TYPE;
	putchar('\n');

	for (int i = 0; i < n_bits;) set_bit(&x, i++, 1);
	print_bits(&x, n_bytes);
	PRINT_TYPE;
	putchar('\n');

	#ifdef FLOAT_TYPE
	main_float(n_bytes, n_bits);
	#endif

	printf("\n\nDone\n");

	return 0;
}

