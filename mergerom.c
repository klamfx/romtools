/*
 * ROM merge utitlies.
 *
 * On the Motorola 68000 based system like the Amiga. The ROMS are usually splitted into an odd and even ROM. This utility combine
 * the ROMs image into a single file so that it can easily disassembled.
 *
 * klam
 * 02/09/2019
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	char *merged_fname, *odd_fname, *even_fname;
	FILE *out, *odd, *even;
	unsigned char buffer[2];

	if (argc < 3) {
		printf(
			"Merge even and odd ROM files into single file.\n\n"
			"Usage: %s even odd rom\n\n"
			"  even\t\tEven ROM file\n"
			"  odd\t\tOdd ROM file\n"
			"  rom\t\tOutput ROM file\n"
			, argv[0]);
		exit(0);
	}

	even_fname = argv[1];
	odd_fname = argv[2];
	merged_fname = argv[3];

	out = fopen(merged_fname, "wb");
	if (out == NULL) {
		perror(merged_fname);
		exit(-1);
	}

	even = fopen(even_fname, "rb");
	if (even == NULL) {
		perror(even_fname);
		exit(-1);
	}

	odd = fopen(odd_fname, "rb");
	if (odd == NULL) {
		perror(odd_fname);
		exit(-1);
	}

	while (1) {
		if (fread(&buffer[0], 1, 1, even) != 1) break;
		if (fread(&buffer[1], 1, 1, odd) != 1) break;
		fwrite(buffer, 1, 2, out);
	}

	fclose(out);
	fclose(odd);
	fclose(even);

	return 0;
}
