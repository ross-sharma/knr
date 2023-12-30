#include <stdio.h>

#define BUFFER_LEN 1000

int get_line(char line[], int maxline);
int reverse(char line[], char output[], int len);

int main() {
	int len;
	char line[BUFFER_LEN];
	char reversed[BUFFER_LEN];

	while ((len = get_line(line, BUFFER_LEN)) > 0) {
		int newlen = reverse(line, reversed, len);
		printf("%s\n", reversed);
	}

	return 0;
}

int get_line(char line[], int maxline) {
	int c, i = -1;

    while  ( (c = getchar()) != EOF ) {
        ++i;
        line[i] = c;
        if (c == '\n') break;
        if (i == maxline-2) break;
	}

	while (c != '\n' && c != EOF) {
		c = getchar();
	}

	line[i+1] = '\0';
	return i+1;
}

int reverse(char line[], char output[], int len) {
	int has_newline = 0;
	char c;
	int j = 0;

	for (int i = len-1; i >= 0; i--) {
		c = line[i];	
		if (c != '\n') {
			output[j++] = c;
		}
	}

	output[j] = '\0';
	return j;
}

