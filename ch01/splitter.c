#include <stdio.h>
#define IN 0
#define OUT 1

int main() {
	int c;
	int state = OUT;
	int n_words, n_chars, n_lines;

	while ( (c = getchar()) != EOF ) {
		int is_space = (c == '\n' || c == ' ' || c == '\t');

		if (!is_space) {
			state = IN;
			putchar(c);
		}
		else {
			if (state == IN) {
				putchar('\n');
			}
			state = OUT;
		}
	}
}
