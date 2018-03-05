/*
 * ROM split utility.
 *
 * On the Motorola 68000 based system like the Amiga. The ROMS are usually splitted into an odd and even ROM. This utility split
 * ROM image into odd and even ROM for burning.
 *
 * klam
 * 02/09/2019
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	char *rom_fname, *odd_fname, *even_fname;
	FILE *in, *odd, *even;
	unsigned char buffer[2];

	if (argc < 3) {
		printf(
			"Split ROM file into ODD and EVEN ROM\n\n"
			"Usage: %s rom even odd\n\n"
			"  rom\t\tInput ROM file\n"
			"  even\t\tOutput file with bytes on even address\n"
			"  odd\t\tOutput file with bytes on odd address\n"
			, argv[0]);
		exit(0);
	}

	rom_fname = argv[1];
	even_fname = argv[2];
	odd_fname = argv[3];

	in = fopen(rom_fname, "rb");
	if (in == NULL) {
		perror(rom_fname);
		exit(-1);
	}

	even = fopen(even_fname, "wb");
	if (even == NULL) {
		perror(even_fname);
		exit(-1);
	}

	odd = fopen(odd_fname, "wb");
	if (odd == NULL) {
		perror(odd_fname);
		exit(-1);
	}

	while (1) {
		int nbytes = fread(buffer, 1, sizeof(buffer), in);
		if (nbytes != 2)
			break;
		fwrite(&buffer[0], 1, 1, even);
		fwrite(&buffer[1], 1, 1, odd);
	}

	fclose(in);
	fclose(odd);
	fclose(even);

	return 0;
}
