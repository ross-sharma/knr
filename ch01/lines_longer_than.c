#include <stdio.h>

#define BUFFER_LEN 1000
#define CHAR_LIMIT 80

int get_line(char line[], int maxline);

int main() {
	int len;
	char line[BUFFER_LEN];
	char longest[BUFFER_LEN];

	while ((len = get_line(line, BUFFER_LEN)) > 0) {
		if (len > CHAR_LIMIT) {
			printf("(%d chars): %s\n", len, line); 
		}
	}

	return 0;
}

int get_line(char line[], int maxline) {
	int c, i;
    i = -1;
        

    while  ( (c = getchar()) != EOF ) {
        ++i;
        line[i] = c;
        if (c == '\n') break;
        if (i == maxline-2) break;
	}

	line[i+1] = '\0';

    while (c != EOF && c != '\n') {
        ++i;
        c = getchar();
    }

	return i+1;
}

