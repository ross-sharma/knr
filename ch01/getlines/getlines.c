#include "stdio.h"
#include "stdlib.h"

int get_line(char* buf, int buf_len);


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
	const int max_i = buf_len - 2;
	int c;
	int i = -1;
	int num_read = 0;

	buf[0] = '\0';

	while (1) {
		c = getchar();
		if (c == EOF) break;
		++num_read;

		const int is_newline = c == '\n';
		const int next_i = (i+1 <= max_i) ? i+1 : max_i;
		const int is_overwrite = (next_i == i);

		i = next_i;
		if (is_newline || !is_overwrite) buf[i] = c;
		if (is_newline) break;
	}

	buf[i+1] = '\0';
	return num_read;
}

