#include <stdio.h>
#define MAXLINE 100

int get_line(char line[], int maxline);
void copy(char to[], char from[]);

int main() {
	int len;
	int max;
	char line[MAXLINE];
	char longest[MAXLINE];

	max = 0;

	while ((len = get_line(line, MAXLINE)) > 0) {
		if (len > max) {
			max = len;
			copy(longest, line);
		}
	}

	if (max > 0) printf("%s\n", longest);
	printf("%d\n", max);
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

void copy(char to[], char from[]) {
	int i;
	i = 0;
	while ((to[i] = from[i]) != '\0') {
		++i;
	}
}

