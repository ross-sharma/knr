#include "stdio.h"
#include "stdlib.h"

int get_line(char* buf, int buf_len);
int increment(int i, int buf_len);


int main(int argc, char** argv) {
	int buf_len = 1000;
	int num_read;
	char* buf;

	if (argc > 1) {
		buf_len = atoi(argv[1]);
		if (buf_len < 2) {
			fprintf(stderr, "Invalid buffer length argument: %s\n", argv[1]);
			return 1;
		}
	}

	buf = (char*)malloc(buf_len);

	while (1) {
		num_read = get_line(buf, buf_len);
		if (num_read == 0) break;
		printf("%s", buf);
	}

	free(buf);
}


int get_line(char* buf, int buf_len) {
	int c;
	int i = 0;
	int num_read = 0;
	int is_newline;

	buf[0] = '\0';

	while (1) {
		c = getchar();
		if (c == EOF) break;

		is_newline = c == '\n';
		buf[i] = c;
		++num_read;
		i = increment(i, buf_len);
		if (is_newline) break;
	}

	buf[i+1] = '\0';
	return num_read;
}


int increment(int i, int buf_len) {
	int max = buf_len - 2;
	if (i+1 <= max) return i+1;
	return max;
}

