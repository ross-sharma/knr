#include <stdio.h>
#define IN 0
#define OUT 1

int main() {
	int c;
	int state = OUT;
	int n_words, n_chars, n_lines;
	n_words = n_chars = n_lines = 0;

	while ( (c = getchar()) != EOF ) {
		++n_chars;
		//printf("%d, %d\n", c, n_chars);
		if (c == '\n') {
			++n_lines;
		}

		if (c != '\n' && c != ' ' && c != '\t') {
			if (state == OUT) {
				++n_words;
				state = IN;
			}
		}
		else {
			state = OUT;
		}
	}

	printf("%d words, %d chars, %d lines\n", n_words, n_chars, n_lines);
}
