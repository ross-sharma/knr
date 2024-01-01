#include "stdio.h"
#include "stdlib.h"


int main(int argc, char** argv) {
	int tab_size = 4;
	char c;

	if (argc > 1) {
		tab_size = atoi(argv[1]);
		if (tab_size <= 0) {
			fprintf(stderr, "Invalid tab size argument: %s\n", argv[1]);
			return 1;
		}
	}

	int current_col = 0;

	while ( (c=getchar()) != EOF ) {
		if ( c == '\t' ) {
			do {
				putchar(' ');
				++current_col;
			} while (current_col % tab_size != 0);
		}
		else {
			putchar(c);
			++current_col;
			if (c == '\n') current_col = 0;
		}
	}
}

