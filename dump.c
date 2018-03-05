#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int main(int argc, char** argv)
{
	size_t offset = 0;
	unsigned char buffer[16];
	int nbytes;
	FILE *in;
	char *input_file;
	int i;

	if (argc < 2) {
		printf(
			"Dump ROM image\n\n"
			"Usage: %s rom\n\n"
			"  rom\t\tInput ROM file\n"
			, argv[0]);
		exit(0);
	}

	input_file = argv[1];

	in = fopen(input_file, "rb");
	if (in == NULL) {
		perror(input_file);
		exit(-1);
	}

	while (!feof(in)) {
		nbytes = fread(buffer, 1, sizeof(buffer), in);

		printf("%08X: ", offset);

		for (i = 0; i < 16; i++) {
			if (i == 8)
				printf(" ");
			if (nbytes > i)
				printf("%02X ", buffer[i]);					
			else
				printf("   ");					
		}

		for (i = 0; i < 16; i++) {
			if (i == 8)
				printf(" ");
			if (nbytes > i) {
				unsigned char c = buffer[i];
				printf("%c", isprint(c) ? c : '.');					
			}
			else
				printf(" ");					
		}

		printf("\n");
		offset += nbytes;
	}

	fclose(in);

	return 0;
}

