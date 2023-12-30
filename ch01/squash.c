#include <stdio.h>

int main() {
	int c;
	int is_squashing = 0;

	while ( (c = getchar()) != EOF) {
		if (c == ' ') {
			if (!is_squashing) {
				putchar(' ');
				is_squashing = 1;
			}
		} else {
			putchar(c);
			is_squashing = 0;
		}
	}
}
