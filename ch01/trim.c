#include <stdio.h>

#define BUFFER_LEN 3

int get_line(char line[], int maxline);
int trim(char line[], char output[]);

int main() {
	int len;
	char line[BUFFER_LEN];
	char trimmed[BUFFER_LEN];

	while ((len = get_line(line, BUFFER_LEN)) > 0) {
		int newlen = trim(line, trimmed);
		if (newlen > 0) printf("%s\n", trimmed);
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

int trim(char line[], char output[]) {
	int i = 0;
	int last_non_space = -1;

	while (1) {
		char c = line[i];
		output[i] = c;
		int is_space = (c == ' ' || c == '\t' || c == '\n');
		if (c == '\0') break;
		if (!is_space) last_non_space = i;
		i++;
	}

	output[last_non_space + 1] = '\0';
	return last_non_space + 1;
}

