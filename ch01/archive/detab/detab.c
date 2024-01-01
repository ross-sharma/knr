#include "stdio.h"
#include "stdlib.h"

int get_line(char* buf, int buf_len);

int main(int argc, char** argv) {
	int buf_len = 1000;
	int num_read;
	char* buf;

	if (argc > 1) {
		buf_len = atoi(argv[1]);
		if (buf_len == 0) {
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

	buf[0] = '\0';

	while (1) {
		c = getchar();

		if (c == EOF) break;
		if (i == buf_len - 2) continue;

		buf[i] = c;

		if (c == '\n') {
			break;
		}

		++i;
	}
	
	buf[i+1] = '\0';
	return i;
}

