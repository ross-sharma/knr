#include <stdio.h>

#define OUTPUT_SIZE 256	
#define HISTOGRAM_WIDTH 100


void print_result(int* arr) {
	for (int i = 0; i < OUTPUT_SIZE; i++) {
		int val = arr[i];
		if (val != 0) printf("%4d %d\n", i, arr[i]);
	}
}


int get_max_value(int* values, int num_values) {
	int max = 0;
	for (int i = 0; i < num_values; i++) {
		int val = values[i];
		if (val > max) max = val;
	}
	return max;
}


void print_histogram(int* values, int num_values, int width) {
	int max = get_max_value(values, num_values);
	for (int i = 0; i < num_values; i++) {
		int val = values[i];
		if (val == 0) continue;
		printf("%d\n", i);
		int bar_length = ((float)val/(float)max) * width;
		if (bar_length == 0) bar_length = 1;
		for (int j = 0; j < bar_length; j++) putchar('=');
		printf(" (%d)\n", val);
		printf("\n");
	}
}


void print_vertical_histogram(int* values, int num_values, int height) {
	int max = get_max_value(values, num_values);

	for (int cur_height = height; cur_height >= 0; cur_height--) {
		for (int i = 0; i < num_values; i++) {
			int val = values[i];
			if (val == 0) continue;

			int bar_length = ((float)val/(float)max) * height;
			if (bar_length == 0) bar_length = 1;
			
			if (bar_length > cur_height) printf("   *");
			else printf("    "); 
		}
		putchar('\n');
	}

	for (int i = 0; i < num_values; i++) {
		int val = values[i];
		if (val == 0) continue;

		if (i == '\n') {
			printf("  \\n");
		}
		else if (i == ' '){
	 		printf(" spc"); 
		}
		else if (i == '\t'){
			printf("  \\t"); 
		}
		else {
			printf("%4c", i);
		}
	}
	putchar('\n');

	for (int i = 0; i < num_values; i++) {
		int val = values[i];
		if (val == 0) continue;
		printf("%4d", val);
	}
	putchar('\n');
}


int main() {
	int c;
	int counts[OUTPUT_SIZE];

	for (int i = 0; i < OUTPUT_SIZE; i++) counts[i] = 0; 

	while ( (c = getchar()) != EOF ) {
		int index = c < OUTPUT_SIZE ? c : 0;
		++counts[index];
	}

	//print_result(counts);
	//print_histogram(counts, OUTPUT_SIZE, HISTOGRAM_WIDTH);
	print_vertical_histogram(counts, OUTPUT_SIZE, 25);

	return 0;
}

