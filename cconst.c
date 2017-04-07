/* Compile: gcc -o cconst cconst.c */

#include <stdio.h>
#include <stdlib.h>

#define ROWS 16

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		printf("Syntax:\n\t%s <infile> <outfile.c>\n", argv[0]);
		exit(0);
	}
	
	FILE* infile  = fopen(argv[1], "r");
	FILE* outfile = fopen(argv[2], "w");
	
	fputs("unsigned char data[] = {\n\t", outfile);
	
	int byte = 0;
	size_t count = 0;
	while ((byte = fgetc(infile)) != EOF)
	{
		if (count % ROWS == 0 && count != 0)
		{
			fputs("\n\t", outfile);
		}
		
		fprintf(outfile, "%s0x%02X", (count != 0 ? ", " : "  "), byte);
		
		count++;
	}
	
	fputs("\n};\n", outfile);
	
	fclose(infile);
	fclose(outfile);
	
	printf("%d bytes converted to C source.\n", (int) count);
	
	return 0;
}
