#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

void write_uint32s(uint64_t count, FILE *output_file) {
	for (uint64_t i = 0; i < count; i++) {
		int v = rand();
		fwrite(&v, sizeof(v), 1, output_file);
	}
}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s [output file]\n", argv[0]);
		exit(1);
	}

	const uint64_t count = 32000000000;

	FILE *output_file = fopen(argv[1], "w");
	if (!output_file) {
		perror("couldn't open output file");
		exit(1);
	}

	write_uint32s(count, output_file);

	fclose(output_file);
}

